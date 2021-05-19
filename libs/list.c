// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void insert(list l, word *key) {
  list add = (list)malloc(sizeof(node)), prev;
  add->key = key;
  
  prev = l;

  while(l->next != NULL) {
    l = l->next;
    
    if(l->key->freq <= add->key->freq) {
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
    printf("%s: %d\n", l->key->str, l->key->freq);
  }
}
