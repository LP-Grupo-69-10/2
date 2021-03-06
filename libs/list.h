#ifndef LIST_H
#define LIST_H

#include "word.h"

typedef struct node *list;
struct node {
  word *key;
  list next;
};

list  new_list();
word* search_list(list, char*);
void  remove_list(list, char*);
void  insert_str(list, char*);
void  insert_word(list, word*);
void  print_list(list);

#endif /* LIST_H */
