// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/t9.h"
#include "libs/utf8.h"
#include "libs/word.h"
#include "libs/list.h"
#include "libs/hash.h"

char *filename = "lusiadas.txt";
char *delim = " .,;?!()[]:\"\n-\'";

void next_word(FILE *fp, char *word) {  
  int i = 1;

  while(strchr(delim, (word[0] = fgetc(fp))) != NULL);
  if(feof(fp)) {
    *word = 0;
    return;
  }
  
  while(strchr(delim, (word[i] = fgetc(fp))) == NULL) i++;
  word[i] = 0;
}

void read_file(hash_table table) {
  FILE *fp = fopen(filename, "r");
    
  while(1) {
    char* word = malloc(20);
    next_word(fp, word);

    if(word[0] == '\0') break;
    insert_table(table, word);
  }

  fclose(fp);
}

void t9_autocomplete(hash_table table, char *t9, int original_size) {
  int flag = 0;
  list l = table[hash(t9)];
  
  while((l = l->next) != NULL) {
    char *temp = t9_string(l->key->str);

    if(strcmp(temp, t9) == 0) {
      printf("%s ", l->key->str);
      flag = 1;
    }
    
    free(temp);
  }

  if(!flag) {
    int n = strlen(t9);
    if(n > 16 || n == original_size+3) return;
    
    for(char ch = '2'; ch <= '9'; ch++) {
      t9[n] = ch;
      t9_autocomplete(table, t9, original_size);
      t9[n] = '\0';
    }
  }
  else {
    printf("-> %s\n", t9);
  }
}

int main() {
  hash_table table = new_table();
  read_file(table);
  
  int p = 0;
  char ch, t9[20] = {0};
  while((ch = getchar()) != '\n') {	
    if(ch == 'D') {
      t9[--p] = '\0';
    } else {
      t9[p++] = ch;
    }

    getchar();
    printf("\e[1;1H\e[2J");

    printf("typed: %s\nsugested:\n", t9);
    t9_autocomplete(table, t9, strlen(t9));
  }
  
  return 0;
}
