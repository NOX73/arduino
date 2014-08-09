#include "Formatter.h"

char* Formatter::f(char *out, const __FlashStringHelper *fmt, ...) {
  char *origin = out;

  va_list args;
  va_start(args, fmt);

  PGM_P p = reinterpret_cast<PGM_P>(fmt);
  char c;

  do {
    c = pgm_read_byte(p++);
    if (c == '%') {
      c = pgm_read_byte(p++);
      formatChar(&out, c, &args);
    } else {
      *out = c;
      out++;
    }
  } while(c != 0);

  *out = 0;

  return origin;
}

char* Formatter::f(char *out, const char *fmt, ...) {
  char *origin = out;

  va_list args;
  va_start(args, fmt);

  for(;*fmt != 0; fmt++){
    char c = *fmt;
    if(c == '%') {
      fmt++;
      formatChar(&out, *fmt, &args);
    } else {
      *out = *fmt;
      out++;
    }
  }

  *out = 0;

  return origin;
}

void Formatter::formatChar(char **out, const char format, va_list *args) {
  if (format == '\0') return;

  if (format == '%') {
    **out = format;
    *out++;
    return;
  }

  if( format == 's' ) {
    char *s = (char *)va_arg( *args, int );

    Serial.println(s);

    for(;*s != 0; s++){
      **out = *s;
      *out = *out + 1;
    }

    return;
  }

  if( format == 'd' || format == 'i') {
    int n = va_arg( *args, int );

    char buff[sizeof(int) * 8];
    char l = 0;

    if(n < 0) {
      **out = '-';
      *out = *out + 1;
      n = -n;
    }

    do {
      int m = n;
      n /= 10;
      char c = m - 10 * n;
      buff[l] = c;
      l++;
    } while(n);

    l--;

    for(;l >= 0; l--) {
      **out = buff[l] + '0';
      *out = *out + 1;
    }

    return;
  }


}

Formatter Fmt = Formatter();

