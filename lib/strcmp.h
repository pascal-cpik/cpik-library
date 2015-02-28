#ifndef __STRCMP_H
#define __STRCMP_H

#include <sys/types.h>
size_t strlen(char *s);
char *strcat(char *dests, char *src);
char *strcpy(char *dests, char *src);
char strcmp(char *s1, char *s2);
char strcasecmp(char *s1, char *s2);
char strncasecmp(char *s1, char *s2, size_t n);
char strncmp(char *s1, char *s2, size_t n);

#endif
