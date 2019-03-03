#include <stdint.h>
#include "lpc17xx_i2c.h"

// mettez ici toutes les déclarations de variables globales

char chaine[30]; // buffer pour l'affichage sur le LCD
char chaine2[20];
uint16_t touch_x, touch_y ;

char highscoreC[20];
int score=0;
int flag_highscore=0;
uint8_t highscore[1];

uint8_t tab_seq[50];   //tableau contenant la séquence des notes à jouer
int taille_seq=0;

int freq=0;
int cpt_note = 0;
int cpt_LCD=0;
int flagcouleur;
//-1 On attends que le joueur appuie
//1	jaune
//2	vert
//3 bleu
//4	rouge

int flag_changement=0;  
int tmp_appuie=1; //on le met à 1 car le port P0.19 est à 1 de base
int cpt_wait=0;
int flag_wait=-1;	//Cette variable vaut -1 quand on a pas besoin d'attendre et n quand on veut attendre n secondes

// variables pour gérer la tache Son
int flagtacheson=0; // pour réveiller la tache Son
int etat_son=0; //variable mémorisant l'état d'avancement de la tache logicielle son

int flag_partieencours=0;
int flag_tachejeu=0;
int etat_partie=0;
//0 Emission d'une séquence
//1 Analyse d'un touche
//2 Perdre la partie
