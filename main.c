// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include "libs/list.h"
#include "libs/t9.h"

#define TAB_SIZE 10000

// --- HASH TABLE ---

list table[TAB_SIZE];

int hash(char *str) {
  int n = strlen(str), ans = 0;
  for(int i = n-1; i >= 0; i--)
    ans = (ans*10 + str[i] - '0') % TAB_SIZE;

  return ans;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, "");
  fwide(stdin,  1);
  fwide(stdout, 1);
  
  /*
  wchar_t str[20];
  wscanf(L"%S", str);
 
  char *new_str = keyboard(str);  
  wprintf(L"%s %d\n", new_str, hash(new_str));
  */

  list l = (list)malloc(sizeof(node));
  l->next = NULL;
  
  for(int i = 0; i < 5; i++) {
    wchar_t *str = malloc(20*4);
    wscanf(L"%S", str);
    insert(l,str,i+1);
  }

  print_list(l);
  
  return 0;
}

