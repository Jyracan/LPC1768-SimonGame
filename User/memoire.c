#include "memoire.h"
#define max 50 

void init_i2c_eeprom(LPC_I2C_TypeDef * i2cx,FunctionalState newstate,uint32_t clockrate){
	I2C_Init(i2cx,clockrate);
	I2C_Cmd(i2cx,newstate);
}

void i2c_eeprom_write(LPC_I2C_TypeDef* i2cx,uint16_t addr,uint8_t* data, int length){
	int i;
	I2C_M_SETUP_Type config;
	uint8_t d[max];
	config.retransmissions_max=max;
	config.sl_addr7bit=(1<<6)|(1<<4);
	config.sl_addr7bit|=addr/256;
	addr-=addr/256;
	d[0]=addr;
	for (i=0;i<length;i++){
		d[i+1]=data[i];
	}
	config.tx_data=d;
	config.tx_length=length+1;
	config.rx_data=NULL;
	config.rx_length=0;
	config.retransmissions_count=0;
	I2C_MasterTransferData(i2cx,&config,I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(LPC_I2C_TypeDef* i2cx,uint16_t addr,uint8_t* data, int length){
	int i;
	uint8_t d[max];
	I2C_M_SETUP_Type config;
	config.retransmissions_count=0;
	config.tx_length=1;
	config.retransmissions_max=max;
	config.sl_addr7bit=(1<<6)|(1<<4);
	config.sl_addr7bit|=addr/256;
	addr-=addr/256;
	d[0]=addr;
	for (i=0;i<length;i++){
		d[i+1]=data[i];
	}
	d[0]=addr;
	config.rx_data=d;
	config.tx_data=d;
	config.rx_length=length;
	I2C_MasterTransferData(i2cx,&config,I2C_TRANSFER_POLLING);
	for (i=0;i<length;i++){
	  data[i]=config.rx_data[i];
	}
}