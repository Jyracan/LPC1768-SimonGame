/* Includes ------------------------------------------------------------------- */
#include "globaldefine.h"
#include "global.h"
#include "timer1.h"
//===========================================================//
// Timer1 pour generer un signal de 20ms
//===========================================================//
void T1_Init(void)
{
	TIM_TIMERCFG_Type		Timer_Config_Structure;
  TIM_MATCHCFG_Type		Timer_MatchConfig_Structure;
	
	// Timer0  Initialization
	Timer_Config_Structure.PrescaleOption = TIM_PRESCALE_USVAL;			  //TIM_PRESCALE_USVAL: Prescaleur en micro secondes 		
	Timer_Config_Structure.PrescaleValue	= 1000;							

	TIM_Init(LPC_TIM1, TIM_TIMER_MODE,&Timer_Config_Structure);    //Initialisation du Timer
	 

	// Configuration of Match channels			
  Timer_MatchConfig_Structure.MatchChannel = 1;
	Timer_MatchConfig_Structure.IntOnMatch   = TRUE;		  //Utiliser une interruption quand il y a un Match								
	Timer_MatchConfig_Structure.ResetOnMatch = TRUE;			//Réinitialisation quand il y a un Match								
	Timer_MatchConfig_Structure.StopOnMatch  = FALSE;			//Arrêter la fonction quand il y a un Match					
	Timer_MatchConfig_Structure.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	
	Timer_MatchConfig_Structure.MatchValue = 20;
	TIM_ConfigMatch(LPC_TIM1,&Timer_MatchConfig_Structure);							
	
	
	TIM_Cmd(LPC_TIM1,ENABLE);
	NVIC->ISER[0]=(1<<2);
}
				
void TIMER1_IRQHandler(void){
	cpt_LCD++;
	if(cpt_LCD==5){
		cpt_LCD=0;
		if((((LPC_GPIO0->FIOPIN)>>19)&(0x01)) != tmp_appuie)
		{
			flag_changement=1;
			tmp_appuie=(((LPC_GPIO0->FIOPIN)>>19)&(0x01));
		}
	}
	if(flag_wait!=-1){
		cpt_wait++;
		if(cpt_wait>50*flag_wait)
		{
			cpt_wait=0;
			flag_wait=-1;
			if (etat_partie==1)				//On sait qu'on a attendu 3s que le joueur appuie sur une touche
			{
				etat_partie=2;
				flag_tachejeu=1;
			}
		}
	}
	LPC_TIM1->IR = 0xFFFFFFFF;
}
