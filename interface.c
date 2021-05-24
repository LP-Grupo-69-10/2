#include<gtk/gtk.h>

GtkWidget *label;

void button_clicked1 (GtkWidget *widget, gpointer data) {
  g_print("1");
  gtk_label_set_text((GtkLabel *) label, "1");

}
void button_clicked2 (GtkWidget *widget, gpointer data) {
  g_print("2");
}
void button_clicked3 (GtkWidget *widget, gpointer data) {
  g_print("3");
}
void button_clicked4 (GtkWidget *widget, gpointer data) {
  g_print("4");
}
void button_clicked5 (GtkWidget *widget, gpointer data) {
  g_print("5");
}
void button_clicked6 (GtkWidget *widget, gpointer data) {
  g_print("6");
}
void button_clicked7 (GtkWidget *widget, gpointer data) {
  g_print("7");
}
void button_clicked8 (GtkWidget *widget, gpointer data) {
  g_print("8");
}
void button_clicked9 (GtkWidget *widget, gpointer data) {
  g_print("9");
}

int main (int argc, char *argv[]) {
  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *vbox;

  GtkWidget *btn0, *btn1, *btn2, *btn3, *btn4, *btn5, *btn6, *btn7, *btn8, *btn9;
  GtkWidget *btn_next, *btn_delete;

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

  btn1 = gtk_button_new_with_label("1");
  gtk_fixed_put(GTK_FIXED(fixed), btn1, 0, 150);
  gtk_widget_set_size_request(btn1, 100, 75);

  btn2 = gtk_button_new_with_label("    2\nABC");
  gtk_fixed_put(GTK_FIXED(fixed), btn2, 100, 150);
  gtk_widget_set_size_request(btn2, 100, 75);

  btn3 = gtk_button_new_with_label("   3\nDEF");
  gtk_fixed_put(GTK_FIXED(fixed), btn3, 200, 150);
  gtk_widget_set_size_request(btn3, 100, 75);

  btn4 = gtk_button_new_with_label("   4\nGHI");
  gtk_fixed_put(GTK_FIXED(fixed), btn4, 0, 225);
  gtk_widget_set_size_request(btn4, 100, 75);

  btn5 = gtk_button_new_with_label("  5\nJKL");
  gtk_fixed_put(GTK_FIXED(fixed), btn5, 100, 225);
  gtk_widget_set_size_request(btn5, 100, 75);

  btn6 = gtk_button_new_with_label("    6\nMNO");
  gtk_fixed_put(GTK_FIXED(fixed), btn6, 200, 225);
  gtk_widget_set_size_request(btn6, 100, 75);

  btn7 = gtk_button_new_with_label("     7\nPQRS");
  gtk_fixed_put(GTK_FIXED(fixed), btn7, 0, 300);
  gtk_widget_set_size_request(btn7, 100, 75);

  btn8 = gtk_button_new_with_label("   8\nTUV");
  gtk_fixed_put(GTK_FIXED(fixed), btn8, 100, 300);
  gtk_widget_set_size_request(btn8, 100, 75);

  btn9 = gtk_button_new_with_label("     9\nWXYZ");
  gtk_fixed_put(GTK_FIXED(fixed), btn9, 200, 300);
  gtk_widget_set_size_request(btn9, 100, 75);

  btn_next = gtk_button_new_with_label("Next");
  gtk_fixed_put(GTK_FIXED(fixed), btn_next, 0, 375);
  gtk_widget_set_size_request(btn_next, 100, 75);

  btn0 = gtk_button_new_with_label("0");
  gtk_fixed_put(GTK_FIXED(fixed), btn0, 100, 375);
  gtk_widget_set_size_request(btn0, 100, 75);

  btn_delete = gtk_button_new_with_label("Delete");
  gtk_fixed_put(GTK_FIXED(fixed), btn_delete, 200, 375);
  gtk_widget_set_size_request(btn_delete, 100, 75);

  g_signal_connect(G_OBJECT(btn1), "clicked", G_CALLBACK(button_clicked1), NULL);
  g_signal_connect(G_OBJECT(btn2), "clicked", G_CALLBACK(button_clicked2), NULL);
  g_signal_connect(G_OBJECT(btn3), "clicked", G_CALLBACK(button_clicked3), NULL);
  g_signal_connect(G_OBJECT(btn4), "clicked", G_CALLBACK(button_clicked4), NULL);
  g_signal_connect(G_OBJECT(btn5), "clicked", G_CALLBACK(button_clicked5), NULL);
  g_signal_connect(G_OBJECT(btn6), "clicked", G_CALLBACK(button_clicked6), NULL);
  g_signal_connect(G_OBJECT(btn7), "clicked", G_CALLBACK(button_clicked7), NULL);
  g_signal_connect(G_OBJECT(btn8), "clicked", G_CALLBACK(button_clicked8), NULL);
  g_signal_connect(G_OBJECT(btn9), "clicked", G_CALLBACK(button_clicked9), NULL);

  //g_signal_connect(G_OBJECT(btn_delete), "delete_event",G_CALLBACK(), NULL);
  g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();
  return 0;
}
