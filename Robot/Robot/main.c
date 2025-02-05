#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include "callbacks.h"

/*================================================
 * Macro constantes on d�finit la table 
 *===============================================*/

#define NB_COLS 18
#define NB_ROWS 12

typedef struct robot {
  int x, y  ;  /* Position */
  int dx, dy ; /* Deplacement */
} *robot ;

/*================================================
 * Variables globales
 *===============================================*/

GtkImage  *G_images[NB_ROWS][NB_COLS] ;
GdkPixbuf *G_pixbuf_terrain ;
GdkPixbuf *G_pixbuf_terrain_rob ;
GdkPixbuf *G_pixbuf_b1 ;
GdkPixbuf *G_pixbuf_b2 ;
GdkPixbuf *G_pixbuf_b3 ;
GdkPixbuf *G_pixbuf_b4 ;
GdkPixbuf *G_pixbuf_zp1 ;
GdkPixbuf *G_pixbuf_zp2 ;
GdkPixbuf *G_pixbuf_zp3 ;
GdkPixbuf *G_pixbuf_zp4 ;
GdkPixbuf *G_pixbuf_chargeur ;
GdkPixbuf *G_pixbuf_rob_chargeur; 


int ax,ay,bx,by,cx,cy,dx,dy,ex,ey,fx,fy,gx,gy,hx,hy,rx,ry;

int   G_idle_timeout = 0; /* ID de l'evenement timeout */
robot G_robot;

void redessiner_grille () ;
void deplacer_robot () ;
gboolean idle_function (gpointer user_data) ;
void start_animation () ;
void stop_animation () ; 
void gauche_animation () ;
void droite_animation () ; 
void haut_animation () ;
void bas_animation () ;
void charge_animation () ;


/*================================================
 * Fonction principale
 *===============================================*/

int main (int argc, char *argv[]) {
  extern GtkBuilder *builder ;
  GtkWindow  *mainwindow ;
  GtkTable   *table ;
  char txt[20] ;
  int i, j ;

  gtk_init (&argc, &argv);

  /* Creer tous les widgets grace au builder GTK */
  
  builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "robot.glade", NULL);
  gtk_builder_connect_signals (builder, NULL);

  /*-- Recuperer les widgets construits par le builder GTK */
  /* On r�cup�re le tableau, puis on r�cup�re les diff�rents boutons/ dans notre cas on veut d�finir un espace, placer les diff�rentes zones*/
  
  mainwindow = GTK_WINDOW (gtk_builder_get_object (builder, "window1"));
  table = GTK_TABLE (gtk_builder_get_object (builder, "table1"));

  /*-- Initialiser les widgets */
  
  /* ouverture fichier / lecture pas a pas*/

  G_pixbuf_terrain = gdk_pixbuf_new_from_file ("../../bin/terrain.png", NULL);
  G_pixbuf_terrain_rob = gdk_pixbuf_new_from_file ("../../bin/terrain_rob.png", NULL) ;
  G_pixbuf_b1 = gdk_pixbuf_new_from_file ("../../bin/b1.png", NULL) ;
  G_pixbuf_b2 = gdk_pixbuf_new_from_file ("../../bin/b2.png", NULL) ;
  G_pixbuf_b3 = gdk_pixbuf_new_from_file ("../../bin/b3.png", NULL) ;
  G_pixbuf_b4 = gdk_pixbuf_new_from_file ("../../bin/b4.png", NULL) ;
  G_pixbuf_zp1 = gdk_pixbuf_new_from_file ("../../bin/zp1.png", NULL) ;
  G_pixbuf_zp2 = gdk_pixbuf_new_from_file ("../../bin/zp2.png", NULL) ;
  G_pixbuf_zp3 = gdk_pixbuf_new_from_file ("../../bin/zp3.png", NULL) ;
  G_pixbuf_zp4 = gdk_pixbuf_new_from_file ("../../bin/zp4.png", NULL) ;
  G_pixbuf_chargeur = gdk_pixbuf_new_from_file ("../../bin/chargeur.png", NULL) ;
  G_pixbuf_rob_chargeur = gdk_pixbuf_new_from_file ("../../bin/rob_chargeur.png", NULL) ;
