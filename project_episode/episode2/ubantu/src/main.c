#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "main.h"
void * read_mes_fuc(void * arg)
{
    int mes_sock=*(int *)arg;
    while(1)
    {
        printf("read mes\n");
        char buf[20];
        bzero(buf,20);
        //为什么没收到
        //为什么mes_sock会断开
        read(mes_sock,buf,20);
        printf("%d\n",mes_sock);
        printf("buf:%s",buf);
        if(strcmp(buf,"1")==0)
        {
            printf("\nmisaya:抱拳\n");
        }
        if(strcmp(buf,"2")==0)
        {
            printf("\nmisaya:笑脸\n");
        }if(strcmp(buf,"3")==0)
        {
            printf("\nmisaya:郁闷\n");
        }

    }


}
int show_login_success(int  mes_sock)
{
    // pause();
    pthread_t read_mes;
    pthread_create(&read_mes,NULL,read_mes_fuc,&mes_sock);

    while(1)
    {
        printf("输入1到3的数发送表情:");
        // char buf[20];
        int read_num;
        // bzero(buf,20);
        // scanf("%c",&read_num);
        scanf("%d",&read_num);
        // printf("scanf:%s\n",buf);
        
        // getchar();
        // char change_num=read_num;
        // getchar();
        // strcpy(buf,&read_num);
        // printf("scanf:%s\n",buf);
        if(read_num==1)
        
            send(mes_sock,"1",strlen("1"),0);
        if(read_num==2)
        send(mes_sock,"2",strlen("2"),0);
        if(read_num==3)
        send(mes_sock,"3",strlen("3"),0);
        
        


    }


    return 0;




}

void * show_online_list(void * arg)
{
    struct online_mes show_list=*(struct online_mes*)arg;
 while(1)
    {
        struct client_online_list  recv_mes;
        bzero(&recv_mes,sizeof(recv_mes));
 
        read(show_list.online_sock,&recv_mes,sizeof(recv_mes));
        // int ip_recv=ntohl(recv_mes.client_ip);
        int ip_recv=htonl(recv_mes.client_ip);

        printf("ip_recv:%d\n",ip_recv);
        char name[20]={0};
        char ip[20]={0};//就显示ip和name把，strcat(name,":");strcat(name,ip);
        int port=0;
        inet_ntop(AF_INET,&ip_recv,ip,20);//20字节****，这个函数
        strcpy(name,recv_mes.client_name);
        char ip_string[20];
    struct in_addr ip_addr;

    // 假设client_mes->kunkun中的错误IP地址以点分十进制形式存储在ip_string中
    strcpy(ip_string, ip);

    // 将错误的IP字符串转换为网络字节序的二进制格式
    if (inet_pton(AF_INET, ip_string, &ip_addr) <= 0) {
        perror("inet_pton failed");
  
    }

    // 将网络字节序转换为主机字节序
    ip_addr.s_addr = htonl(ip_addr.s_addr);

    // 手动交换字节顺序以纠正IP地址
    unsigned char *bytes = (unsigned char *)&ip_addr.s_addr;
    unsigned char temp = bytes[0];
    // bytes[0] = bytes[3];
    // bytes[3] = temp;
    temp = bytes[1];
    // bytes[1] = bytes[2];
    // bytes[2] = temp;
    printf("change\n");
    // 将纠正后的二进制格式转换回字符串格式
    char correct_ip[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &ip_addr, correct_ip, sizeof(correct_ip)) == NULL) {
        perror("inet_ntop failed");
        
    }




        // port=ntohs(recv_mes.client_port);
        printf("好友上线\n");
        // printf("client_mes->%s\t%s\n",name,correct_ip);
        printf("client_mes->%s\t%s\n",name,ip);

    }



}

