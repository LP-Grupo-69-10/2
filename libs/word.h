// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef WORD_H
#define WORD_H

typedef struct {
  char *str;
  int   freq;
} word;

word* new_word();
void next_word(FILE*, char*);

#endif /* WORD_H  */