;

  /* Redimensioner la grille d'agencement */
  gtk_table_resize (table, NB_COLS, NB_ROWS);

  /* Initialisation du tableau comme terrain vide (obstacle et zone non dispos�) */
  
  for (i=0 ; i<NB_ROWS ; i++) {
    for (j=0 ; j<NB_COLS ; j++) {
	
      /* Creer un nouveau GtkImage */
      G_images[i][j] = (GtkImage *)gtk_image_new_from_pixbuf (G_pixbuf_terrain) ;
      
      /* Lui associer une etiquette avec ses coordonnees */
      sprintf (txt, "( %d ; %d )", i, j) ;
      gtk_widget_set_tooltip_text (GTK_WIDGET(G_images[i][j]), txt) ;

      /* Le placer dans la grille d'agencement prevue a cet effet */
      gtk_table_attach_defaults (table, (GtkWidget *)G_images[i][j], j, j+1, i, i+1) ;

    }
  }
 
  /* cr�ation du robot */
  G_robot = (struct robot *) malloc (sizeof (struct robot)) ;
  
   /* Verifier le succes de l'allocation memoire */
  if (G_robot == NULL) {
    perror ("Erreur allocation memoire") ;
    exit (1) ;
  }
  
  /* Coordonnes des zones de prises*/

printf("Donnez les coordonnees x,y de la premiere boite : \n");
	  scanf("%d,%d",&ax,&ay);
printf("Donnez les coordonnees x,y de la deuxieme boite : \n");
	  scanf("%d,%d",&bx,&by);
printf("Donnez les coordonnees x,y de la troisieme boite : \n");
	  scanf("%d,%d",&cx,&cy);
printf("Donnez les coordonnees x,y de la quatrieme boite : \n");
	  scanf("%d,%d",&dx,&dy);

  /*Coordonnees des zones de depose */

printf("Donnez les coordonnees x,y de la premiere depose : \n");
	  scanf("%d,%d",&ex,&ey);
printf("Donnez les coordonnees x,y de la deuxieme depose : \n");
	  scanf("%d,%d",&fx,&fy);
printf("Donnez les coordonnees x,y de la troisieme depose : \n");
	  scanf("%d,%d",&gx,&gy);
printf("Donnez les coordonnees x,y de la quatrieme depose : \n");
	  scanf("%d,%d",&hx,&hy);

	    /*Coordonnees de zone de recharge */

printf("Donnez les coordonnees x,y de la zone de recharge : \n");
	  scanf("%d,%d",&rx,&ry);


/* Initialiser le robot */
  G_robot->x = rx ;
  G_robot->y = ry ;
  G_robot->dx = 1 ;
  G_robot->dy = 1 ;

/* Initialiser la matrice d'affichage */
  redessiner_grille () ;

  gtk_widget_show_all (GTK_WIDGET(mainwindow));

  /* Lancer la boucle GTK */
  gtk_main ();

  /* La boucle GTK est terminee, detruire maintenant tous les widgets */
  g_object_unref (G_OBJECT (builder));

  /* Fin normale du programme */
  return 0;
}

void redessiner_grille () {
  int i, j;
  static char zp1_done = 0 ;
  static char zp2_done = 0 ;
  static char zp3_done = 0 ;
  static char zp4_done = 0 ;
  static char b1_done = 0 ;
  static char b2_done = 0 ;
  static char b3_done = 0 ;
  static char b4_done = 0 ;
  static char deplacement1_done =0;
  static char deplacement2_done=0;
  static char deplacement3_done=0;
  static char deplacement4_done=0;
  static char trajet_fini=0;

  for (i=0 ; i<NB_ROWS ; i++) {
    for (j=0 ; j<NB_COLS ; j++) {
	
	 /* Effacer l'image */
      gtk_image_clear(GTK_IMAGE(G_images[i][j])) ;

	     /* Affiche le robot sur le terrain */
	  if ((i == G_robot->x) && (j == G_robot->y)){
		  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[i][j]), G_pixbuf_terrain_rob) ; }
		
	  else  {gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[i][j]), G_pixbuf_terrain);}  /* Afficher terrain dans l'image (i,j) */
	  
