/* Includes ------------------------------------------------------------------- */
#include "globaldefine.h"
#include "global.h"
#include "timer0.h" 
/*
Iniatilisation d'un timer qui va nous partir en interruption toute les 50us avec une précision de 1us.
*/
 
void T0_Init(void)
{
    //CONFIGURATION DU PRESCALER
    TIM_TIMERCFG_Type cfg_timer;
    TIM_MATCHCFG_Type cfg_match;
    cfg_timer.PrescaleOption = TIM_PRESCALE_USVAL;    //On dit que l'unité du prescaler est la ms
    cfg_timer.PrescaleValue = 1; // On met le prescaler à 1us
    
    //CONFIGURATION DU MACTH REGISTER
 
    cfg_match.MatchChannel=0;    //On se met sur MR0
    cfg_match.IntOnMatch=ENABLE;    //On autorise les interruptions sur le timer
    cfg_match.StopOnMatch=DISABLE;    //On ne doit pas stop le timer quand match  
    cfg_match.ResetOnMatch=ENABLE;    //On reset quand on match
    cfg_match.ExtMatchOutputType=TIM_EXTMATCH_NOTHING;    //Pas de match extérieur car en mode timer
    cfg_match.MatchValue=49;    //On met le match toute les 50 us

    //CONFIGURATION DU TIMER
    TIM_Init(LPC_TIM0, TIM_TIMER_MODE,& cfg_timer);    //On initialise le timer 0 en mode timer avec la conf faîtes au dessus
    TIM_ConfigMatch(LPC_TIM0,& cfg_match);        //On config le timer en interruption à chaque fois qu'on match !
		NVIC->ISER[0]|=(1<<1);			//On dis au processeur qu'il va devoir gérer le timer en interruption
}
/*
	Interruption pour le timer 0, à chaque fois que le timer 0 part en interruption, on va incrémenter cpt_note, quand le compteur de note à été incrémenter suffisament de fois, on va changer la valeur sur 
la
*/
void TIMER0_IRQHandler (void)
{
	cpt_note++;
	if (cpt_note*freq*5>= 100000) //On regarde si on a fait suffisament de match pour arriver à la fréquence diviser par deux 
	{
		cpt_note=0;
		if ((((LPC_GPIO1->FIOPIN)>>9)&(0x01)) == 1)
		{
			LPC_GPIO1->FIOPIN &= ~ (1<<9);	//On met un 0 en position 9
		}
		else
		{
			LPC_GPIO1->FIOPIN |=(1<<9);	//On met un 1 en position 9
		}
	}
	LPC_TIM0->IR = 0xFFFFFFFF;	//On fait l'acquitement
}
