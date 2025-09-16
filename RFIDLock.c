#include <gtk/gtk.h>

static void
print_hello(GtkWidget *widget, gpointer data)
{
  g_print("Hello World");

  return;
}

static void
activate (GtkApplication* app, gpointer user_data)
{
  // Declaring variables
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *grid;

  // Create Window, set tittle and set size
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "RFIDLock");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
 
  // Create and setting grid
  grid = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(window), grid);

  // Create and connecting button 1
  button = gtk_button_new_with_label("Button 1");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  // Attaching button 1 in grid
  gtk_grid_attach(GTK_GRID(grid), button, 0, 0, 1, 1);

  // Create and connecting button 2
  button = gtk_button_new_with_label("Button 2");
  g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

  // Attaching button 2 in grid
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);

  // Create and connecting button quit
  button = gtk_button_new_with_label("Quit");
  g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

  // Attaching button quit in grid
  gtk_grid_attach(GTK_GRID(grid), button, 0, 1, 2, 1);


  GtkWidget *menuBar;
  GtkWidget *fileMenu;
  GtkWidget *helpMenu;
  GtkWidget *menuItem;

  menuBar = gtk_menu_bar_new();
  fileMenu = gtk_menu_new();
  helpMenu = gtk_menu_new();
/*  
  menuItem = gtk_menu_item_new_with_label("File");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);

  helpItem = gtk_menu_item_new_with_label("Help");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(menuItem), fileMenu);
  gtk_menu_shell_append(GTK_MENU_SHELL(menuBar), menuItem);
*/


  // Print window
  gtk_window_present(GTK_WINDOW(window));
  
  return;
}

int
main(int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
