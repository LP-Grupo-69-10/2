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

char *t9_map[10] =
  {
   "0",
   "1",
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
  char *t9 = malloc(20*sizeof(char));
  int bytes = 0, k = 0;

 
  for(int i = 0; str[i]; i += bytes) {
    char *cur = next_char(&str[i]);
    t9[k++] = (char)t9_getkey(cur) + '0';
    
    bytes = strlen(cur);
  }

  t9[k] = '\0';
  
  return t9;
}

int t9_find(hash_table table, char *t9) {
  int flag = 0;
  list l = table[hash(t9)];

  while((l = l->next) != NULL) {
    char *temp = t9_string(l->key->str);
    
    if(strcmp(temp, t9) == 0) {
      printf("%s ", l->key->str);
      flag = 1;
    }
    
    free(temp);
  }
  
  return flag;
}

void t9_autocomplete(hash_table table, char *t9) {
  int n = strlen(t9), k = 0, found = -1;
  
  char extended[600][20];
  int depth[600];
  strcpy(extended[k], t9);
  depth[k++] = 0;
  
  for(int i = 0; i < k; i++) {
    if(found != -1 && depth[i] > found) {
      return;
    }
        
    if(t9_find(table, extended[i])) {
      printf("-> %s\n", extended[i]);
      found = depth[i];
    }
    
    else if (found == -1) {
      if(depth[i] == 3) continue;
      
      for(char ch = '2'; ch <= '9'; ch++) {
	strcpy(extended[k], extended[i]);
	extended[k][n+depth[i]] = ch;
	extended[k][n+depth[i]+1] = '\0';
	depth[k] = depth[i]+1;
	k++;
      }
    }
  }
}
