// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef WORD_H
#define WORD_H

#include <wchar.h>

typedef struct {
  wchar_t *str;
  int      freq;
} word;

#endif /* WORD_H  */
