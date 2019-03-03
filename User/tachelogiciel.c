#include "tachelogiciel.h"

void tache_clavier()
{
  	touch_read();
		if(touch_x>600 & touch_x<2000 & touch_y>2000 & touch_y<3000)
			{
				flagcouleur=1;
			}
		else if(touch_x>600 & touch_x<2000 & touch_y>700 & touch_y<1800)
			{
				flagcouleur=3;
			}
		else if(touch_x>2100 & touch_x<3600 & touch_y>2000 & touch_y<3000)
			{
				flagcouleur=2;			
			}
		else if(touch_x>2100 & touch_x<3600 & touch_y>700 & touch_y<1800)
			{
				flagcouleur=4;
			}
		if (etat_partie==1)
		{
			flag_tachejeu=1;
		}
}
  
void tache_son()
{
	int i;
	switch(etat_son)
	{
		case 0: TIM_Cmd (LPC_TIM0, DISABLE);
						break;
		case 1: //jouer une note
						TIM_Cmd (LPC_TIM0, ENABLE);
						switch(flagcouleur)
						{
							case 1: freq=LA;
											break;
							case 2: freq=RE;
											break;
							case 3: freq=SOL;
											break;
							case 4: freq=DO;
											break;
						}
						break;
		case 2:  //jouer une séquence de note
						
      			for(i=0;i<taille_seq;i++)
						{
							TIM_Cmd (LPC_TIM0, ENABLE);	//On lance le son
							toucheCouleur(tab_seq[i]);
							switch(tab_seq[i])
							{
								case 1: freq=LA;
												break;
								case 2: freq=RE;
												break;
								case 3: freq=SOL;
												break;
								case 4: freq=DO;
												break;
							}
							flag_wait=1;	//On dit que qu'on veut attendre 1s
							while(flag_wait!=-1){}	//On attends que les 1s passent
							TIM_Cmd (LPC_TIM0, DISABLE);	//On coupe le son
						
							if(i!=taille_seq-1){   //après la dernière note on attend 1 sec
								flag_wait=1;
								while(flag_wait!=-1){}	//On attends que les 1s passent
							}
							toucheCouleurInv(tab_seq[i]);
							
						}
							flagcouleur=-1;	//On a joué notre séquence on attends que le joueur appuie sur une touche.
							flag_wait=3;	//On vas attendre 3s que l'utilisateur appuie !
							LPC_GPIO0->FIOCLR = (1<<3); //On allume la led lorsque l'on peut jouer
							etat_partie=1;
							break;
	  	}
	flagtacheson=0;
}

void tache_jeu()
{
	switch(etat_partie)
	{
		case 0: //Ajout d'une note
			ajout_note();		//Appele une procédure qui incrémente la taille de la séquence et génère un entier entre 1 et 4
			etat_son=2;	
			flagtacheson=1;
			break;
		
		case 1: // Analyse de la touche	
			if(flagcouleur!=-1)	//Si le flagcouleur à changé
			{
				if(flagcouleur==tab_seq[score])	//Si le flagcouleur correspond
				{
					score++;                     //Score actuel
					if(score==taille_seq)
					{
						etat_partie=0;
						score=0;
						LPC_GPIO0->FIOSET |= (1<<3);//On éteind la led
					}
					flagcouleur=-1;
					cpt_wait=0;
				}
				else	//On perds pour avoir appuyé sur la mauvaise touche
				{
					perdu();
				}
			}
			break;
		case 2: //perdre la partie
			perdu();
	}
	flag_tachejeu=0;
}
	
void toucheCouleur(int n){  //contour de la note en blanc
						switch(n)
						{
							case 1: dessiner_rect(10,60,110,110,2,1,White,Yellow);
											break;
							case 2: dessiner_rect(120,60,110,110,2,1,White,Green);
											break;
							case 3: dessiner_rect(10,170,110,110,2,1,White,Blue);
											break;
							case 4: dessiner_rect(120,170,110,110,2,1,White,Red);
											break;
						}
}

