#ifndef _SERIAL_H_
#define _SERIAL_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <inttypes.h>

#ifndef PORTNAME
#define PORTNAME "/dev/ttyAMA0"
#endif

void serial_init(void);
void serial_config(void);
void serial_println(const char *, int);
void serial_readln(char *, int);
void serial_close(void);
#ifdef __cplusplus
}   
#endif

#endif // _SERIAL_H_s
