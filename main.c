// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/t9.h"
#include "libs/utf8.h"
#include "libs/word.h"
#include "libs/list.h"
#include "libs/hash.h"

char *filename = "lusiadas.txt";
char *delim = " .,;?!()[]:\"\n-\'";

void next_word(FILE *fp, char *word) {  
  int i = 1;

  while(strchr(delim, (word[0] = fgetc(fp))) != NULL);
  if(feof(fp)) {
    *word = 0;
    return;
  }
  
  while(strchr(delim, (word[i] = fgetc(fp))) == NULL) i++;
  word[i] = 0;
}

void read_file(hash_table table) {
  FILE *fp = fopen(filename, "r");
    
  while(1) {
    char* word = malloc(20);
    next_word(fp, word);

    if(word[0] == '\0') break;
    insert_table(table, word);
  }

  fclose(fp);
}

int t9_autocomplete(hash_table table, char *t9) {
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

void autocomplete(hash_table table, char *t9) {
  int n = strlen(t9), k = 0, found = -1;
  
  char extended[600][20];
  int depth[600];
  strcpy(extended[k], t9);
  depth[k++] = 0;
  
  for(int i = 0; i < k; i++) {
    if(found != -1 && depth[i] > found) {
      return;
    }
        
    if(t9_autocomplete(table, extended[i])) {
      printf(" -> %s\n", extended[i]);
      found = depth[i];
    }
    
    else if (found == -1) {
      int size = strlen(extended[i]);
      if(depth[i] == 3) continue;
      
      for(char ch = '2'; ch <= '9'; ch++) {
	strcpy(extended[k], extended[i]);
	extended[k][size] = ch;
	extended[k][size+1] = '\0';
	depth[k] = depth[i]+1;
	k++;
      }
    }
    
  }

}

int main() {
  hash_table table = new_table();
  read_file(table);
  
  int p = 0;
  char ch, t9[20] = {0};
  while((ch = getchar()) != '\n') {	
    if(ch == 'D') {
      t9[--p] = '\0';
    } else {
      t9[p++] = ch;
    }

    getchar();
    printf("\e[1;1H\e[2J");

    printf("typed: %s\nsugested:\n", t9);
    autocomplete(table, t9);
  }
  
  return 0;
}
