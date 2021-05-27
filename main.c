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
#include "libs/file.h"

char *filename = "lusiadas.txt";
char *delim = " .,;?!()[]:\"\n\'-";

void next_word(FILE *fp, char *word) {  
  int i = 1;

  while(strchr(delim, (word[0] = fgetc(fp))) != NULL);
    
  if(feof(fp)) {
    *word = 0;
    return;
  }
  
  while(strchr(delim, (word[i] = fgetc(fp))) == NULL) i++;
  if(word[i] == '-' || word[i] == '\'') {
    while(strchr(delim, (word[++i] = fgetc(fp))) == NULL);
  } word[i] = 0;

  puts(word);
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

int main() {
  hash_table table = new_table();
  read_file(table);
  
  //hash_table table = read_ft("cocoxixi.bin");

  /* atualizar no ficheiro é assim */
  /* write_wf(w, "cocoxixi.bin"); */
  /* print_file("cocoxixi.bin"); */
  
  /* int p = 0; */
  /* char ch, t9[20] = {0}; */
  /* while((ch = getchar()) != '\n') {	 */
  /*   if(ch == 'D') { */
  /*     t9[--p] = '\0'; */
  /*   } else { */
  /*     t9[p++] = ch; */
  /*   } */

  /*   getchar(); */
  /*   printf("\e[1;1H\e[2J"); */

  /*   printf("typed: %s\nsugested:\n", t9); */
  /*   t9_autocomplete(table, t9); */
  /* } */
  
  write_tf(table, "cocoxixi.bin");
  
  return 0;
}
