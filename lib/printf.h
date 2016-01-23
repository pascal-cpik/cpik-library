#ifndef _PRINTF_H
#define _PRINTF_H

#include <rom.h>
#include <sys/types.h>

// printf function using embedded ROM code. It is implemented with a
// macro and does not directly return a value, because it is implemented
// as series of commands. If really required, the result can be re-
// trieved from _r0 with ROM_result_char().

#define printf( fmt, ... ) {  \
  get_ROM_ptr_();             \
  __datat__(fmt,"\0");        \
  printf_(0u, __VA_ARGS__);   \
}

// printf function (implemented as macro) that uses a ROM accessor.
// e.g. defined ROMF_TXT(fmt, "format %d\0")

#define RFprintf( fmt, ... ) \
  printf_(2u, fmt, __VA_ARGS__);

// printf function (implemented as macro) that uses a ROM pointer to
// pass the format string, e.g. using ROM_ENTRY(fmt) { __datat__ ... }

#define RPprintf( fmt, ... ) \
  printf_(4u, fmt, __VA_ARGS__);

// printf function (implemented as macro) that uses a format string
// stored in RAM.

#define RAMprintf( fmt, ... ) \
  printf_(1u, fmt, __VA_ARGS__);

// sprintf, with format string embedded in the ROM code.
// Note that sprintf cannot return a value. It is, however, stored in
// _r0 when the function returns and can be retrieved by calling
// ROM_result_char()

#define sprintf( str, fmt, ... ) {    \
  get_ROM_ptr_();                     \
  __datat__(fmt,"\0");                \
  printf_(0u|0x80, str, __VA_ARGS__); \
}

// sprintf function with format string stored as ROM accessor.

#define RFsprintf( str, fmt, ... )               \
  printf_(2u|0x80, str, fmt, __VA_ARGS__);  

// sprintf function with format string passed as ROM pointer

#define RPsprintf( str, fmt, ... )               \
  printf_(4u|0x80, str, fmt, __VA_ARGS__);  

// sprintf function with format string stored in RAM.

#define RAMsprintf( str, fmt, ... )               \
  printf_(1u|0x80, str, fmt,  __VA_ARGS__);

// set output vector for printf rountines. The function
// returns the previously installed vector.

typedef void (*printf_putch_fun)(char);
printf_putch_fun printf_set_putch(printf_putch_fun vec);


// retrieve return value of printf functions with format
// string embedded in ROM code. The value is also in _r0 upon
// exit, but this is safer since the value is preserved
// until the next call to printf...

unsigned char printf_chars_printed();

// functions not to be called directly

unsigned char printf_(uint8_t mode,...) ;
void get_ROM_ptr_();


#endif
