#include "../include.h"
#include <stdio.h>
#include "net/af.h"
#include "net/protnum.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "xtimer.h"
#include "periph/gpio.h"
#include <inttypes.h>
#include <math.h>
#include "math_stuff.h"

#define DIFFERENCE_TON_ON	(5000000)

sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
sock_udp_t sock;

uint32_t time_client = 0, time_server = 0;//Wann der server eine nachricht bekommen hat
volatile uint32_t time_ISR_microphone = 0;
volatile int i = 0;
volatile int j = 0;
volatile bool flag_microphone = false;

extern double calc_average(double data[],int len);//wenn ich die funktion nicht brauch weglöschen <- ist in include.c drin
msgw_t* client_server_timeout(msgw_t *msg);
double measure_distance(msgw_t *msg, double omega);
void ready_ISR(void);
msgw_t* time_sync(msgw_t *msg);
msgw_t* read_values_time_sync(msgw_t *msg);
circle* calc_verzoegerung(msgw_t *msg, circle *C);
circle* time_sync_for_AP(msgw_t* ptr_msg, circle* C);
void ISR_microphone_pin(void *arg);
double calc_distance(uint32_t server_ton_on, uint32_t time_microphone, double omega);
void init(void);
void handler(void);

int main(void)
{
	init();
	while(1){
		handler();
	}
	return 0;
}


void handler(void){
	
	circle c;
	circle *ptr_circle = &c;

	msgw_t msg;
	msgw_t* ptr_msg = &msg;

	AP1(ptr_msg, ptr_circle);
	AP2(ptr_msg, ptr_circle);
	AP3(ptr_msg, ptr_circle);
}

circle* time_sync_for_AP(msgw_t* ptr_msg, circle* C){
	
	int port = ptr_msg->port;
	
	ptr_msg = time_sync(ptr_msg);
	if(ptr_msg != NULL){
		uint32_t t0,t1, t2, t3, t4;
		t0 = ptr_msg->array[0];
		t3 = ptr_msg->array[1];
		
		ptr_msg->port = port;
		ptr_msg = read_values_time_sync(ptr_msg);
		if(ptr_msg != NULL){
		
			t1 = ptr_msg->array[0];
			t2 = ptr_msg->array[1];
			t4 = ptr_msg->array[2];

			//Einmal alles ordnen für calc_verzögerung
			ptr_msg->array[0] = t0;
			ptr_msg->array[1] = t1;
			ptr_msg->array[2] = t2;
			ptr_msg->array[3] = t3;
			ptr_msg->array[4] = t4;

			//printf("Wir haben jetzt alle werte von der zeit sync...\n");
			//printf("Berechnen jetzt omega und t_prop\n");
			return calc_verzoegerung(ptr_msg, C);
		}
	}
	return NULL;
} 
double measure_distance(msgw_t *msg, double omega){

	uint32_t server_ton_on = 0;

	msg->cmd = CODE_MESSUNG;

	//Das micro scharf schalten
        gpio_irq_enable(GPIO_PIN(1,23));

	//printf("Omega: %f\n", omega);
	
	msg->data= xtimer_now_usec() + DIFFERENCE_TON_ON + omega;
        server_ton_on = msg->data;

	msg = client_server_timeout(msg);
	if(msg == NULL){
		printf("Messung machen: Haben von client_server ein NULL zurückbekommen\n");
		return -1;
	}else{
		if(msg->data < 0){
			printf("ERROR:  Slave kann nicht triggern, weil die Zeit in der Vergangenheit liegt\n");
			return -2;
		}
		server_ton_on = server_ton_on - omega + 14000;//hab einfach den offset hinzugefügt
//		printf("Ich mache den Ton an bei: %ld\n",server_ton_on);
//		printf("Akutelle Zeit           : %ld\n",xtimer_now_usec()); 
		while(1){
			if(xtimer_now_usec() >= server_ton_on){
				gpio_toggle(GPIO_PIN(0,5));
				xtimer_sleep(1);
				printf("Erg = %ld\n", ( server_ton_on));
				return 0.0;
			}
		}
	}
}
double calc_distance(uint32_t server_ton_on, uint32_t time_microphone, double omega){

	double client_ton_on = server_ton_on - omega - DIFFERENCE_TON_ON;
	double result = time_microphone - client_ton_on;
	result *= 0.034;

	printf("===================================\n");
	printf("Ton an server : %ld\n", server_ton_on);
	printf("Ton an client : %f\n", client_ton_on);
	printf("Micro received: %ld\n",time_microphone);

	if(client_ton_on > time_microphone){

		printf("!!!!!!! An sich nicht möglich: client_time > time_microphone <---darf nicht sein\n");
		result = (client_ton_on - time_microphone);
		result *= 0.034;
	}

	printf("zeit_diff: %f ms\n",(time_microphone - client_ton_on)/1000.);
	printf("\nBerechnete Länge: %f [cm]\n", result);
	printf("Andere Länge: %f cm\n",(time_microphone - client_ton_on)/2000.);
        printf("===================================\n");
	ready_ISR();
	return result;//[cm]
}
void ready_ISR(void){
	flag_microphone = false;
	time_ISR_microphone = 0;
}

