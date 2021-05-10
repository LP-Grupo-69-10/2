// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef T9_H
#define T9_H

#include <wchar.h>

int contains(wchar_t *str, wchar_t chr);
int key(wchar_t chr);
char* keyboard(wchar_t *str);

#endif /* T9_H */
