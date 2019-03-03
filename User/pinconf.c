
#include "globaldefine.h"
#include "global.h"
#include "pinconf.h"

void pin_Configuration(void)
{
  // déclaration des structures de configuration
	PINSEL_CFG_Type configLED;
	PINSEL_CFG_Type configHP;
	PINSEL_CFG_Type configMem1;
	PINSEL_CFG_Type configMem2;
	
// configuration des GPIOsdirectement dans les registres
	// Haut parleur
  LPC_GPIO1->FIODIR |= (1<<9);

	// LED
  LPC_GPIO0->FIODIR |= (1<<3);
	LPC_GPIO0->FIOSET |= (1<<3); //On éteind la led 
// configuration des pinsel
	
	configHP.Portnum = PINSEL_PORT_1;
	configHP.Pinnum =PINSEL_PIN_9;
	configHP.Funcnum = PINSEL_FUNC_0;
	configHP.Pinmode =PINSEL_PINMODE_PULLUP;
	configHP.OpenDrain = PINSEL_PINMODE_NORMAL;
  PINSEL_ConfigPin(&configHP);
	
	configLED.Portnum = PINSEL_PORT_0;
	configLED.Pinnum =PINSEL_PIN_3;
	configLED.Funcnum = PINSEL_FUNC_0;
	configLED.Pinmode =PINSEL_PINMODE_PULLUP;
	configLED.OpenDrain = PINSEL_PINMODE_NORMAL;
  PINSEL_ConfigPin(&configLED);
 

	configMem1.Portnum = PINSEL_PORT_0;
	configMem1.Pinnum =PINSEL_PIN_27;
	configMem1.Funcnum = PINSEL_FUNC_1;
	configMem1.Pinmode =PINSEL_PINMODE_PULLUP;
	configMem1.OpenDrain = PINSEL_PINMODE_NORMAL;
  PINSEL_ConfigPin(&configMem1);
	
	configMem2.Portnum = PINSEL_PORT_0;
	configMem2.Pinnum =PINSEL_PIN_28;
	configMem2.Funcnum = PINSEL_FUNC_1;
	configMem2.Pinmode =PINSEL_PINMODE_PULLUP;
	configMem2.OpenDrain = PINSEL_PINMODE_NORMAL;
  PINSEL_ConfigPin(&configMem2);
	
}
