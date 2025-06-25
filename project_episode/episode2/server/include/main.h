#ifndef  __MAIN_H__
#define  __MAIN_H__

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

struct link_ifo{

    char client_name[20];
    //本机send_write的sock
    int  my_sock;
    int  mes_sock;
    int  key_sock;
    int  online_sock;
    //这个获取目标sock有什么用，验证是否成功吗
    int client_sock;
    int  client_mes_sock;
    int  client_key_sock;
    int client_online_sock;
    //头节点//24,32
    struct client_list * key_head;
    struct client_online_list * online_head;

    //传输用的ip和port
    struct sockaddr * client_s;
    struct sockaddr * client_key_s;
    struct sockaddr * client_mes_s;
    struct sockaddr * client_online_s;
};
struct login{
    int password;
    int id;
    int flag;//(用来标志是register还是login)
    int flag_login;//(标志是否登录成功)
    char client_name[20];//用来存储name


};

struct client_online_list
{

    char client_name[20];
    int client_ip;//注意是网络字节序数据
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
struct online_mes{
    struct client_online_list* online_head;
    int online_client_sock;
    int flag_print[4];
    int flag;//标志数组顺序

};
struct mes_trans{
    int *  client_mes_sock;
    int flag_mes;



};

extern void * handle_fuc(void * arg);
extern struct client_list * init_head();

extern int head_insert_data(struct client_list * head,int id,int passowrd);
extern int display_key(struct client_list * head);
extern int check_key(struct client_list * head,int id,int password);

extern struct client_online_list * init_online_head();
extern int head_insert_online(struct client_online_list * head,char * name,int ip,int port);
extern int display_online(struct client_online_list * head);
extern int print_send_online(struct client_online_list * head,int online_client_sock,int i);








#endif