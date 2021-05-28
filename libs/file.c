// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "word.h"
#include "t9.h"

void write_tf(hash_table table, char *filename) {  
  FILE *fp = fopen(filename, "wb");

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

void write_wf(word *w, char *filename) {
  FILE *fp = fopen(filename, "rb+");

  if(fp == NULL) {
    printf("%s: file does not exist\n", filename);
    return;
  }

  while(1) {
    word *t = new_word();
    t->str = malloc(32*sizeof(char));
  
    fread(&t->freq, sizeof(int), 1, fp);
    if(t->freq == 0) {
      free(t);
      break;
    }
    
    int i = 0;
    while(1) {
      fread(&t->str[i], sizeof(char), 1, fp);
      if(t->str[i++] == '\0') break;
    }

    if(strcmp(w->str, t->str) == 0) {
      fseek(fp, -(strlen(t->str)+1+4), SEEK_CUR);
      break;
    }
  }
  
  fwrite(&w->freq, sizeof(int), 1, fp);
  fwrite(w->str, sizeof(char), strlen(w->str)+1, fp);
  
  fclose(fp);
}

void read_ft(hash_table table, char *filename) {
  FILE *fp = fopen(filename, "rb");
    
  if(fp == NULL) {
    return;
  }
  
  while(1) {
    word *w = new_word();
    w->str = malloc(32*sizeof(char));
    
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
}

void load_ft(hash_table table, char *filename) {
  FILE *fp = fopen(filename, "r");
    
  while(1) {
    char* word = malloc(20);
    next_word(fp, word);

    if(word[0] == '\0') break;
    insert_table(table, word);
  }

  fclose(fp);
}

void print_file(char *filename) {
  FILE *fp = fopen(filename, "rb");

  while(1) {
    word *t = new_word();
    t->str = malloc(32*sizeof(char));
  
    fread(&t->freq, sizeof(int), 1, fp);
    if(t->freq == 0) {
      free(t);
      break;
    }
    
    int i = 0;
    while(1) {
      fread(&t->str[i], sizeof(char), 1, fp);
      if(t->str[i++] == '\0') break;
    }

    printf("%s: %d\n", t->str, t->freq);
  }

  fclose(fp);
}




