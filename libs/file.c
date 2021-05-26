// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "t9.h"

void write_tf(hash_table table, char *filename) {  
  FILE *fp = fopen(filename,"wb");

  if(fp != NULL) {
    for(int i = 0; i < M; i++) {
      list l = table[i];
      while((l = l->next) != NULL) {
	fwrite(&l->key->freq, sizeof(int), 1, fp);
        fwrite(l->key->str, sizeof(char), strlen(l->key->str)+1, fp);
      }
    }
  }
    
  fclose(fp);
}

hash_table read_ft(char *filename) {
  FILE *fp = fopen(filename,"rb");
  hash_table table = new_table();
  
  if(fp == NULL) return table;
  
  while(1) {
    word *w = new_word();
    w->str = malloc(20*sizeof(char));
    
    fread(&w->freq, sizeof(int), 1, fp);

    if(w->freq == 0) {
      free(w);
      break;
    }
    
    int i = 0;
    while(1) {
      fread(&w->str[i], sizeof(char), 1, fp);
      if(w->str[i++] == '\0') break;
    }

    char *t9 = t9_string(w->str);
    insert_word(table[hash(t9)], w);
    free(t9);
  }
  
  fclose(fp);
  
  return table;
}