/* ==========Initialisation des images des zones de prise de boite==============*/

	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[ax][ay]), G_pixbuf_b1) ;
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[bx][by]), G_pixbuf_b2) ;
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[cx][cy]), G_pixbuf_b3) ;
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[dx][dy]), G_pixbuf_b4) ;

	  /* ==========Initialisation de l image de charge==============*/

	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[rx][ry]), G_pixbuf_chargeur) ;

	/*=========== Initialisation des zones de deposes des boites=================*/

	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[ex][ey]), G_pixbuf_zp1) ;
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[fx][fy]), G_pixbuf_zp2) ;
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[gx][gy]), G_pixbuf_zp3) ;
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[hx][hy]), G_pixbuf_zp4) ;
	}
	}

  /*boite 1 */

	if ((G_robot->x == ax+1) && (G_robot->y == ay)){ 
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[ax][ay]), G_pixbuf_terrain);
			deplacement1_done=1;}
  
	if (deplacement1_done){
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[ax][ay]), G_pixbuf_terrain);}


	if ((G_robot->x == ex-1) && (G_robot->y == ey)) {
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[ex][ey]), G_pixbuf_b1);
			zp1_done=1;}

	if (zp1_done){gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[ex][ey]), G_pixbuf_b1);}

/* boite 2 */

	if ((G_robot->x == bx+1) && (G_robot->y == by) && (zp1_done)){ 
		 gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[bx][by]), G_pixbuf_terrain);
		deplacement2_done=1;}
  
	if (deplacement2_done){
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[bx][by]), G_pixbuf_terrain);
		b2_done=1;}


	if ((G_robot->x == fx-1) && (G_robot->y == fy) && (b2_done)) {
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[fx][fy]), G_pixbuf_b2);
		zp2_done=1;}

	if (zp2_done){gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[fx][fy]), G_pixbuf_b2);}

/* boite 3*/

	if ((G_robot->x == cx+1) && (G_robot->y == cy) && (zp2_done)){ 
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[cx][cy]), G_pixbuf_terrain);
		deplacement3_done=1;}
  
	if (deplacement3_done){
	  gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[cx][cy]), G_pixbuf_terrain);
		b3_done=1;}


	if ((G_robot->x == gx-1) && (G_robot->y == gy) && (b3_done)) {
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[gx][gy]), G_pixbuf_b3);
		zp3_done=1;}

	if (zp3_done){
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[gx][gy]), G_pixbuf_b3);}

/* boite 4*/

	if ((G_robot->x == dx+1) && (G_robot->y == dy) && (zp3_done)){ 
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[dx][dy]), G_pixbuf_terrain);
		deplacement4_done=1;}
  
	if (deplacement4_done){
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[dx][dy]), G_pixbuf_terrain);
		b4_done=1;}


	if ((G_robot->x == hx-1) && (G_robot->y == hy) && (b4_done)) {
		gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[hx][hy]), G_pixbuf_b4);
		zp4_done=1;}

	if (zp4_done){gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[hx][hy]), G_pixbuf_b4);
	trajet_fini=1;}

