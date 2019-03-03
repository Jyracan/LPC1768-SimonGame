#include "globaldefine.h"
#include "global.h"
#include <stdlib.h>
#include "constantes.h"
#include <time.h>
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"

void tache_clavier(void);
void tache_son(void);
void ajout_note(void);
void tache_jeu(void);

void afficher_jeu(void);
void afficher_menu(void);
void toucheCouleur(int);
void toucheCouleurInv(int);
void perdu(void);
void jouer_highscore(void);