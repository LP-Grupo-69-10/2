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

int main() {
  hash_table table = new_table();
  int words = 0;
  
  while(1) {
    char* word = malloc(20);
    next_word(stdin, word);
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

  /*
  printf("words %d\n%d/%d = %.2f\n", words, (M-cnt), M, (float)(M-cnt)/M);
  printf("max: %d\n", max);
  */

  print_list(table[hash("5652")]);
  
  return 0;
}
