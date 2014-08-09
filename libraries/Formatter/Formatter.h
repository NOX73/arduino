#ifndef Formatter_h
#define Formatter_h

#include <stdarg.h>
#include "Arduino.h"

class Formatter {
  private:
    void formatChar(char **out, const char format, va_list *args);

  public:
    char* f(char *out, const char *format, ...);
    char* f(char *out, const __FlashStringHelper *format, ...);
    Formatter(){};

};

extern Formatter Fmt;
#endif
