#include <stdio.h>
#include <string.h>


typedef struct ip_header
{

    unsigned char header_len : 4;

    unsigned char ver : 4;

    unsigned char tos;

    unsigned short total_len;

    unsigned short id;

    unsigned char frag_offset : 5;

    unsigned char mf : 1;

    unsigned char df : 1;

    unsigned char rz : 1;

    unsigned char frag_offset1;

    unsigned char ttl;

    unsigned char protocol;

    unsigned char cksum;

    struct in_addr src_ip;
    struct in_addr dst_ip;

}IP_HEADER;

typedef struct tcp_header
{

    unsigned short src_port;

    unsigned short dst_port;

    unsigned int seq;

    unsigned int ack;

    unsigned char data_offset;

    unsigned char ns : 1;

    unsigned char reserved : 3;

    unsigned char flag_fin : 1;

    unsigned char flag_syn : 1;

    unsigned char flag_rst : 1;

    unsigned char flag_psh : 1;

    unsigned char flag_ack : 1;

    unsigned char flag_urg : 1;

    unsigned char flag_ece : 1;

    unsigned char flag_cwr : 1;

    unsigned short window;

    unsigned short cksum;

    unsigned short up;

}TCP_HEADER;

typedef struct IP_LIST{
	char ip[15];
	struct IP_LIST *next;
}ip_list;

ip_list* create(char *i){
	ip_list* new_list = (ip_list*)malloc(sizeof(ip_list));
	strcpy(new_list->ip,i);
	new_list->next = NULL;
	return new_list;
}
void add(ip_list** l1,ip_list* l2){
	if((*l1)==NULL){
		*l1 = l2;
	}
	else{
		ip_list* i = (*l1);
		
		while(i->next != NULL){
			i = i->next;
		}
		i->next = l2;
	}
}
void delete(ip_list* a){
	free(a);
}
int is_in(char* a,ip_list* l){
	ip_list* h = l;

	while(h!=NULL){
		if(strncmp(h->ip,a,15)==0){
			return 0;
		}
		h=h->next;
	}
	return 1;
}


