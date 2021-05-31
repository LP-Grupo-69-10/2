// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t9.h"
#include "utf8.h"
#include "list.h"

char *t9_map[10] =
  {
   "0",
   "1.?!,;-\'",
   "2AÃÁÀÂBCÇaãáàâbcç",
   "3DEÉÈÊFdeéèêf",
   "4GHIÍghií",
   "5JKLjkl",
   "6MNOÕÓÔmnoõóô",
   "7PQRSpqrs",
   "8TUÚÜVtuúüv",
   "9WXYZwxyz"
  };

int t9_getkey(char *chr) {
  for(int i = 0; i < 10; i++) {
    if(strstr(t9_map[i], chr) != NULL)
      return i;
  }

  return -1;
}

char* t9_string(char *str) {
  char *t9 = malloc(32*sizeof(char));
  int bytes = 0, k = 0;
 
  for(int i = 0; str[i]; i += bytes) {    
    char *cur = next_char(&str[i]);
    t9[k++] = (char)t9_getkey(cur) + '0';
    
    bytes = strlen(cur);
  }

  t9[k] = '\0';
  
  return t9;
}

list t9_find(hash_table table, char *t9) {
  list l = table[hash(t9)];
  list out = new_list();

  while((l = l->next) != NULL) {
    char *temp = t9_string(l->key->str);
    
    if(strcmp(temp, t9) == 0) {
      insert_word(out, l->key);
    }
    
    free(temp);
  }
  
  return out;
}

void t9_autocomplete_limited(hash_table table, char *t9, list out, int max_len) {
  int len = strlen(t9);
  if(len > max_len) return;

  list temp = t9_find(table, t9);
  while((temp = temp->next) != NULL) {
    insert_word(out, temp->key);
  }
  free(temp);
  
  for(int i = '1'; i <= '9'; i++) {
    t9[len] = i;      
    t9_autocomplete_limited(table, t9, out, max_len);
    t9[len] = '\0';
  }
}

list t9_autocomplete(hash_table table, char *t9) {
  int len = strlen(t9), d;
  list out = new_list();

  for(d = 0; d <= 4 && out->next == NULL; d++) {
    t9_autocomplete_limited(table, t9, out, len+d);
  }
  
  // check for better word in next level
  list temp = new_list();
  t9_autocomplete_limited(table, t9, temp, len+d);
  while(temp->next != NULL) {
    temp = temp->next;
    if(temp->key->freq < out->next->key->freq) {
      break;
    } else {
      insert_word(out, temp->key);
    }
  }
  free(temp);
  
  // set list to be circular
  temp = out;
  while(temp->next != NULL) {
    temp = temp->next;
  }
  temp->next = out->next;
  out = out->next;
  
  return out;
}
