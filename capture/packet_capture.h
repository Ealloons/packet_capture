#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap-inttypes.h>
#include <pcap/pcap.h>
#include <net/ethernet.h>
#include <sys/socket.h>
#include "get_ip_list.h"
int is_lan = 0;
int is_in_list = 0;
int is_danger_port = 0;

char pkt_src[15] = "\0";
char pkt_dst[15] = "\0";
char pkt_src_mac[20] = "\0";
char pkt_dst_mac[20] = "\0";
int pkt_port;

void initializing();
void packet_handler_for_en(const u_char *pkt_data){
    struct ether_header * eh = (struct ether_header *)pkt_data;
    if(is_lan == 0){
    	return;
    }
    char src[20] = "\0";
    char dst[20] = "\0";
    for(int i=0;i<6;i++){
        char s[3] = {0};
        char d[3] = {0};
        sprintf(s,"%02x",eh->ether_dhost[i]);
        sprintf(d,"%02x",eh->ether_shost[i]);
        strcat(src,s);
        strcat(dst,d);
    }
    strcat(pkt_src_mac,src);
    strcat(pkt_dst_mac,dst);
}
void packet_handler_for_ip(const u_char *pkt_data,char* ipp,ip_list** l){
    IP_HEADER * ip;
    ip = (IP_HEADER *)pkt_data;
    
    strcat(pkt_src,inet_ntoa(ip->src_ip));
    strcat(pkt_dst,inet_ntoa(ip->dst_ip));
    
    if(strncmp(get_lan(pkt_src),get_lan(ipp),13) == 0)
    {
    	is_lan = 1;
    }else if(strncmp(get_lan(pkt_dst),get_lan(ipp),13) == 0){
    	is_lan = 2;
    }else{
    	is_lan = 0;
    	return;
    }
    
    if(is_in(pkt_src,*l)==1&&is_lan==1){
    	printf("%s\n",pkt_src);
    	is_in_list = 1;
    	add(l,create(pkt_src));
    }else if(is_in(pkt_dst,*l)==1&&is_lan==2){
    	printf("%s\n",pkt_dst);
    	is_in_list = 2;
    	add(l,create(pkt_dst));
    }else{
    	is_in_list = 0;
    }
    
    pkt_port = ip->protocol;
    
}
void packet_handler_for_tcp(const u_char *pkt_data){
    TCP_HEADER * tcp;
    tcp = (TCP_HEADER *)pkt_data;
    if(is_lan == 0){
    	return;
    }
}

void packet_capture(char* ip,ip_list** l){
    int res;
    pcap_t * handler;
    struct pcap_pkthdr * p;
    char errbuff[PCAP_ERRBUF_SIZE];
    const unsigned char* data;
    const char * k = "enp0s3";
    int offset = 0;
    
    if((handler=pcap_open_live(k,65536,1,1000,errbuff))==NULL)
        printf("error");
    if((res=pcap_next_ex(handler,&p,&data)>=0)){
        offset = sizeof(struct ether_header);
        packet_handler_for_ip(data+offset,ip,l);
        offset = 0;
        packet_handler_for_en(data+offset);
        offset = offset + sizeof(struct ether_header) + sizeof(IP_HEADER);
        packet_handler_for_tcp(data+offset);
    }else{
    printf("error");
    }
    
    if(is_lan==0){
    	initializing();
    	return;
    }
    
    
    if(is_in_list==1){
    	sql_dv_list("Unknown",pkt_src,pkt_src_mac);
    }else if(is_in_list==2){
    	sql_dv_list("Unknown",pkt_dst,pkt_dst_mac);
    }
    sql_packet(pkt_src,pkt_src_mac,pkt_dst,pkt_dst_mac,pkt_port);
    initializing();
}
void initializing(){
	strcpy(pkt_src,"\0");
	strcpy(pkt_dst,"\0");
	strcpy(pkt_src_mac,"\0");
	strcpy(pkt_dst_mac,"\0");
	is_lan = 0;
	is_in_list = 0;
	is_danger_port = 0;
}
