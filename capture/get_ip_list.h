#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h> 
#include <arpa/inet.h> 
#include <stdlib.h>
#include "sql.h"


void get_ip(char **ip);
char* get_lan(char *ip);

char* get_ip_list(ip_list** l) {
	char *ip;
	char *ip_tmp;
	char q[50];
	q[0] = '\0';
	get_ip(&ip);
	ip_tmp = ip;
	ip = strcat(get_lan(ip),";");
	char *query = "delete from dv_list where dv_ip not like ";
	strcat(q,query);
	strcat(q,ip);
	sql_IO(q);
	
	sql_selector("select * from dv_list",l);
	return ip_tmp;
 }

void get_ip(char **ip){
 	struct ifreq ifr; 
	char *ipstr;
	ipstr = (char *)malloc(40);
	int s; 
	s = socket(AF_INET, SOCK_DGRAM, 0); 
	strncpy(ifr.ifr_name, "enp0s3", IFNAMSIZ); 
	if (ioctl(s, SIOCGIFADDR, &ifr) < 0) { 
		printf("Error"); 
	}else{ 
		inet_ntop(AF_INET, ifr.ifr_addr.sa_data+2, ipstr,sizeof(struct sockaddr)); 
		*ip = ipstr;
	}
}
char* get_lan(char *ip){
	char *lan;
	lan = (char *)malloc(12);
	lan[0] = '\'';
	int j = 0;
	int i = 0;
	while(1){
		if(j==3){
			lan[i+1] = '%';
			lan[i+2] = '\'';
			break;
		}
		if(ip[i]=='.'){
			j++;
		}
		lan[i+1] = ip[i];
		i++;
	}
	return lan;
}