int show_view_register(int my_sock,int key_sock,int mes_sock)
{
    int login_state=0;
    int id=0,password=0;
    printf("register view\n");
    printf("请输入3位或3位以下的数字账号:");
    scanf("%d",&id);
    printf("请输入3位或3位以下的数字密码:");
    scanf("%d",&password);

    struct login login_ifo;
    bzero(&login_ifo,sizeof(login_ifo));
    //整形需要装换字节序
    login_ifo.id=htons(id);
    login_ifo.password=htons(password);
    login_ifo.flag=htons(1);
    strcpy(login_ifo.client_name,"misaya");
    //先验证是否注册
    send(my_sock,&login_ifo,sizeof(login_ifo),0);
    //建立结构体client_list
    struct client_list key;
    bzero(&key,sizeof(key));
    key.client_id=htonl(id);
    key.client_password=htonl(password);
    //再发信息key_sock
    send(key_sock,&key,sizeof(key),0);


    return 3;
}
int show_view_login(int my_sock,struct client_online_list*  online_head)
{
    int login_state=0;
    int id=0,password=0;
    while(1)
    {


    printf("login view\n");
    printf("请选择模式,输入1进入注册界面,输入其他数字或符号进入登录界面,\n");
    scanf("%d",&login_state);
    if(login_state==1)
        return 1;
    printf("请输入3位或3位以下的数字账号:");
    scanf("%d",&id);
    printf("请输入3位或3位以下的数字密码:");
    scanf("%d",&password);
    struct login login_ifo;
    bzero(&login_ifo,sizeof(login_ifo));
    login_ifo.id=htons(id);
    login_ifo.password=htons(password);
    login_ifo.flag=htons(2);
    strcpy(login_ifo.client_name,"misaya");
    send(my_sock,&login_ifo,sizeof(login_ifo),0);
    int ret_login_state=read(my_sock,&login_ifo,40);
    if(ntohs(login_ifo.flag_login)==1)
        {
            //下面是注册成功界面
        printf("login success\n");
        //创建线程接受online_client
        return 2;
        }  
    if(ntohs(login_ifo.flag_login)==2)
        continue;;

    }

    return 0;
}


