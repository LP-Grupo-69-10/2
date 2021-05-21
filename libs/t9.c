// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t9.h"
#include "utf8.h"

char *t9_map[10] =
  {
   "0",
   "1",
   "2AÃÁÀÂBCÇaãáàâbcç",
   "3DEÉÈÊFdeéèêf",
   "4GHIÍghií",
   "5JKLjkl",
   "6MNOÕÓÔmnoõóô",
   "7PQRSpqrs",
   "8TUÚÜVtuúüv",
   "9WXYZwxyz"
  };

int t9_getkey(char *chr) {
  for(int i = 0; i < 10; i++) {
    if(strstr(t9_map[i], chr) != NULL)
      return i;
  }

  return -1;
}

char* t9_string(char *str) {
  char *t9 = malloc(utf8_strlen(str)*sizeof(char));
  int bytes = 0, k = 0;
  
  for(int i = 0; str[i]; i += bytes) {
    char *cur = next_char(&str[i]); 
    t9[k++] = (char)t9_getkey(cur) + '0';
    
    bytes = strlen(cur);
  }

  return t9;
} 
