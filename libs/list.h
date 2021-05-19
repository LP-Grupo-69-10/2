#ifndef LIST_H
#define LIST_H

#include "word.h"

typedef struct node_ *list;
typedef struct node_ {
  word *key;
  list next;
} node;

void insert(list, word*);
void print_list(list);

#endif /* LIST_H */
