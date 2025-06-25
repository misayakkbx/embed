#ifndef __MAIN_H__
#define __MAIN_H__


//client的ip和port
#define A_CLIENT_IP "192.168.2.136"
#define A_CLIENT_PORT 50000
#define KEY_CLIENT_PORT 50001
#define DATA_CLIENT_PORT 50002
#define ONLINE_CLIENT_PORT 50003
#define A_CLIENT_NAME "misaya"

//server的ip和port
#define A_SERVER_IP "192.168.2.137"
#define A_SERVER_PORT 50000
#define KEY_SERVER_PORT 50001
#define DATA_SERVER_PORT 50002
#define ONLINE_SERVER_PORT 50003

//ubantu_client
#define U_CLIENT_IP "192.168.2.137"
#define U_CLIENT_PORT 60000
#define U_KEY_CLIENT_PORT 60001
#define U_DATA_CLIENT_PORT 60002
#define U_ONLINE_CLIENT_PORT 60003
#define U_CLIENT_NAME "kunkun"



struct login{

int password;
int id;
int flag;//(用来标志是register还是login),1register,2,login
int flag_login;//(标志是否登录成功)
int mes;//1,2,3三张图，开心，难过，鄙夷
char client_name[20];


};
struct client_list
{
    //数据域放什么,client_passowrd,client_id
    int client_password;
    int client_id;

    #if 0
    int  my_sock;
    int client_sock;
    #endif
    struct client_list * prev;
    struct client_list * next;

};
struct client_online_list
{

    char client_name[20];
    int client_ip;//网络字节序，传整形
    int client_port;
    int flag_print[4];
    int flag;//标志数组顺序

    #if 0
    int  my_sock;
    int client_sock;
    #endif
    struct client_online_list * prev;
    struct client_online_list * next;

};
struct online_mes{
    struct client_online_list* online_head;
    int online_sock;
    int * addr;

};


extern struct client_online_list * init_online_head();
extern int head_insert_online(struct client_online_list * head,char * name,int  ip,int port);
extern int display_online(struct client_online_list * head);
extern int show_login_success(int mes_sock);






#endif