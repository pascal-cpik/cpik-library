#ifndef _PRINTF_H
#define _PRINTF_H


// http://stackoverflow.com/questions/5588855/standard-alternative-to-gccs-va-args-trick

#include <rom.h>


#define printf( fmt, ... ) printf_get_fmt_ptr_(); __datat__(fmt); __datat__("\0"); printf_(0u, __VA_ARGS__); 

unsigned char printf_(uint8_t dummy,...) ;
void printf_get_fmt_ptr_();


#endif
