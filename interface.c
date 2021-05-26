#include <gtk/gtk.h>
#include <string.h>

GtkWidget *window, *vbox, *label, *grid, *check;
GtkWidget *btns[12];
gint predictive = 1;
  
char *values[]  = {"1","2","3","4","5","6","7","8","9","N","0","D"};
char *strings[] = {"1","   2\nABC","   3\nDEF","   4\nGHI","  5\nJKL","    6\nMNO","     7\nPQRS","   8\nTUV","     9\nWXYZ","Next","0","Delete"};

void change_state(GtkWidget *widget, gpointer *data) {
  predictive = !predictive;
  gtk_label_set_text((GtkLabel*)label, "\0");
}

void button_clicked(GtkWidget *widget, gpointer *data) {
  char *str = (char*)gtk_label_get_text((GtkLabel*) label);
  
  /* Next word */
  if(strcmp((char*)data, "N") == 0) {
    if(predictive) {
      
    } 
  }

  /* Accept word */
  else if(strcmp((char*)data, "0") == 0) {
    
  }
  
  /* Delete */
  else if(strcmp((char*)data, "D") == 0) {
    int n = strlen(str);
    if(n != 0) {
      str[n-1] = '\0';
    }
  }

  /* Pontuation */
  else if(strcmp((char*)data, "1") == 0) {
    
  }

  /* Letters */
  else {
    strcat(str, (char*)data);
  }
  
  gtk_label_set_text((GtkLabel*)label, str);
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
  gtk_widget_set_size_request(label, 100, 200);

  /* Buttons */
  grid = gtk_grid_new();

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      int k = i*3 + j;
      btns[k] = gtk_button_new_with_label(strings[k]);
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
