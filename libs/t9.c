// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t9.h"

char *t9_map[10] =
  {
   "0",
   "1",
   "2AÃÁÀÂBCÇaãáàâbcç",
   "3DEÉÊFdeéèêf",
   "4GHIÍghií",
   "5JKLjkl",
   "6MNOÕÓÔmnoõóô",
   "7PQRSpqrs",
   "8TUÚVtuúv",
   "9WXYZwxyz"
  };

int t9_getkey(char *chr) {
  for(int i = 0; i < 10; i++) {
    if(strstr(t9_map[i], chr) != NULL)
      return i;
  }

  return -1;
}
