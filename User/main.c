//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2018							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
//===========================================================//

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"

#include "pinconf.h"
#include "globaldefine.h" // fichier contenant toutes les include
#include "globaldec.h" // fichier contenant toutes les déclarations de variables globales
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"

#include "timer1.h"
#include "timer0.h"
#include "tachelogiciel.h"


  //===========================================================//
 //											Function: Main												//
//===========================================================//

int main(void)

{	   
   	pin_Configuration();	// init pinsel LED, HP et I2C0
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		init_i2c_eeprom(LPC_I2C0,ENABLE,500000);// init mémoire
		afficher_menu(); // init menu
		//highscore[0]=0; 
		//i2c_eeprom_write(LPC_I2C0,0,highscore,1);// reset le highscore
	  touch_init(); // init pinsel tactile et init tactile 
	  T1_Init();// init timer 1 (LCD)
		T0_Init();// init timer 0 (note)
		
	  
    while(1){
			if(flag_partieencours==0)  //Zone menu
			{
				if(flag_changement == 1) //actions lors d'un changement d'état au niveau de l'écran tactile
				{
					flag_changement=0;	//On réinitialise le flag changement au cas ou on appuie sur une mauvaise touche
					touch_read();	//On met à jour les variable touch
					if(touch_x>800 & touch_x<3000 & touch_y>1500 & touch_y<2500)	//Si on est dans la zone avec marqué ---Jouer--- alors on lance la partie
					{
						flag_partieencours=1;		//On sort du mode menu
						etat_partie=0;		//La partie commence dans l'état de génération d'une note
						flag_tachejeu=1;	//On appelle la tache jeu
						afficher_jeu();		//On affiche le jeu
						flag_changement=0;
						flagcouleur=-1;
					}
					else if(touch_x>800 & touch_x<3000 & touch_y>0 & touch_y<1000)	//Si on est dans la zone avec marqué High Score alors on joue le highscore
					{
						jouer_highscore();
					}
				}
			}
			
			else //Zone jeu
				{
				if(flag_tachejeu==1)
                                                                                                                                                                                                                                                                                         				{						
					tache_jeu();
				}
				if(flag_changement == 1) //actions lors d'un changement d'état au niveau de l'écran tactil
				{
					if (tmp_appuie==0)  //actions lors de l'appui
					{
						tache_clavier();
						etat_son=1;
						flagtacheson=1;
					}
					else		//actions lors du relachement
					{
						etat_son=0;
						flagtacheson=1;
						flag_tachejeu=1;
					}
					flag_changement=0;
				}
				if(flagtacheson==1)
				{
					tache_son();
				}
			}
		}
}
//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