void toucheCouleurInv(int n){  //contour de la note en noir
						switch(n)
						{
							case 1: dessiner_rect(10,60,110,110,2,1,Black,Yellow);
											break;
							case 2: dessiner_rect(120,60,110,110,2,1,Black,Green);
											break;
							case 3: dessiner_rect(10,170,110,110,2,1,Black,Blue);
											break;
							case 4: dessiner_rect(120,170,110,110,2,1,Black,Red);
											break;
						}
}


void ajout_note()
{	
	tab_seq[taille_seq]=(cpt_note%4)+1;
	taille_seq++;
}

void perdu()
{
	LPC_GPIO0->FIOSET |= (1<<3); //On éteind la led 
	
	i2c_eeprom_read(LPC_I2C0,0,highscore,1); //adresse 0, 1 valeur
	if(taille_seq>highscore[0]){
		highscore[0] = (uint8_t) taille_seq;
		i2c_eeprom_write(LPC_I2C0,0,highscore,1); //on écrit le highscore
		i2c_eeprom_write(LPC_I2C0,100,tab_seq,highscore[0]); //ainsi que sa séquence
		}
	
	TIM_Cmd (LPC_TIM0, DISABLE);	//On coupe le son
	taille_seq=0;
	flag_partieencours=0;
	dessiner_rect(0,0,240,320,2,1,Black,Black);
	sprintf(chaine,"---- GAME OVER ----");
	LCD_write_english_string(45,160,chaine,Green,Black);
	flag_wait=6;	//On dit que qu'on veut attendre 6s
	while(flag_wait!=-1){}	//On attends que les 6s passent...
	afficher_menu(); // init menu
	
}

void jouer_highscore()
{
	int i;
	i2c_eeprom_read(LPC_I2C0,0,highscore,1);
	i2c_eeprom_read(LPC_I2C0,100,tab_seq,highscore[0]);
	
	for(i=0;i<highscore[0];i++) //on joue la séquence
	{
		TIM_Cmd (LPC_TIM0, ENABLE);	//On lance le son
			switch(tab_seq[i])
					{
					case 1: freq=LA;
									break;
					case 2: freq=RE;
									break;
					case 3: freq=SOL;
									break;
					case 4: freq=DO;
									break;
							}
		flag_wait=1;	//On attend 1s
		while(flag_wait!=-1){}	
		TIM_Cmd (LPC_TIM0, DISABLE);	//On coupe le son
		flag_wait=1;	//On attend 1s
		while(flag_wait!=-1){}	
	}
}
  //==========================================================================//
 //                     Procédures d'affichage                        	     //
//==========================================================================//

void afficher_jeu()  	// affichage de l'écran maitre
{
  sprintf(chaine,"*-*-Jeu Simon-*-* ");
	LCD_write_english_string(50,30,chaine,White,Blue2);  //Décalaqe à droite/ Décalaqe vers le bas  /couleur du text / couleur du fond
	dessiner_rect(10,60,110,110,2,1,Black,Yellow);
	dessiner_rect(120,60,110,110,2,1,Black,Green);
	dessiner_rect(10,170,110,110,2,1,Black,Blue);
	dessiner_rect(120,170,110,110,2,1,Black,Red);
}

void afficher_menu()
{
	dessiner_rect(0,0,240,320,2,1,Blue2,Blue2);
	sprintf(chaine,"*-*-Jeu Simon-*-* ");
	LCD_write_english_string(50,30,chaine,White,Blue2);
	sprintf(chaine2,"--Jouer--");
	LCD_write_english_string(80,160,chaine2,White,Blue2);
  i2c_eeprom_read(LPC_I2C0,0,highscore,1); //adresse 0, 1 valeur
	sprintf(highscoreC,"High Score: %d ",highscore[0]);
  LCD_write_english_string(60,300,highscoreC,White,Blue2);
	
}
