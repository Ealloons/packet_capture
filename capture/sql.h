#include <stdio.h>
#include <mysql/mysql.h>
#include "struct.h"
#include <time.h>

MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *server = "localhost";                            
char *user = "root";
char *password = "1234";
char *database = "packet";

void sql_IO(char *query){
        if( !(conn = mysql_init((MYSQL*)NULL))){        
                printf("init fail\n");
                exit(1);
        }
        printf("mysql_init sucsess.\n");
        if(!mysql_real_connect(conn, server, user, password, NULL, 3306, NULL, 0)){
                printf("connect error.\n");    
                exit(1);
        }
        printf("mysql_real_connect suc.\n");
        if(mysql_select_db(conn, database) != 0){
                mysql_close(conn);
                printf("select_db fail.\n");
                exit(1);
        }
        if(mysql_query(conn,query)){
                printf("query fail\n");
                exit(1);
        }
        printf("query sucsess\n");
        
        mysql_close(conn);

}
void sql_selector(char *query,ip_list **l){
	ip_list* k = *l;
        if( !(conn = mysql_init((MYSQL*)NULL))){       
                printf("init fail\n");
                exit(1);
        }
        if(!mysql_real_connect(conn, server, user, password, NULL, 3306, NULL, 0)){
                printf("connect error.\n");     
                exit(1);
        }
        if(mysql_select_db(conn, database) != 0){
                mysql_close(conn);
                printf("select_db fail.\n");
                exit(1);
        }
        if(mysql_query(conn,query)){
                printf("query fail\n");
                exit(1);
        }
        res = mysql_store_result(conn);                 
        printf("res suceese\n");
        if(res==NULL)
        	return;
        while( (row=mysql_fetch_row(res))!=NULL){
        	add(l,create(row[2]));
        }
        mysql_close(conn);
}
void sql_packet(char* s_ip,char* s_mac,char* d_ip,char* d_mac,int port){
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	char time[100] = {0};
	char *t_tmp = "%d-%d-%d %d:%d:%d";
	sprintf(time,t_tmp,tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday,tm.tm_hour,tm.tm_min,tm.tm_sec);
	char query[300] = {0};
	char* tmp = "insert into pkt_log(time,src_ip,src_mac,dst_ip,dst_mac,port,dangerous) value('%s','%s','%s','%s','%s','%d',0);";
	sprintf(query,tmp,time,s_ip,s_mac,d_ip,d_mac,port);
	
	if( !(conn = mysql_init((MYSQL*)NULL))){        
                printf("init fail\n");
                exit(1);
        }
        if(!mysql_real_connect(conn, server, user, password, NULL, 3306, NULL, 0)){
                printf("connect error.\n");     
                exit(1);
        }
        if(mysql_select_db(conn, database) != 0){
                mysql_close(conn);
                printf("select_db fail.\n");
                exit(1);
        }
        if(mysql_query(conn,query)){
                printf("query fail\n");
                exit(1);
        }
        
        mysql_close(conn);
        
}
void sql_dv_list(char* id,char* ip,char* mac){
	
	char query[300] = {0};
	char* tmp = "insert ignore into dv_list(dv_id,dv_ip,dv_mac) value('%s','%s','%s');";
	sprintf(query,tmp,id,ip,mac);
	if( !(conn = mysql_init((MYSQL*)NULL))){        
                printf("init fail\n");
                exit(1);
        }
        if(!mysql_real_connect(conn, server, user, password, NULL, 3306, NULL, 0)){
                printf("connect error.\n");     
                exit(1);
        }
        if(mysql_select_db(conn, database) != 0){
                mysql_close(conn);
                printf("select_db fail.\n");
                exit(1);
        }
        if(mysql_query(conn,query)){
                printf("query fail\n");
                exit(1);
        }
        mysql_close(conn);
}
