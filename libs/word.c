// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "word.h"

char *delim = " .,;?!()[]:\"\n\'-";

word* new_word() {
  word *w = (word*)malloc(sizeof(word));
  w->str = NULL;
  w->freq = 0;

  return w;
}

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

