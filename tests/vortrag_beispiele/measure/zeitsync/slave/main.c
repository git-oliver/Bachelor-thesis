#include "../include.h"
#include <stdbool.h>
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include <stdio.h>
#include "net/sock/udp.h"
#include "thread.h"
#include "msg.h"

#define ACCESSPOINT_PORT 	1001

time_values time_value;	//ein object erstellen für t0 -t4

uint32_t time_server, time_client;

//sind nur global weil sonst würde die function client_server hängen
sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
sock_udp_t sock;

void init(void);
msgw_t* server(msgw_t *msg);
int client(msgw_t *msg);
void command_handler(msgw_t *msg);

void cmd_zeit_sync(msgw_t *msg);
void cmd_zeit_follow_up(msgw_t *msg);
void cmd_zeit_delay_req(msgw_t *msg);
void cmd_zeit_delay_resp(msgw_t *msg);
void cmd_read_t1_t2_t4(msgw_t *msg);
void cmd_nop(msgw_t *msg);
void cmd_messung(msgw_t *msg);
void cmd_unknown(void);

int main(void)
{
	msgw_t msg;
	msgw_t* ptr_msg = &msg;
	
	init();
	while(1){
		ptr_msg = server(ptr_msg);
		if(ptr_msg != NULL){
			command_handler(ptr_msg);
		}else{
			printf("ERROR: Funktion server hat ein NULL zurückgegeben");
		}
	}
	return 0;
}

void init(void){

	gpio_init(GPIO_PIN(0,18),GPIO_OUT);
	gpio_clear(GPIO_PIN(0,18));

        local.port = ACCESSPOINT_PORT;
	if(sock_udp_create(&sock, &local, NULL, 0) < 0) {
		printf("Error creating UDP sock\n");
	}
}

int client(msgw_t *msg){

	int returnval;

	sock_udp_ep_t remote = { .family = AF_INET6 };
	remote.port = AUTO_PORT;
 	ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6,IPV6_ADDR_MCAST_SCP_LINK_LOCAL);
	
	msg->port = AUTO_PORT;
	msg->cmd = CODE_SERVER_RESPONSE;
	msg->systime = xtimer_now_usec();

	if ((returnval = sock_udp_send(&sock, msg, sizeof(msgw_t), &remote)) < 0) {

		printf("func. client: Error sending message  %d\n",returnval);
		return returnval;
        }
	time_client = msg->systime;

//	printf("client: haben die nachricht gesendet\n");
	return 0;
}
msgw_t* server(msgw_t *msg){

	sock_udp_ep_t remote;
	ssize_t res;
	
	if ((res = sock_udp_recv(&sock, msg, sizeof(msgw_t), SOCK_NO_TIMEOUT,&remote)) >= 0) {
		time_server = xtimer_now_usec();

/*		printf("server: Haben eine nachricht bekommen res= %d\n",res);
		printf("Alles ausgeben\n");
		printf("port: %d\n",msg->port);
		printf("cmd: %d\n",msg->cmd);
		printf("systime: %ld\n",msg->systime);
		printf("data: %d\n",msg->data);
		printf("array[0]: %ld\n", msg->array[0]);
                printf("array[1]: %ld\n", msg->array[1]);
                printf("array[2]: %ld\n", msg->array[2]);
                printf("array[3]: %ld\n", msg->array[3]);
                printf("array[4]: %ld\n", msg->array[4]);
		printf("len_array: %d\n", msg->len_array);
*/
		return msg;
	}else{
		printf("FAILED  res= %d\n",res);
	}
	return NULL;
}
void command_handler(msgw_t *msg){

//	printf("Sind im Command handler\n");
	switch(msg->cmd){
		case CODE_MESSUNG:
                        {
                              	cmd_messung(msg);
                                break;
                        }
                case CODE_NOP:
                        {
                                cmd_nop(msg);
                                break;
                        }
		case CODE_ZEIT_SYNC:
			{
				cmd_zeit_sync(msg);
				break;
			}
		case CODE_ZEIT_FOLLOW_UP:
			{
				cmd_zeit_follow_up(msg);
				break;
			}
		case CODE_ZEIT_DELAY_REQ:
			{
				cmd_zeit_delay_req(msg);
				break;
			}
		case CODE_ZEIT_DELAY_RESP:
			{
				cmd_zeit_delay_resp(msg);
				break;
			}
		case CODE_READ_T1_T2_T4:
			{
				cmd_read_t1_t2_t4(msg);
				break;
			}
		default:
                        {
                                cmd_unknown();
                                break;
                        }
	}
//	printf("Warte wieder auf eine nachricht\n");
}

void cmd_zeit_sync(msgw_t *msg){

//	printf("Es kam eine SYNC MSG an\n");
	time_value.t1 = time_server;
	client(msg);
}
void cmd_zeit_follow_up(msgw_t *msg){

//	printf("CODE_ZEIT_FOLLOW_UP MSG angekommen\n");
	client(msg);
}
void cmd_zeit_delay_req(msgw_t *msg){

	client(msg);
	time_value.t2 = time_client;
}
void cmd_zeit_delay_resp(msgw_t *msg){

	time_value.t4 = time_server;
	client(msg);
}
void cmd_read_t1_t2_t4(msgw_t *msg){

//	printf("CODE_READ_T1_T2_T4 angekommen\n");
	msg->array[0] = time_value.t1;
	msg->array[1] = time_value.t2;
	msg->array[2] = time_value.t4;
	msg->len_array = 3;
	client(msg);

/*	printf("Alle T-Werte ausgeben\n");
	printf("t1 = %ld\n", time_value.t1);
	printf("t2 = %ld\n", time_value.t2);
	printf("t4 = %ld\n", time_value.t4);
*/
}


void cmd_nop(msgw_t *msg){

        printf("CMD NOP\n");
        msg->data = 0;
        client(msg);
}
void cmd_messung(msgw_t *msg){

//	uint32_t time = xtimer_now_usec();
	
	printf("CMD messung\n");
	printf("Die aktuelle zeit: %ld\n",xtimer_now_usec());

	volatile uint32_t data = msg->data;
	printf("Senden SERVER_RESPONSE: %d\n", client(msg));

	if(data < xtimer_now_usec()){
		printf("ERROR Zeit zum feuern liegt schon in der vergangenheit\n");
		printf("Sende -1 zuück\n");
		msg->data = -1;
		client(msg);
		return;
	}else{
		msg->data = 0;
		client(msg);
	}

	printf("okay wir warten bis wir den ton anmachen: aktuelle Zeit: %ld     ton_an bei: %ld\n",xtimer_now_usec(),data);
	while(1){
		if(xtimer_now_usec() >= data){

			gpio_set(GPIO_PIN(0,18));
			xtimer_usleep(40000);
			gpio_clear(GPIO_PIN(0,18));
			data = xtimer_now_usec() - 40000;
			printf("Lautsprecher wurde an gemacht\n");
			printf("Uhrzeit ca. nach dem feuern: %ld\n",data);
			break;
		}
	}
}
void cmd_unknown(void){

	printf("CMD unknown angekommen\n");
}
