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

int main() {
  char *str = "cãozarrão comilão com comichão";

  printf("%s -> %d\n", str, utf8_strlen(str));

  for(int i = 0, offset; str[i] != 0; i+=offset) {
    offset = utf8_chrlen(&str[i]);
    
    char chr[offset+1];
    strncpy(chr, &str[i], offset);
    chr[offset] = '\0';
    
    printf("%d", t9_getkey(chr));
  }

  printf("\n%d %d\n", (int)strlen(str), (int)utf8_strlen(str));

  list l = (list)malloc(sizeof(node));
  l->next = NULL;

  char* teste[] = {"ola", "o", "michael", "come", "croissants"};
  int    freq[] = {10, 20, 30, 40, 50};
  for(int i = 0; i < 5; i++) {
    word *w = (word*)malloc(sizeof(word));
    w->str  = teste[i];
    w->freq = freq[i];
    insert(l,w);
  }
  
  print_list(l);
  
  return 0;
}