/* Aller � la zone de charge */

	if ((G_robot->x == rx) && (G_robot->y == ry)){ 
	gtk_image_set_from_pixbuf (GTK_IMAGE(G_images[rx][ry]), G_pixbuf_rob_chargeur);}

}
	
 char deplacer_robot(robot bot, int dest_x, int dest_y) {
	char res = 0 ;

  /* Deplacer le robot dans la direction en vigueur */

	if (bot->x != dest_x){ 
		res = 1 ;
		if (bot->x > dest_x) {
			bot->x -= bot->dx;
		}
		else if (bot->x < dest_x){
			bot->x += bot->dx;
		}
    }

	if (bot->y != dest_y){
		res = 1 ;
		if (bot->y > dest_y){
			bot->y -= bot->dy;
		}
		else if (bot->y < dest_y){
			bot->y += bot->dy;
		}
	}

	return res ;
}

 gboolean idle_function (gpointer user_data){
  static char boite1_done = 0 ;
  static char zonedepose1_done = 0 ;
  static char boite2_done = 0 ;
  static char zonedepose2_done = 0 ;
  static char boite3_done = 0 ;
  static char zonedepose3_done = 0 ;
  static char boite4_done = 0 ;
  static char zonedepose4_done = 0 ;
  static char trajet_done = 0 ;

  if (!boite1_done) {
	 if (!deplacer_robot (G_robot, ax+1, ay)) {
		 boite1_done = 1 ;}	
  }
  else if (!zonedepose1_done) {
	  if (!deplacer_robot (G_robot, ex-1, ey)) {
			zonedepose1_done = 1 ;
	  }
  }
  else if (!boite2_done) {
	 if (!deplacer_robot (G_robot, bx+1, by)) {
		 boite2_done = 1 ;
	 }
  }
  else if (!zonedepose2_done) {
	  if (!deplacer_robot (G_robot, fx-1, fy)) {
			zonedepose2_done = 1 ;
	  }
  }
  else if (!boite3_done) {
	 if (!deplacer_robot (G_robot, cx+1, cy)) {
		 boite3_done = 1 ;
	 }
  }
  else if (!zonedepose3_done) {
	  if (!deplacer_robot (G_robot, gx-1, gy)) {
			zonedepose3_done = 1 ;
	  }
  }
  else if (!boite4_done) {
	 if (!deplacer_robot (G_robot, dx+1, dy)) {
		 boite4_done = 1 ;
	 }
  }
  else if (!zonedepose4_done) {
	  if (!deplacer_robot (G_robot, hx-1, hy)) {
			zonedepose4_done = 1 ;
	  }
  }
  else if (!trajet_done) {
	  if (!deplacer_robot (G_robot, rx, ry)) {
			trajet_done = 1 ;
	  }
  }
  else {
	  return FALSE ; }
  redessiner_grille () ;
  return TRUE ;
  }

   /* should return FALSE if the source should be removed */
 gboolean idle_function2 (gpointer user_data){

	 if ((G_robot->x == rx) && (G_robot->y == ry)) {
		 return FALSE;}
	 else {
	 deplacer_robot(G_robot,rx,ry);
	 }
	redessiner_grille();
	return TRUE;
 }

void start_animation () {
    if (G_idle_timeout == 0) {
    /* Demander que la fonction idle_function() soit appellee toutes les 200 ms */
	  G_idle_timeout = g_timeout_add (200, (GSourceFunc)idle_function, NULL) ;
	  
	}
}

void stop_animation () {
  if (G_idle_timeout > 0) {
    /* Demander de ne plus appeller la fonction idle_function() toutes les 200 ms */
    g_source_remove(G_idle_timeout) ;
	G_idle_timeout = 0 ;}
}

void gauche_animation () {
	if (G_robot->y - G_robot->dy < 0) { 
		G_robot->y +=0;}
	else{
		deplacer_robot(G_robot,G_robot->x,G_robot->y-1);}
	redessiner_grille();
}

void droite_animation () {
	if (G_robot->y + G_robot->dy >= NB_COLS) { 
		G_robot->y +=0;}
	else {
		deplacer_robot(G_robot,G_robot->x,G_robot->y+1);}
	redessiner_grille();
}

void haut_animation () {
	if (G_robot->x - G_robot->dx < 0) { 
		G_robot->x +=0;}
	else {
		deplacer_robot(G_robot,G_robot->x-1,G_robot->y);}
	redessiner_grille();
}

void bas_animation () {
	if (G_robot->x + G_robot->dx >= NB_ROWS) { 
		G_robot->x +=0;}
	else {
		deplacer_robot(G_robot,G_robot->x+1,G_robot->y);}
	redessiner_grille();
}

void charge_animation () {
	if (G_idle_timeout == 0) {
    /* Demander que la fonction idle_function2() soit appellee toutes les 200 ms */
	  G_idle_timeout = g_timeout_add (1000, (GSourceFunc)idle_function2, NULL) ;
	  
	}
	deplacer_robot(G_robot,rx,ry);
	redessiner_grille();
}
