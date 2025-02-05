#include <gtk/gtk.h>
#include "callbacks.h"

GtkBuilder *builder;
/*================================================
 * Prototypes de fonction declarees dans main.c
 *===============================================*/

void stop_animation () ;
void start_animation () ; 
void gauche_animation () ;
void droite_animation () ; 
void haut_animation () ;
void bas_animation () ;
void charge_animation () ;
void on_radiobutton_manuel_toggled (GtkObject *object, gpointer user_data) ;
void on_radiobutton_automatique_toggled (GtkObject *object, gpointer user_data);


/*================================================
 * Fonctions callbacks
 *===============================================*/

 G_MODULE_EXPORT void on_window1_destroy (GtkObject *object, gpointer user_data) {
  /* Arreter la boucle d'animation */ 
  stop_animation () ;

  /* Stopper la boucle GTK */
   gtk_main_quit () ;
   }


 G_MODULE_EXPORT void on_button_start_clicked (GtkObject *object, gpointer user_data) {
  start_animation () ;
}

G_MODULE_EXPORT void on_button_stop_clicked (GtkObject *object, gpointer user_data) {
  stop_animation () ; 
}

void on_button_gauche_clicked (GtkObject *object, gpointer user_data) {
	gauche_animation();
}
void on_button_droite_clicked (GtkObject *object, gpointer user_data) {
	droite_animation();
}
void on_button_haut_clicked (GtkObject *object, gpointer user_data) {
	haut_animation();
}
void on_button_bas_clicked (GtkObject *object, gpointer user_data) {
	bas_animation();
}
void on_button_charge_clicked (GtkObject *object, gpointer user_data) {
	charge_animation();
}

G_MODULE_EXPORT void on_radiobutton_automatique_toggled (GtkObject *object, gpointer user_data) {
	GtkToggleButton *t = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"radiobutton_automatique"));
	gboolean val2 = gtk_toggle_button_get_active(t);

	GtkWidget *start = GTK_WIDGET (gtk_builder_get_object (builder, "button_start"));
	GtkWidget *stop = GTK_WIDGET (gtk_builder_get_object (builder, "button_stop"));

if (val2!=0)
	{
		gtk_widget_set_sensitive (start, TRUE);
		gtk_widget_set_sensitive (stop, TRUE);

	}
else {
		gtk_widget_set_sensitive (start, FALSE);
		gtk_widget_set_sensitive (stop, FALSE);
}
}


G_MODULE_EXPORT void on_radiobutton_manuel_toggled (GtkObject *object, gpointer user_data) {
	GtkToggleButton *t1 = GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder,"radiobutton_manuel"));
	gboolean val = gtk_toggle_button_get_active(t1);

	GtkWidget *haut = GTK_WIDGET (gtk_builder_get_object (builder, "button_haut"));
	GtkWidget *bas = GTK_WIDGET (gtk_builder_get_object (builder, "button_bas"));
	GtkWidget *gauche = GTK_WIDGET (gtk_builder_get_object (builder, "button_gauche"));
	GtkWidget *droite = GTK_WIDGET (gtk_builder_get_object (builder, "button_droite"));
	GtkWidget *charge = GTK_WIDGET (gtk_builder_get_object (builder, "button_charge"));

if (val!=0)
	{
		gtk_widget_set_sensitive (haut, TRUE);
		gtk_widget_set_sensitive (bas, TRUE);
		gtk_widget_set_sensitive (gauche, TRUE);
		gtk_widget_set_sensitive (droite, TRUE);
		gtk_widget_set_sensitive (charge, TRUE);

	}
else {
		gtk_widget_set_sensitive (haut, FALSE);
		gtk_widget_set_sensitive (bas, FALSE);
		gtk_widget_set_sensitive (gauche, FALSE);
		gtk_widget_set_sensitive (droite, FALSE);
		gtk_widget_set_sensitive (charge, FALSE);
}
}
