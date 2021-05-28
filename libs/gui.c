// ----------------------------------------------------
// DCC - LP - Teclado T9 – Predictive Text
// ----------------------------------------------------
// Ana Sofia Teixeira - Guilherme Duarte - Miguel Alves
// ----------------------------------------------------

#include <gtk/gtk.h>

#include <string.h>
#include <stdlib.h>

#include "t9.h"
#include "utf8.h"
#include "file.h"

/* Very important */
hash_table table;
char* binname;

/* Widgets */
GtkWidget *window, *vbox, *label_str, *label_t9, *grid, *check;
GtkWidget *btns[12];
GtkWidget *label_btns[12];

/* Predictive flag */
gint predictive = 1;

/* Last button pressed variables */
gint64 time_pressed = 0;
gint last_pressed = -1;
gint text_index = 0;
gint last_chrlen;

/* Buttons variables */
char *values[] = {"1","2","3","4","5","6","7","8","9","N","0","D"};
char *names[]  = {
  "  1\n.?!","   2\nABC","   3\nDEF","   4\nGHI","  5\nJKL",
  "    6\nMNO", "     7\nPQRS","   8\nTUV", "     9\nWXYZ",
  "   *\nNext","     0\nSpace","     #\nDelete"
};
char *text[]   = {
  ".?!,;-\'","abcABCãáàâçÃÁÀÂÇ2","defDEFéèêÉÈÊ3", "ghiGHIíÍ4",
  "jklJKL5","mnoMNOõóôÕÓÔ6","pqrsPQRS7", "tuvTUVúüÚÜ8","wxyzWXYZ9"
};

/* T9 string from predictive text */
char t9[32];
list predicted;

/* Toggle predictive text */
void change_state(GtkWidget *widget, gpointer *data) {
  predictive = !predictive;
  t9[0] = '\0';
  predicted = NULL;
  gtk_label_set_text((GtkLabel*)label_str, "\0");
  gtk_label_set_text((GtkLabel*)label_t9, "\0");
}

/* Get int key by str key */
int get_key(char *str) {
  if(strcmp(str, "N") == 0) {
    return 9;
  }
  
  if(strcmp(str, "0") == 0) {
    return 10;
  }

  if(strcmp(str, "D") == 0) {
    return 11;
  }

  return atoi(str) - 1;
}

/* Updates label_str using multiple clicks to iterate over characters */
void nokia(char *str, int size, int key, gint64 now) {
  if(last_pressed == key && now - time_pressed <= 10e5) {
    text_index = (text_index + last_chrlen) % strlen(text[key]);
    str[size-last_chrlen] = '\0';
  }
  
  else {
    text_index = 0;
  }
  
  int len = utf8_chrlen(&text[key][text_index]);
  char *chr = malloc(len+1);
  strncpy(chr, &text[key][text_index], len);
  chr[len] = '\0';      
  last_chrlen = len;
  
  strcat(str, chr);
  free(chr);
}

/* Function called by the buttons  */
void button_click(GtkWidget *widget, gpointer *data) {
  int key = get_key((char*)data);
  gint64 now = g_get_real_time();
  
  char *str = (char*)gtk_label_get_text((GtkLabel*) label_str);
  int size = strlen(str);
  int t9_size = strlen(t9);

  switch(key) {
    
  case 9:  /* Next word */
    if(predictive && predicted != NULL) {
      predicted = predicted->next;
      str = predicted->key->str;
    }
    break;
    
  case 10: /* Accept word */
    if(size != 0) {
      insert_table(table, str);
      char *temp = t9_string(str);
      word *w = search_list(table[hash(t9_string(str))], str);
      free(temp);
      
      write_wf(w, binname);
    }
    
    *str = *t9 = '\0'; 
    break;
    
  case 11: /* Delete */
    if(size > 0) {
      while(utf8_luggage(str[--size]));
      str[size] = '\0';
    }
    
    if(predictive) {
      t9[t9_size > 0 ? --t9_size : 0] = '\0';
      predicted = t9_size != 0 ? t9_autocomplete(table, t9) : NULL;
      str = predicted == NULL ? "" : predicted->key->str;
    }
    break;
    
  default: /* Letters */
    if(size >= 24 || t9_size >= 24) {
      break;
    }
    
    if(!predictive) {
      nokia(str, size, key, now);
    }
    
    else {
      strcat(t9, (char*)data);
      predicted = t9_autocomplete(table, t9);
      str = predicted == NULL ? "" : predicted->key->str;
    }
    break;
  }
  
  last_pressed = key;
  time_pressed = now;
  
  char *format, *markup;
  format = "<span foreground=\"grey\" size=\"xx-large\">%s</span>";
  markup = g_markup_printf_escaped(format, str);
  gtk_label_set_markup(GTK_LABEL(label_str), markup);

  format = "<span style=\"italic\" foreground=\"dark blue\" size=\"medium\">%s</span>";
  markup = g_markup_printf_escaped(format, t9);
  gtk_label_set_markup(GTK_LABEL(label_t9), markup);
  free(markup);
}

void gui_init(int* argc, char* *argv[], hash_table table_, char* binname_) {
  table = table_;
  binname = binname_;
  
  /* Window init */
  gtk_init(argc, argv);
  
  window = gtk_window_new    (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position    (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
  gtk_window_set_title       (GTK_WINDOW(window), "T9");
  gtk_window_set_resizable   (GTK_WINDOW(window), FALSE);
  g_signal_connect(G_OBJECT(window), "destroy",
		   G_CALLBACK(gtk_main_quit), NULL);

  /* Vbox */
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  /* Check button */
  check = gtk_check_button_new_with_label("inteligente");
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check), TRUE);
  g_signal_connect(G_OBJECT(check), "toggled",
		   G_CALLBACK(change_state), NULL);
  
  /* Labels */
  label_str = gtk_label_new(NULL);
  gtk_widget_set_size_request(label_str, 300, 200);
  label_t9 = gtk_label_new(NULL);
  gtk_widget_set_size_request(label_str, 300, 200);
  
  /* Buttons */
  grid = gtk_grid_new();
  
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      int k = i*3 + j;
      char *format = "<span style=\"italic\" size=\"12000\">%s</span>";
      char *markup = g_markup_printf_escaped(format, names[k]);

      label_btns[k] = gtk_label_new(NULL);	    
      gtk_label_set_markup(GTK_LABEL(label_btns[k]), markup);
      gtk_grid_attach(GTK_GRID(grid), label_btns[k], j, i, 1, 1);
      
      btns[k] = gtk_button_new();
      gtk_grid_attach(GTK_GRID(grid), btns[k], j, i, 1, 1);
      gtk_widget_set_size_request(btns[k], 100, 60);
      g_signal_connect(G_OBJECT(btns[k]), "clicked",
		       G_CALLBACK(button_click), values[k]);

      free(markup);
    }
  }
  
  /* Pack widgets */
  gtk_box_pack_start(GTK_BOX(vbox), label_str, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label_t9, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), check, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), grid,  TRUE, TRUE, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);
  
  /* Show */
  gtk_widget_show_all(window);
}
