#include <stdio.h>
#include "packet_capture.h"
void show(ip_list* k);
int main(){
	char* ip;
	ip_list* k =NULL;
	ip = get_ip_list(&k);
	while(1){
	packet_capture(ip,&k);
	
	//printf("%d",is_in("192.168.35.144",k));
	//is_in("192.168.35.144\0",k);
	//show(k);
	}
	return 0;
}
void show(ip_list* k){
	ip_list* horse = k;
	while(horse != NULL){
		printf("%s\n",horse->ip);
		horse = horse->next;
	}
}
