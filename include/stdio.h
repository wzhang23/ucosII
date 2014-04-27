#ifndef _STDIO_H
#define _STDIO_H

int vsnprintf(char *buf, size_t size, const char *fmt, va_list args);
int snprintf(char * buf, size_t size, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char * buf, const char *fmt, ...);
int vsscanf(const char * buf, const char * fmt, va_list args);
int sscanf(const char * buf, const char * fmt, ...);

int printf(const char *fmt, ...);
int scanf(const char * fmt, ...);

#endif /* _STDIO_H */
