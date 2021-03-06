// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"
#include "hash.h"
#include "t9.h"
#include "utf8.h"

hash_table new_table() {
  hash_table table = (hash_table)malloc(M * sizeof(struct node));
  for(int i = 0; i < M; i++)
    table[i] = new_list();
  
  return table;
}

int hash(char *str) {
  int sum = 0;

  for(int i = 0; str[i]; i++) {
    sum = (sum*11 + str[i] - '0') % M;
  }

  return sum;
}

void insert_table(hash_table table, char *str) {
  char *t9 = t9_string(str);
  insert_str(table[hash(t9)], str);
  free(t9);
}
