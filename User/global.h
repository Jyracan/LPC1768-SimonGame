#include <stdint.h>


// mettez ici toutes les "extern" correspondant aux déclarations contenues dans globadec.h

extern char chaine[30]; // buffer pour l'affichage sur le LCD
extern char chaine2[20];
extern uint16_t touch_x, touch_y ;

extern char highscoreC[20];
extern int score;
extern int flag_highscore;
extern uint8_t highscore[1];

extern uint8_t tab_seq[50];
extern int taille_seq;

extern int freq;
extern int cpt_note;
extern int cpt_LCD;
extern int flagtacheclavier;
extern int flagcouleur;
extern int flagfin;

extern int flag_changement;
extern int tmp_appuie;
extern int cpt_wait;
extern int flag_wait;

// variables pour gérer la tache Son
extern int flagtacheson;
extern int etat_son;

extern int flag_partieencours;
extern int flag_tachejeu;
extern int etat_partie;
