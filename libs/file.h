// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef FILE_H
#define FILE_H

#include "hash.h"

void write_tf(hash_table, char*);
void write_wf(word*, char*);
void read_ft(hash_table table, char*);
void load_ft(hash_table table, char*);
void print_file(char*);

#endif /* FILE_H */
