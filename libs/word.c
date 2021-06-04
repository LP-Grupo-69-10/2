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

void next_word(FILE *fp, char *str) {  
  int i = 1;

  while(strchr(delim, (str[0] = fgetc(fp))) != NULL);
    
  if(feof(fp)) {
    *str = 0;
    return;
  }
  
  while(strchr(delim, (str[i] = fgetc(fp))) == NULL) i++;
  if(str[i] == '-' || str[i] == '\'') {
    while(strchr(delim, (str[++i] = fgetc(fp))) == NULL);
  } str[i] = 0;
}

