// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include "utf8.h"

int utf8_luggage(char chr) {
  return (chr & 0xc0) == 0x80;
}

int utf8_chrlen(char *chr) {
  if((chr[0] & 0x80) == 0x0)
    return 1;
  else if((chr[0] & 0xe0) == 0xc0 && utf8_luggage(chr[1]))
    return 2;
  else if((chr[0] & 0xf0) == 0xe0 && utf8_luggage(chr[1]) && utf8_luggage(chr[2]))
    return 3;
  else if((chr[0] & 0xf8) == 0xf0 && utf8_luggage(chr[1]) && utf8_luggage(chr[2]) && utf8_luggage(chr[3]))
    return 4;

  return 0;
}

int utf8_strlen(char *str) {
  int size = 0, bytes = 1;
  
  for(int i = 0; str[i] != '\0'; i+=bytes) {
    bytes = utf8_chrlen(&str[i]);
    // printf("%d\n", bytes);
    size++;
  }

  return size;
}
