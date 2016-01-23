#ifndef __STRCMP_H
#define __STRCMP_H

#include <sys/types.h>
#include <rom.h>

size_t strlen(char *s);
char *strcat(char *dests, char *src);
char *strcpy(char *dests, char *src);
char strcmp(char *s1, char *s2);
char strcasecmp(char *s1, char *s2);
char strncasecmp(char *s1, char *s2, size_t n);
char strncmp(char *s1, char *s2, size_t n);

// ------------------- embedded ROM versions ----------------------

// these cannot return a result, for syntax reason. However, the
// result is stored in _r0. It is accessible by ROM_result_char()

#define ROMstrcmp(s1, s2) {      \
  get_ROM_ptr_();                \
  __datat__(s2,"\0");            \
  ROMstrcmp_(s1);                \
}

char ROMstrcmp_(char *);

// note that this "function" do not return a value

#define ROMstrcpy(s1, s2) {      \
  get_ROM_ptr_();                \
  __datat__(s2,"\0");            \
  ROMstrcpy_(s1);                \
}

void ROMstrcpy_(char *);

// note that this "function" do not return a value

#define ROMstrcat(s1, s2) {      \
  get_ROM_ptr_();                \
  __datat__(s2,"\0");            \
  ROMstrcat_(s1);                \
}

void ROMstrcat_(char *);

// ------------------- ROM accessor versions --------------------

char *RFstrcpy(char *dest, ROMF_txt_t src);
char *RFstrcat(char *dest, ROMF_txt_t src);

// ------------------- ROM pointer versions ---------------------

char *RPstrcpy(char *dest, ROMptr src);
char *RPstrcat(char *dest, ROMptr src);

// ------------------- helper functions -------------------------

void get_ROM_ptr_();

// retrieve result of functions that can't return a value because
// they are invoked as series of commands in a macro.
// simply returns _r0.

char ROM_result_char();

#endif
