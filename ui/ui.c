// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.11
// Project name: EdusatUI

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Navbar;
lv_obj_t * ui_CompanyPanel;
lv_obj_t * ui_CompanyLogo;
lv_obj_t * ui_EdusatLabel;
lv_obj_t * ui_EdusatLabelText;
lv_obj_t * ui_NavPanel;
lv_obj_t * ui_TabView;
lv_obj_t * ui_OverviewTab;
lv_obj_t * ui_OverviewTopRowCont;
lv_obj_t * ui_BMECont;
lv_obj_t * ui_BMEHeaderCont;
lv_obj_t * ui_BMEHeaderLabel;
lv_obj_t * ui_BMEInfoCont;
lv_obj_t * ui_AltitudeInfoCont;
lv_obj_t * ui_AltitudeValueLabel;
lv_obj_t * ui_AltitudeUnitLabel;
lv_obj_t * ui_PressureInfoCont;
lv_obj_t * ui_PressureValueLabel;
lv_obj_t * ui_PressureUnitLabel;
lv_obj_t * ui_TempCont;
lv_obj_t * ui_TempHeaderCont;
lv_obj_t * ui_TempHeaderLabel;
lv_obj_t * ui_TempInfoCont;
lv_obj_t * ui_TempArc;
lv_obj_t * ui_TempValueLabel;
lv_obj_t * ui_TempUnitLabel;
lv_obj_t * ui_HumidityCont;
lv_obj_t * ui_HumidityHeaderCont;
lv_obj_t * ui_HumidityHeaderLabel;
lv_obj_t * ui_HumidityInfoCont;
lv_obj_t * ui_HumidtyArc;
lv_obj_t * ui_HumidityValueLabel;
lv_obj_t * ui_HumidityUnitLabel;
lv_obj_t * ui_MagnetometerCont;
lv_obj_t * ui_MagentometerHeaderCont;
lv_obj_t * ui_MagnetometerHeaderLabel;
lv_obj_t * ui_MagentometerInfoCont;
lv_obj_t * ui_MagentometerArc;
lv_obj_t * ui_MagnetometerValueLabel;
lv_obj_t * ui_MagentometerUnitLabel;
lv_obj_t * ui_OverviewBottomRowCont;
lv_obj_t * ui_DoubleDataCont;
lv_obj_t * ui_GPSCont;
lv_obj_t * ui_GPSHeaderCont;
lv_obj_t * ui_GPSHeaderLabel;
lv_obj_t * ui_GPSInfoCont;
lv_obj_t * ui_LatInfoCont;
lv_obj_t * ui_LatitudeValueLabel;
lv_obj_t * ui_LatitudeUnitLabel;
lv_obj_t * ui_LongInfoCont;
lv_obj_t * ui_LongValueLabel;
lv_obj_t * ui_LongUnitLabel;
lv_obj_t * ui_UVCont;
lv_obj_t * ui_UVHeaderCont;
lv_obj_t * ui_UVHeaderLabel;
lv_obj_t * ui_UVInfoCont;
lv_obj_t * ui_LatInfoCont1;
lv_obj_t * ui_UVValueLabel;
lv_obj_t * ui_UVUnitLabel;
lv_obj_t * ui_VoltageCont;
lv_obj_t * ui_VoltageHeaderCont;
lv_obj_t * ui_VoltageHeaderLabel;
lv_obj_t * ui_VoltageInfoCont;
lv_obj_t * ui_VoltageArc;
lv_obj_t * ui_VoltageValueLabel;
lv_obj_t * ui_VoltageUnitLabel;
lv_obj_t * ui_CurrentCont;
lv_obj_t * ui_CurrentHeaderCont;
lv_obj_t * ui_VoltageHeaderLabel1;
lv_obj_t * ui_CurrentInfoCont;
lv_obj_t * ui_CurrentArc;
lv_obj_t * ui_CurrentValueLabel;
lv_obj_t * ui_CurrentUnitLabel;
lv_obj_t * ui_MPU6050Cont;
lv_obj_t * ui_MPU605HeaderCont;
lv_obj_t * ui_Attitude;
lv_obj_t * ui_MPU6050InfoCont;
lv_obj_t * ui_AccInfoCont;
lv_obj_t * ui_AltitudeValueLabel1;
lv_obj_t * ui_AltitudeUnitLabel1;
lv_obj_t * ui_GyroInfoCont;
lv_obj_t * ui_PressureValueLabel1;
lv_obj_t * ui_PressureUnitLabel1;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}