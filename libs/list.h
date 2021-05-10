// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#ifndef LIST_H
#define LIST_H

typedef struct node_ *list;
typedef struct node_ {
  wchar_t *word;
  int      freq;
  list     next;
} node;

void insert(list, wchar_t*, int);
void print_list(list);

#endif /* LIST_H */
