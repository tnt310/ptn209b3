#include "param.h"
#include "eeprom.h"

uint8_t PARAM[EEP_MAX_SIZE];
/*
 * Brief: Load stored data from EEPROM to RAM
 *
 *
 * */
//	DevAddress: specifies the slave address to be programmed (EEPROM ADDRESS).
//	MemAddress: Internal memory address (WHERE YOU WANNA WRITE TO).
//	pData: Pointer to data buffer.
//` TxBufferSize: Amount of data you wanna Write.

void v_epr_load(uint16_t usAdr) {
	uint8_t err;
	if (usAdr == PARAM_LOAD_ALL) {
		err = at24_read_bytes(AT24_ADR, 0x00, PARAM, EEP_MAX_SIZE);
		/*Load all value in Eeprom to RAM*/
//		for (uint8_t funcID = 0; funcID < PARAM_MAX_SIZE; funcID++) {
//			err = at24_read_bytes(AT24_ADR, U_PARAM[funcID].uAdr,
//					&PARAM[U_PARAM[funcID].uAdr], U_PARAM[funcID].uLen);
			if (err == 0) {
				printf("Read TimeOut \r\n");
			}
//		}
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
		/*Store all value in Eeprom to RAM*/
//		for (uint8_t funcID = 0; funcID < PARAM_MAX_SIZE; funcID++) {
//			err = at24_write_bytes(AT24_ADR, U_PARAM[funcID].uAdr,
//					&PARAM[U_PARAM[funcID].uAdr], U_PARAM[funcID].uLen);
//			if (err == ERR_TIMEOUT) {
//				printf("Write TimeOut \r\n");
//				break;
//			}
//		}
//		at24_write_bytes(AT24_ADR, NODE_HAVE_PARAM_ADR,
//				&PARAM[NODE_HAVE_PARAM_ADR], 8);
//
//		at24_write_bytes(AT24_ADR, NODE_LRWAN_DEVEUI_ADR,
//				&PARAM[NODE_LRWAN_DEVEUI_ADR], 8);
//		at24_write_bytes(AT24_ADR, NODE_LRWAN_APPKEY_ADR,
//				&PARAM[NODE_LRWAN_APPKEY_ADR], 16);
//		at24_write_bytes(AT24_ADR, NODE_LRWAN_APPEUI_ADR,
//				&PARAM[NODE_LRWAN_APPEUI_ADR], 16);

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
//		v_epr_load(usAdr);
		return PARAM[usAdr];
	} else
		return 0;
//	return
}

void u_mem_set(uint16_t usAdr, uint8_t uVal) {
	if (usAdr < EEP_MAX_SIZE) {

		PARAM[usAdr] = uVal;
//		v_epr_save(usAdr);
	}

}

