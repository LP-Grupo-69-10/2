// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "file.h"
#include "t9.h"

list new_list() {
  list l = (list)malloc(sizeof(struct node));
  l->key  = NULL;
  l->next = NULL;

  return l;
}

word* search_list(list l, char *str) {
  while((l = l->next) != NULL) {
    if(strcmp(str, l->key->str) == 0) {
      return l->key;
    }
  }

  return NULL;
}

void remove_list(list l, char *str) {
  while(l->next != NULL) {    
    if(strcmp(str, l->next->key->str) == 0) {
      list remove = l->next;
      l->next = l->next->next;
      free(remove);
      
      return;
    }

    l = l->next;
  }
}

void insert_list(list l, char *str) {
  word *w;
  if((w = search_list(l, str)) != NULL) {
    remove_list(l, str);
    w->freq++;
  }
  else {
    w = new_word();
    w->str = malloc(20*sizeof(char));
    strcpy(w->str, str);
    w->freq = 1;
  }

  insert_word(l, w);
}

void insert_word(list l, word *w) {
  list add = new_list(), prev = l;
  add->key = w;
  
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
