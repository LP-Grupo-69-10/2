// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef FILE_H
#define FILE_H

#include "hash.h"

int write_tf(hash_table, char*);
int write_wf(word*, char*);
int read_ft(hash_table table, char*);
int load_ft(hash_table table, char*);

#endif /* FILE_H */