msgw_t* read_values_time_sync(msgw_t *msg){
	
//	printf("Wir lesen die werte t1, t2 und t4\n");
	msg->cmd = CODE_READ_T1_T2_T4;
	return client_server_timeout(msg);
} 

msgw_t* time_sync(msgw_t *msg){
	
	uint32_t t0,t1,t2,t3,t4;
	//kommt nachher noch raus
	(void)t4;
	(void)t2;
	(void)t1;

	int port = msg->port;
 
//	printf("Es wird ein time_sync gemacht für %d\n", msg->port);

	//Send SYNC_MSG <- wait for ACK
//	printf("SYNC MSG\n");
	msg->port = port;
	msg->cmd = CODE_ZEIT_SYNC;
	msg = client_server_timeout(msg);

	if(msg != NULL){

		t0 = time_client;

		//FOLLOW_UP senden

//		printf("FOLLOW_UP\n");
		msg->port = port;
		msg->cmd = CODE_ZEIT_FOLLOW_UP;
                msg->data = t0;
		msg = client_server_timeout(msg);
	
		if(msg != NULL){

			//Anfrage für DELAY_REQ
//			printf("Sende anfrage damit der slave ein DELAY_REQ sendet\n");
//			printf("DELAY_REQ\n");
			msg->port = port;
			msg->cmd = CODE_ZEIT_DELAY_REQ;
			msg->data = 0;
			msg = client_server_timeout(msg);
			
			if(msg != NULL){
				
//				printf("Antwort für DELAY_REQ ist angekommen\n");
				t3 = time_server;
				
				//DELAY_RESP senden
//				printf("DELAY_RESP\n");
				msg->port = port;
				msg->cmd = CODE_ZEIT_DELAY_RESP;
				msg->data = t3;
				msg = client_server_timeout(msg);

				if(msg != NULL){
//					printf("Zeitsync SUCCESS\n");
//					printf("Array füllen mit t0,t3\n");
					msg->array[0] = t0;
					msg->array[1] = t3;
					return msg;
				}

			}
		}
	}
	return NULL;
}

void init(void){
        
        int returnval = 0;
	(void)returnval;

        local.port = AUTO_PORT;

	if(sock_udp_create(&sock, &local, NULL, 0) < 0) {
		printf("Error creating UDP sock\n");
	}
        gpio_init(GPIO_PIN(1,23),GPIO_IN);
        returnval = gpio_init_int(GPIO_PIN(1,23),GPIO_IN,GPIO_RISING,&ISR_microphone_pin,NULL);
	//DEBUG
	gpio_init(GPIO_PIN(0,18),GPIO_OUT);
	gpio_clear(GPIO_PIN(0,18));

	gpio_irq_disable(GPIO_PIN(1,23)); 
}

void ISR_microphone_pin(void *arg){

	time_ISR_microphone = xtimer_now_usec();
	flag_microphone = true;
	gpio_irq_disable(GPIO_PIN(1,23));
	gpio_clear(GPIO_PIN(0,18));
	(void)arg;
}

circle* calc_verzoegerung(msgw_t *msg, circle *C){

	int32_t t0,t1,t2,t3,t4;
	(void)t4;

	t0 = msg->array[0];
	t1 = msg->array[1];
	t2 = msg->array[2];
	t3 = msg->array[3];
	t4 = msg->array[4];

	C->t_prop = ((t1 - t0) + (t3 - t2)) / 2.;
	C->omega = t1 - t0 - C->t_prop;
	return C;
}
msgw_t* client_server_timeout(msgw_t *msg){

        int returnval;
        ssize_t res;

        sock_udp_ep_t remote = { .family = AF_INET6 };
        remote.port = msg->port;
        ipv6_addr_set_all_nodes_multicast((ipv6_addr_t *)&remote.addr.ipv6,IPV6_ADDR_MCAST_SCP_LINK_LOCAL);

	msg->systime = xtimer_now_usec(); 

        if ((returnval = sock_udp_send(&sock, msg, sizeof(msgw_t), &remote)) < 0) {

                printf("client_server_timeout: Error sending message  %d\n",returnval);
                return NULL;
        }

	time_client = msg->systime;

	if ((res = sock_udp_recv(&sock, msg, sizeof(msgw_t), 3 * US_PER_SEC, &remote)) >= 0) {
		time_server = xtimer_now_usec();
/*		printf("client_server_timeout: Got msg\n");
		printf("port: %d\n", msg->port);
		printf("cmd: %d\n", msg->cmd);
		printf("systime: %ld\n", msg->systime);
		printf("data: %d\n", msg->data);
		printf("len: %d\n", msg->len_array);
		printf("array[0]: %ld\n", msg->array[0]);
                printf("array[1]: %ld\n", msg->array[1]);
                printf("array[2]: %ld\n", msg->array[2]);
                printf("array[3]: %ld\n", msg->array[3]);
                printf("array[4]: %ld\n", msg->array[4]);
*/
		return msg;
        }
	return NULL;
}

