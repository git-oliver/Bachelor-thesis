#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>

#define MAX_LEN_BUFFER          128
#define AUTO_PORT               8888
#define AP1_PORT                1001
#define AP2_PORT                1002
#define AP3_PORT                1003
#define AP4_PORT                1004 

#define CODE_MESSUNG		((uint8_t)('A'))	//Den lautsprecher an machen zu einer bestimmten uhrzeit
#define CODE_NOP                ((uint8_t)('B'))	//Einfach ein SERVER_RESPONSE senden
#define CODE_ZEIT_SYNC          ((uint8_t)('C'))	//von PTP die SYNC_MSG
#define CODE_SERVER_RESPONSE	((uint8_t)('D'))	//ACK vom SERVER
#define CODE_ZEIT_FOLLOW_UP     ((uint8_t)('D'))	//von PTP die FOLLOW_UP MSG
#define CODE_ZEIT_DELAY_REQ     ((uint8_t)('E'))	//von PTP die DELAY_REQ MSG
#define CODE_ZEIT_DELAY_RESP    ((uint8_t)('F'))	//von PTP die DELAY_RESP MSG
#define CODE_READ_T1_T2_T4	((uint8_t)('G'))	//Lesen von den Werten vom Server aus PTP

struct msg_wireless{
       
	int port;
        uint8_t cmd;
	uint32_t systime;

	int32_t data;

	//Future
	uint32_t array[5];
	uint8_t len_array;
};
typedef struct msg_wireless msgw_t;

struct time_values{

	uint32_t t0;
	uint32_t t1;
	uint32_t t2;
	uint32_t t3;
	uint32_t t4;
};
typedef struct time_values time_values;




double calc_average(double data[], int len);

#endif
