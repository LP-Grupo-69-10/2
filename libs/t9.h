// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef T9_H
#define T9_H

#include "hash.h"

int t9_getkey(char*);
char* t9_string(char*);
list t9_find(hash_table, char*);
list t9_autocomplete(hash_table, char*);

#endif /* T9_H */
