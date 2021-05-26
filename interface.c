#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include "libs/utf8.h"

/* Widgets */
GtkWidget *window, *vbox, *label, *grid, *check;
GtkWidget *btns[12];

/* Predictive flag */
gint predictive = 1;

/* Last button pressed variables */
gint64 time_pressed = 0;
int last_pressed = -1;
int text_index = 0;
int last_chrlen;

/* Buttons variables */
char *values[]  = {"1","2","3","4","5","6","7","8","9","N","0","D"};
char *names[]   = {"1","   2\nABC","   3\nDEF","   4\nGHI","  5\nJKL",
                   "    6\nMNO","     7\nPQRS","   8\nTUV",
                   "     9\nWXYZ","Next","0","Delete"};
char *text[]    = {",.?!;","abcABCãáàâçÃÁÀÂÇ2","defDEFéèêÉÈÊ3",
                   "ghiGHIíÍ4","jklJKL5","mnoMNOõóôÕÓÔ6","pqrsPQRS7",
		   "tuvTUVúüÚÜ8","wxyzWXYZ9"};

/* Toggle predictive text */
void change_state(GtkWidget *widget, gpointer *data) {
  predictive = !predictive;
  gtk_label_set_text((GtkLabel*)label, "\0");
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

void button_clicked(GtkWidget *widget, gpointer *data) {
  int key = get_key((char*)data);
  gint64 now = g_get_real_time();
  
  char *str = (char*)gtk_label_get_text((GtkLabel*) label);
  int size = strlen(str);
  
  /* Next word */
  if(key == 9) {
    if(predictive) {
      
    }
  }

  /* Accept word */
  else if(key == 10) {
    
  }
  
  /* Delete */
  else if(key == 11) {
    if(size > 0) {
      while(utf8_luggage(str[--size])); /* juicy juicy code */
      str[size] = '\0';
    }
  }

  /* Pontuation */
  else if(key == 0) {
    if(last_pressed == key && now - time_pressed <= 10e5) {
      text_index = (text_index + 1) % strlen(text[key]);
      str[size-1] = text[key][text_index];
    }    
    else {
      text_index = 0;
      str[size] = text[key][text_index];
      str[size+1] = '\0';
    }
  }
  
  /* Letters */
  else {
    if(!predictive) {      
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
    
    else {
      strcat(str, (char*)data);
    }
  }

  last_pressed = key;
  time_pressed = now;
  
  const char *format = "<span foreground=\"grey\" size=\"xx-large\">%s</span>";
  char *markup;
  
  markup = g_markup_printf_escaped (format, str);
  gtk_label_set_markup(GTK_LABEL (label), markup);
  g_free (markup);
}

int main (int argc, char *argv[]) {
  /* Window init */
  gtk_init(&argc, &argv);
  
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
  
  /* Label */
  label = gtk_label_new(NULL);
  gtk_widget_set_size_request(label, 300, 200);
  
  /* Buttons */
  grid = gtk_grid_new();

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      int k = i*3 + j;
      btns[k] = gtk_button_new_with_label(names[k]);
      gtk_grid_attach(GTK_GRID(grid), btns[k], j, i, 1, 1);
      gtk_widget_set_size_request(btns[k], 100, 60);
      g_signal_connect(G_OBJECT(btns[k]), "clicked",
		       G_CALLBACK(button_clicked), values[k]);
    }
  }

  /* Pack widgets */
  gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), check, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), grid,  TRUE, TRUE, 0);
  gtk_container_add (GTK_CONTAINER(window), vbox);

  /* Show */
  gtk_widget_show_all(window);

  /* Main loop */
  gtk_main();
  
  return 0;
}
