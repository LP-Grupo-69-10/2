#include<gtk/gtk.h>

GtkWidget *window, *fixed, *vbox, *label;
GtkWidget *btns[12];
  
char *values[] = {"1","2","3","4","5","6","7","8","9","0","0","0"};
char *strings[] = {"1","   2\nABC","   3\nDEF","   4\nGHI","  5\nJKL","    6\nMNO","     7\nPQRS","   8\nTUV","     9\nWXYZ","Next","0","Delete"};

void button_clicked (GtkWidget *widget, gpointer *data) {
  g_print("%s", (char*)data);
  gtk_label_set_text((GtkLabel*) label, (char*)data);
}

int main (int argc, char *argv[]) {
  gtk_init(&argc, &argv);
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 450);
  gtk_window_set_title(GTK_WINDOW(window), "T9");
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  
  vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);

  fixed = gtk_fixed_new();
  gtk_container_add(GTK_CONTAINER(window), fixed);

  label = gtk_label_new(NULL);
  
  // Buttons
  for(int i = 0; i < 12; i++) {
    btns[i] = gtk_button_new_with_label(strings[i]);
    gtk_fixed_put(GTK_FIXED(fixed), btns[i],
		  100*(i%3), 150+(i/3)*75);
    gtk_widget_set_size_request(btns[i], 100, 75);
    g_signal_connect(G_OBJECT(btns[i]), "clicked",
		     G_CALLBACK(button_clicked), values[i]);
      }
  
  //g_signal_connect(G_OBJECT(btn_delete), "delete_event",G_CALLBACK(), NULL);
  
  g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);
  
  gtk_widget_show_all(window);

  gtk_main();
  
  return 0;
}
