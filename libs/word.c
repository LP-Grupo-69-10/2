// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdlib.h>
#include "word.h"

word* new_word() {
  word *w = (word*)malloc(sizeof(word));
  w->str = NULL;
  w->freq = 0;

  return w;
}
