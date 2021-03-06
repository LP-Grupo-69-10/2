// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <gtk/gtk.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/t9.h"
#include "libs/utf8.h"
#include "libs/word.h"
#include "libs/list.h"
#include "libs/hash.h"
#include "libs/file.h"
#include "libs/gui.h"

char *filename = "files/lusiadas.txt";
char *binname  = "files/dicionario.bin";

int main(int argc, char *argv[]) {
  hash_table table = new_table();

  
  if(read_ft(table, binname) != 0) {
    load_ft(table, filename);
    write_tf(table, binname);
  }

  gui_init(&argc, &argv, table, binname);
  gtk_main();
  
  return 0;
}
