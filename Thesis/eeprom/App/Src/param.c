#include "param.h"
#include "epprom.h"

uint8_t PARAM[EEP_MAX_SIZE];

//PARAM_MAX_SIZE

uParam_t U_PARAM[] = {

		{NODE_HAVE_PARAM_ADR, NODE_MB_DEFAULT_LEN },
		{NODE_ID_ADR,NODE_MB_DEFAULT_LEN },
		{NODE_MB_ID_ADR, NODE_MB_DEFAULT_LEN },
		{NODE_MB_SERCFG_ADR, NODE_MB_DEFAULT_LEN },
		{NODE_MB_MODE_ADR,NODE_MB_DEFAULT_LEN },
		{NODE_MB_BAUD_ADR, NODE_MB_DEFAULT_LEN },
		{NODE_MB_PARTITY_ADR,NODE_MB_DEFAULT_LEN },

		{NODE_NETWORK_IP_ADR, NODE_NETWORK_DEFAULT_LEN },
		{NODE_NETWORK_NETMASK_ADR, NODE_NETWORK_DEFAULT_LEN},
		{NODE_NETWORK_GATEWAY_ADR, NODE_NETWORK_DEFAULT_LEN },
		{NODE_NETWORK_MQTT_ADR, NODE_NETWORK_DEFAULT_LEN },

		{NODE_CHANEL_1_BAUD	, NODE_MB_DEFAULT_LEN },
		{NODE_CHANEL_1_DATABITS,NODE_MB_DEFAULT_LEN },
		{NODE_CHANEL_1_STOPBIT,NODE_MB_DEFAULT_LEN },
		{NODE_CHANEL_1_PARITY,NODE_MB_DEFAULT_LEN },

		{NODE_CHANEL_2_BAUD	, NODE_MB_DEFAULT_LEN },
		{NODE_CHANEL_2_DATABITS,NODE_MB_DEFAULT_LEN },
		{NODE_CHANEL_2_STOPBIT,NODE_MB_DEFAULT_LEN },
		{NODE_CHANEL_2_PARITY,NODE_MB_DEFAULT_LEN },

		{ 0, 0 }

};

/*
 * Brief: Load stored data from EEPROM to RAM
 *
 *
 * */

void v_epr_load(uint16_t usAdr) {
	uint8_t err;
	if (usAdr == PARAM_LOAD_ALL) {
		err = at24_read_bytes(AT24_ADR, 0x00,PARAM,EEP_MAX_SIZE);
		/*Load all value in Eeprom to RAM*/
			if (err == 0) {
				printf("Read TimeOut \r\n");
			}
	} else {
		/*Load the specific adr requested*/
		err = at24_read_bytes(AT24_ADR, usAdr, &PARAM[usAdr],0x01);
		if (err == 0) {
			printf("Read TimeOut \r\n");

		}
	}

}
/*
 * Brief: Store data to Eeprom
 *
 *
 * */

void v_epr_save(uint16_t usAdr) {
	uint8_t err;
	if (usAdr == PARAM_LOAD_ALL) {
		err = at24_write_bytes(AT24_ADR,0x00, PARAM,EEP_MAX_SIZE);
		if (err = 0) {
			printf("Write TimeOut \r\n");
		}
	} else {

		/*Store the specific adr requested*/
		err = at24_write_bytes(AT24_ADR,usAdr, &PARAM[usAdr],0x01);
		if (err = 0) {
			printf("Write TimeOut \r\n");

		}
	}

}
/**/

uint8_t u_mem_get(uint16_t usAdr) {

	if (usAdr < PARAM_MAX_SIZE) {
		return PARAM[usAdr];
	} else
		return 0;
}

void u_mem_set(uint16_t usAdr, uint8_t uVal) {
	if (usAdr < EEP_MAX_SIZE) {
		PARAM[usAdr] = uVal;
	}
}

void u_mem_set_16(uint16_t usAdr, uint16_t uVal) {
	if (usAdr < EEP_MAX_SIZE) {
		PARAM[usAdr] = uVal;
	}
}
