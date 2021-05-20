// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include "list.h"

#define M 9011

typedef list *hash_table;

hash_table new_table();
int hash(char*);
void insert_table(hash_table, char*);
