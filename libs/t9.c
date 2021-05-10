// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "t9.h"

wchar_t *T[10] =
  {
   L"0",
   L"1",
   L"2AÃÁÀÂBCÇaãáàâbcç",
   L"3DEÉÊFdeéêf",
   L"4GHIÍghií",
   L"5JKLjkl",
   L"6MNOÕÓÔmnoõóô",
   L"7PQRSpqrs",
   L"8TUÚVtuúv",
   L"9WXYZwxyz"
  };

int contains(wchar_t *str, wchar_t chr) {
  while(*str != 0) {
    if(*str == chr) return 1;
    str++;
  }

  return 0;
}

int key(wchar_t chr) {
  for(int i = 0; i <= 9; i++) {
    if(contains(T[i], chr)) return i;
  }
  
  return -1;
}

char* keyboard(wchar_t *str) {
  int n = wcslen(str);
  char *ans = malloc(n);
  
  for(int i = 0; i < n; i++)
    ans[i] = key(str[i]) + '0';

  return ans;
}
