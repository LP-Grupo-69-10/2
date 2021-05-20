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
  int h = utf8_strlen(str);
  int sum = 0, bytes = 0;

  for(int i = 0, power = 1; str[i] != '\0'; i += bytes) {
    char *cur = next_char(&str[i]); 
    int t9 = t9_getkey(cur);
       
    sum = (sum + t9 * power) % M;
    bytes = strlen(cur);
    power = (power * 10) % M;
  }
  
  return (h + sum*20) % M;
}

void insert_table(hash_table table, char *str) {
  insert_list(table[hash(str)], str);
}
