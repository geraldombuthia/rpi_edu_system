#include <cstddef>
#include <cstdio>
#include "mpu6050.h"
#include "bme280.h"
#include "mcp3008.h"
#include "hmc5883l.h"
// #include "gps_data.h"
#include <wiringPi.h>
#include "ui/ui.h"

#include <SDL2/SDL.h>
#include "lv_drv_conf.h"
#include "lv_conf.h"
#include "lvgl.h"
#include "sdl/sdl.h"
#include  "gps.h"

#define MAXTIMINGS 85
#define DHTPIN 3

int dht11_dat[5] = {0, 0, 0, 0, 0};
double dht_temp;
double dht_humidity;

int gui_tick_thread(void* data) {
    (void)data;

    while(1) {
        SDL_Delay(1);

        lv_tick_inc(1); /* Tell LittelvGL that 1 milliseconds were elapsed */


    }
    return 0;
}

int read_dht11_dat()
{
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    pinMode(DHTPIN, OUTPUT);
    digitalWrite(DHTPIN, LOW);
    delay(18);
    digitalWrite(DHTPIN, HIGH);
    delayMicroseconds(40);
    pinMode(DHTPIN, INPUT);

    for (i = 0; i < MAXTIMINGS; i++)
    {
        counter = 0;
        while (digitalRead(DHTPIN) == laststate)
        {
            counter++;
            delayMicroseconds(1);
            if (counter == 255)
                break;
        }
        laststate = digitalRead(DHTPIN);

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0))
        {
            dht11_dat[j / 8] <<= 1;
            if (counter > 64)
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF)))
    {
        dht_temp = dht11_dat[2] + (dht11_dat[3] / 10);
        dht_humidity = dht11_dat[0] + (dht11_dat[1] / 10);
        return (1);
    }
    else
        return (0);
}

char * format_double_to_char(double value)
{
    char buffer[20];
    snprintf(buffer, 20, "%.2f", value);
    return buffer;
}

int main()
{
    float roll, pitch, yaw;
    float ax, ay, az;

    // Create an instance of the BME280 class
    MPU6050 mpu6050(0x68, true);

    // Create an instance of the BME280 class
    BME280 sensor(0x76);
    // Call the measure method to get the measurements
    BME280::Measurement_t measurements = sensor.measure();

    // Create an instance of the MCP3008 class
    MCP3008 adc;

    // Create an instance of the HMC5883L class
    HMC5883L hmc5883l;

    // Create an instance of the GPSData class
    // GPS gps_data;

    loc_t location;

    // gps_data.init();
    gps_init();

    delay(1000);
    // Initialize

    if (wiringPiSetup() == -1)
        // exit(1);
        printf("WirinPi setup failed\n");

    // Now you can access the measurements
    lv_init();
    sdl_init();
    SDL_CreateThread(gui_tick_thread, "gui_tick_thread", NULL);

    /*Create a display buffer*/
    static lv_color_t buf[SDL_HOR_RES * SDL_VER_RES];
    static lv_disp_draw_buf_t disp_draw_buf;
    lv_disp_draw_buf_init(&disp_draw_buf, buf, NULL, SDL_HOR_RES * SDL_VER_RES);

    /*Create a display*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.draw_buf = &disp_draw_buf;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

    /* Add a mouse as input device */
    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = sdl_mouse_read;
    lv_indev_drv_register(&indev_drv);

    ui_init();

    while (1)
    {
        lv_task_handler();

        float temperature = measurements.temperature; // in degrees Celsius
        float pressure = measurements.pressure;       // in hPa
        float humidity = measurements.humidity;       // in %
        float altitude = measurements.altitude;       // in meters

        mpu6050.getGyro(&roll, &pitch, &yaw);
        mpu6050.getAccel(&ax, &ay, &az);

        adc.readAllChannels();

        // if (gps_data.location(&location) != gps_state_t::GPS_STATE_READ) {
        //     printf("Error reading GPS data\n");
        // }
        // gps_location(&location);

        // Initialize
        if (hmc5883l_init(&hmc5883l) != HMC5883L_OKAY)
        {
            fprintf(stderr, "Error: %d\n", hmc5883l._error);
            // exit(1);
        }

        // Read
        hmc5883l_read(&hmc5883l);

        read_dht11_dat();

        lv_label_set_text(ui_AltitudeValueLabel, "10,000");
        lv_label_set_text(ui_AltitudeUnitLabel, "m");
        lv_label_set_text(ui_PressureValueLabel, "23,800");
        lv_label_set_text(ui_PressureUnitLabel, "Pa");
        lv_arc_set_value(ui_TempArc, dht_temp);
        lv_label_set_text(ui_TempValueLabel, format_double_to_char(dht_temp));
        lv_label_set_text(ui_TempUnitLabel, " °C");
        lv_arc_set_value(ui_HumidtyArc, dht_humidity);
        lv_label_set_text(ui_HumidityValueLabel, format_double_to_char(dht_humidity));
        lv_label_set_text(ui_HumidityUnitLabel, "%");

        lv_arc_set_value(ui_MagentometerArc, hmc5883l._data.orientation_deg);
        lv_label_set_text(ui_MagnetometerValueLabel, format_double_to_char(hmc5883l._data.orientation_deg));
        lv_label_set_text(ui_MagentometerUnitLabel, "°");

        lv_label_set_text(ui_LatitudeValueLabel, format_double_to_char(location.latitude));
        lv_label_set_text(ui_LatitudeUnitLabel, "lat");
        lv_label_set_text(ui_LongValueLabel, format_double_to_char(location.longitude));
        lv_label_set_text(ui_LongUnitLabel, "lon");
        // lv_label_set_text(ui_UVValueLabel, std::to_string(adc.readChannel(0)).c_str());
        lv_label_set_text(ui_UVUnitLabel, "lux");
        lv_label_set_text(ui_VoltageValueLabel, "5.0");
        lv_label_set_text(ui_VoltageUnitLabel, "V");
        lv_label_set_text(ui_CurrentValueLabel, "5.0");
        lv_label_set_text(ui_CurrentUnitLabel, "A");
        lv_label_set_text(ui_AltitudeValueLabel1, "10,000");
        lv_label_set_text(ui_AltitudeUnitLabel1, "m");
        lv_label_set_text(ui_PressureValueLabel1, "23,800");
        lv_label_set_text(ui_PressureUnitLabel1, "Pa");

        // Print results
        printf("X: %f Y:%f Z:%f\n",
               hmc5883l._data.x,
               hmc5883l._data.y,
               hmc5883l._data.z);

        printf("Scaled:\t%f | %f | %f\n",
               hmc5883l._data.x_scaled,
               hmc5883l._data.y_scaled,
               hmc5883l._data.z_scaled);

        printf("Orientation:Deg: %f | Rad: %f\n",
               hmc5883l._data.orientation_deg,
               hmc5883l._data.orientation_rad);

        printf("Roll: %f, Pitch: %f, Yaw: %f\n", roll, pitch, yaw);
        printf("Ax: %f, Ay: %f, Az: %f\n\n", ax, ay, az);


        printf("Humidity: %.1f%%\nTemperature: %.1f C\n", dht_humidity, dht_temp);

        printf("Temperature: %.2f C Pressure: %.2f hPa Humidity: %.2f %% Altitude: %.2f m\n\n", temperature, pressure, humidity, altitude);

        printf("GPS Location: Latitude: %f Longitude: %f\n", location.latitude, location.longitude);

        fflush(stdout);

        delay(1000); // To be removed later on
    }
}