int main(int argc,char **argv)
{
//建立my_sock,key_sock,mes_sock
    int my_sock=socket(AF_INET,SOCK_STREAM,0);
    if(my_sock<0)
    {
        perror("my_sock socket create fail");
        return -1;
    }
    //
    
    //创建结构体my_net，进行绑定本地ip和port
    struct sockaddr_in my_net;
    my_net.sin_family=AF_INET;
    my_net.sin_port=htons(U_CLIENT_PORT);
    inet_pton(AF_INET,U_CLIENT_IP,&(my_net.sin_addr.s_addr));

     int key_sock=socket(AF_INET,SOCK_STREAM,0);
    if(key_sock<0)
    {
        perror("my_sock_list socket create fail");
        return -1;
    }
    //
    struct sockaddr_in my_net_key;
    my_net_key.sin_family=AF_INET;
    my_net_key.sin_port=htons(U_KEY_CLIENT_PORT);
    inet_pton(AF_INET,U_CLIENT_IP,&(my_net_key.sin_addr.s_addr));

    //登录成功后的mes_sock
    int mes_sock=socket(AF_INET,SOCK_STREAM,0);
    if(mes_sock<0)
    {
        perror("mes_sock socket create fail");
        return -1;
    }
    
    struct sockaddr_in my_net_mes;
    my_net_mes.sin_family=AF_INET;
    my_net_mes.sin_port=htons(U_DATA_CLIENT_PORT);
    inet_pton(AF_INET,U_CLIENT_IP,&(my_net_mes.sin_addr.s_addr));
    int online_sock=socket(AF_INET,SOCK_STREAM,0);
    if(online_sock<0)
    {
        perror("online_sock socket create fail");
        return -1;
    }
    
    struct sockaddr_in my_net_online;
    my_net_online.sin_family=AF_INET;
    my_net_online.sin_port=htons(U_ONLINE_CLIENT_PORT);
    inet_pton(AF_INET,U_CLIENT_IP,&(my_net_online.sin_addr.s_addr));

//绑定各自的sock和port
    //bind结构体
    int ret_bind=bind(my_sock,(struct sockaddr*)&my_net,sizeof(struct sockaddr_in));
    if(ret_bind<0)
    {
        perror("bind local_socket fail");
        return -1;
    }

    //绑定key_sock
    int ret_bind_key=bind(key_sock,(struct sockaddr*)&my_net_key,sizeof(struct sockaddr_in));
    if(ret_bind_key<0)
    {
        perror("bind ret_bind_key fail");
        return -1;
    }

    //绑定mes_sock
    int ret_bind_mes=bind(mes_sock,(struct sockaddr*)&my_net_mes,sizeof(struct sockaddr_in));
    if(ret_bind_mes<0)
    {
        perror("bind ret_bind_mes fail");
        return -1;
    }
     //绑定online_sock
    int ret_bind_online=bind(online_sock,(struct sockaddr*)&my_net_online,sizeof(struct sockaddr_in));
    if(ret_bind_online<0)
    {
        perror("bind ret_bind_online fail");
        return -1;
    }
//创建后续需要connect的目标ip和port结构体
    //创建server_net结构体
    struct sockaddr_in server_net;
    server_net.sin_family=AF_INET;
    server_net.sin_port=htons(A_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(server_net.sin_addr.s_addr));
    // printf("%s\n%d\n",A_SERVER_IP,A_SERVER_PORT);
    //创建server_net_key结构体         //什么时候开是连接
    struct sockaddr_in server_net_key;
    server_net_key.sin_family=AF_INET;
    server_net_key.sin_port=htons(KEY_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(server_net_key.sin_addr.s_addr));
    //创建server_net_mes结构体         //什么时候开是连接
    struct sockaddr_in server_net_mes;
    server_net_mes.sin_family=AF_INET;
    server_net_mes.sin_port=htons(DATA_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(server_net_mes.sin_addr.s_addr));

    //创建server_net_online结构体         //什么时候开是连接
    struct sockaddr_in server_net_online;
    server_net_online.sin_family=AF_INET;
    server_net_online.sin_port=htons(ONLINE_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(server_net_online.sin_addr.s_addr));


    //开始进行连接server，connect
    int ret_connect=connect(my_sock,(struct sockaddr *)&server_net,sizeof(struct sockaddr_in));
    //连接出现问题，可能是目标ip和port弄错了
    if(ret_connect<0)
    {
        perror("connect server_net fail");
        return -1;
    }

    int ret_connect_key=connect(key_sock,(struct sockaddr *)&server_net_key,sizeof(struct sockaddr_in));
    //连接出现问题，可能是目标ip和port弄错了
    if(ret_connect_key<0)
    {
        perror("connect server_net_key fail");
        return -1;
    }



    int ret_connect_mes=connect(mes_sock,(struct sockaddr *)&server_net_mes,sizeof(struct sockaddr_in));
    //连接出现问题，可能是目标ip和port弄错了
    if(ret_connect_mes<0)
    {
        perror("connect server_net_mes fail");
        return -1;
    }

    int ret_connect_online=connect(online_sock,(struct sockaddr *)&server_net_online,sizeof(struct sockaddr_in));
    //连接出现问题，可能是目标ip和port弄错了
    if(ret_connect_mes<0)
    {
        perror("connect server_net_mes fail");
        return -1;
    }


    struct client_online_list*  online_head=init_online_head();

    //开始展示登录界面
    while(1)
    {
    //show_login
 
        int ret_login=0;

        ret_login=show_view_login(my_sock,online_head);

    if(ret_login==1)
    {
       
        show_view_register(my_sock,key_sock,mes_sock);
        // continue;

    }
    if(ret_login==2)
    {
       
        struct client_online_list online_mes;
        char name[20]={0};
        int ip=0;
        int port=0;
        inet_pton(AF_INET,U_CLIENT_IP, &ip);

        bzero(&online_mes,sizeof(online_mes));
        strcpy(online_mes.client_name,U_CLIENT_NAME);
        online_mes.client_ip=ip;
        printf("my_ip%s->%d\n",U_CLIENT_IP,ip);

        online_mes.client_port=htons(U_ONLINE_CLIENT_PORT);

        //先发送自己的ip和port和name
        send(online_sock,&online_mes,sizeof(online_mes),0);
                 //贴登录成功界面图片
        //show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y );
        //用线程及时刷新链表
        pthread_t pthread;
        //传入什么进去，online_head,addr
        struct online_mes show_list;
        show_list.online_head=online_head;
        show_list.online_sock=online_sock;



        pthread_create(&pthread,NULL,show_online_list,&show_list);

        show_login_success(mes_sock);

     }


    }



    pause();

    return 0;
}




