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

int K = 2;
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

void t9_autocomplete(hash_table table, char *t9) {
  int len = strlen(t9), found = 0;
  list l = table[hash(t9)];

  if(len > K+2) return;
  
  while((l = l->next) != NULL) {
    if(utf8_strlen(l->key->str) == len) {
      printf("%s ", l->key->str);
      found = 1;
    }
  }

  if(!found) {
    for(int i = '2'; i <= '9'; i++) {
      t9[len] = i;      
      t9_autocomplete(table, t9);
      t9[len] = '\0';
    }
  } else {
    printf("are from %s\n", t9);
  }
}

int main() {
  FILE *fp = fopen(filename, "r");
  
  hash_table table = new_table();
  int words = 0;
  
  while(1) {
    char* word = malloc(20);
    next_word(fp, word);

    if(word[0] == '\0') break;
    insert_table(table, word);
    words++;
  }
  
  int cnt = 0, max = 0;
  for(int i = 0; i < M; i++) {
    cnt += table[i]->next == NULL ? 1 : 0;

    list l = table[i];
    int size = 0;
    while((l = l->next) != NULL)
      size++;

    max = max < size ? size : max;
  }
  
  printf("words %d\n%d/%d = %.2f\n", words, (M-cnt), M, (float)(M-cnt)/M);
  printf("max: %d\n\n", max);

  // printf("%d %d\n", hash("234323"), hash("262327"));
  
  print_list(table[hash("234323")]);

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
    t9_autocomplete(table, t9);
    K = strlen(t9);
  }

  fclose(fp);
  
  return 0;
}
