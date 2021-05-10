// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "list.h"

void insert(list l, wchar_t *word, int freq) {
  list add = (list)malloc(sizeof(node)), prev;
  add->word = word;
  add->freq = freq;
  
  prev = l;

  while(l->next != NULL) {
    l = l->next;
    
    if(l->freq <= add->freq) {
      prev->next = add;
      add->next = l;
      return;
    }    
    prev = l;
  }

  // if not returned
  l->next = add;
  add->next = NULL;
}

void print_list(list l) {
  while((l = l->next) != NULL) {
    wprintf(L"%S: %d\n", l->word, l->freq);
  }
}
