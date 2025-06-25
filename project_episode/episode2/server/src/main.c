#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "main.h"
#include <arpa/inet.h>
void * mes_tras_fuc(void * arg)
{
    sleep(1);
    struct mes_trans mes=*(struct mes_trans*)arg;
    int * client_mes_sock=mes.client_mes_sock;
    int flag_mes=mes.flag_mes;
    char buf[20];
    printf("********2\n");
    for(int i=0;i<2;i++)
    {
    printf("mes_sock%d\n",*(client_mes_sock+i));


    }
    while(1)
    {
        bzero(buf,sizeof(buf));
        // if(flag_mes==0)
        // read(9,buf,20);
        int recv_read=read(client_mes_sock[flag_mes],buf,20);
        printf("recv_read:%d->mes_sock:%d\n",recv_read,client_mes_sock[flag_mes]);


        // if(flag_mes==1)
        // // read(13,buf,20);
        // read(client_mes_sock[flag_mes],buf,20);

        printf("read buf:%s->%d\n",buf,flag_mes);
        printf("cliennt_mes_sock_____:%d->%d\n",client_mes_sock[0],client_mes_sock[1]);

    //下面发送问题,为什么连接会断开
    if(flag_mes==0)//9
        // send(client_mes_sock[flag_mes+1],buf,20,0);
     {
        // int ret_send1=send(client_mes_sock[flag_mes+1],buf,20,0);
        int ret_send1=send(*(client_mes_sock+1),buf,20,0);


        // int ret_send1=send(13,buf,20,0);
            printf("%d->%d\n",ret_send1,*(client_mes_sock+1));

     }   

    if(flag_mes==1)//13
        // send(client_mes_sock[flag_mes-1],buf,20,0);
        {
        // int ret_send2=send(client_mes_sock[flag_mes-1],buf,20,0);
        int ret_send2=send(*(client_mes_sock),buf,20,0);


        // int ret_send2=send(9,buf,20,0);
            // printf("%d\n",ret_send2);
            printf("%d->%d\n",ret_send2,*(client_mes_sock+1));


     }   
        // send(9,buf,20,0);



    }

}

void * online_send_fuc(void * arg)
{
    printf("send_fun1\n");
    struct online_mes online_list=*(struct online_mes *)arg;
    while(1)
    {
    printf("send_fun2\n");

        //遍历链表，发送数据，发完数据把，flag设置为1，后续不再发重复数据
        print_send_online(online_list.online_head,online_list.online_client_sock,online_list.flag);  

    }



}
void * online_fuc(void * arg)
{
    printf("online_fuc1\n");
    struct online_mes online_list=*(struct online_mes*)arg;
    pthread_t pthread_send;
    printf("online_fuc2\n");
    //为什么下面有问题
    pthread_create(&pthread_send,NULL,online_send_fuc,&online_list);//考虑把什么传入线程响应函数

    printf("online_fuc3\n");
   
        struct client_online_list recv_list;
        bzero(&recv_list,sizeof(recv_list));
        read(online_list.online_client_sock,&recv_list,sizeof(recv_list));
        //需要转换，字节序吗
        char ip[20]={0};
        inet_ntop(AF_INET,&recv_list.client_ip,ip,20);
        printf("recv_list.ip:%d->%s\n",recv_list.client_ip,ip);

        //插入链表,online，直接存入网络字节序数据行不行，到时候我再转发该链表，需要再转换字节序吗
        head_insert_online(online_list.online_head,recv_list.client_name,
            recv_list.client_ip,recv_list.client_port);


}

//client_list * client_head;
int main(int argc,char **argv)
{
    //建立sock，login，
    int my_sock=socket(AF_INET,SOCK_STREAM,0);
    if(my_sock<0)
    {
        perror("send socket create fail");
        return -1;
    }
     //创建结构体my_net，进行绑定本地ip和port
    struct sockaddr_in my_net;
    my_net.sin_family=AF_INET;
    my_net.sin_port=htons(A_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(my_net.sin_addr.s_addr));

    int ret_bind=bind(my_sock,(struct sockaddr*)&my_net,sizeof(struct sockaddr_in));
    if(ret_bind<0)
    {
        perror("bind socket fail");
        return -1;
    }

    //设置最大连接数量，listen
    int ret_lis=listen(my_sock,20);
    if(ret_lis<0)
    {
        perror("listen set fail");
        return -1;
    }
     int key_sock=socket(AF_INET,SOCK_STREAM,0);
    if(key_sock<0)
    {
        perror("key_sock socket create fail");
        return -1;
    }

     //创建结构体my_net，进行绑定本地ip和port,key_port
    struct sockaddr_in my_net_key;
    my_net_key.sin_family=AF_INET;
    my_net_key.sin_port=htons(KEY_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(my_net_key.sin_addr.s_addr));

    int ret_bind_key=bind(key_sock,(struct sockaddr*)&my_net_key,sizeof(struct sockaddr_in));
    if(ret_bind_key<0)
    {
        perror("bind socket fail");
        return -1;
    }

    //设置最大连接数量，listen
    int ret_lis_key=listen(key_sock,20);
    if(ret_lis_key<0)
    {
        perror("listen set fail");
        return -1;
    }
     int mes_sock=socket(AF_INET,SOCK_STREAM,0);
    if(mes_sock<0)
    {
        perror("mes_sock socket create fail");
        return -1;
    }

     //创建结构体my_net，进行绑定本地ip和port
    struct sockaddr_in my_net_mes;
    my_net_mes.sin_family=AF_INET;
    my_net_mes.sin_port=htons(DATA_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(my_net_mes.sin_addr.s_addr));

    int ret_bind_mes=bind(mes_sock,(struct sockaddr*)&my_net_mes,sizeof(struct sockaddr_in));
    if(ret_bind_mes<0)
    {
        perror("ret_bind_mes band socket fail");
        return -1;
    }

    //设置最大连接数量，listen
    int ret_lis_mes=listen(mes_sock,20);
    if(ret_lis_mes<0)
    {
        perror("ret_lis_mes listen set fail");
        return -1;
    }
    int online_sock=socket(AF_INET,SOCK_STREAM,0);
    if(online_sock<0)
    {
        perror("mes_sock socket create fail");
        return -1;
    }

    struct sockaddr_in my_net_online;
    my_net_online.sin_family=AF_INET;
    my_net_online.sin_port=htons(ONLINE_SERVER_PORT);
    inet_pton(AF_INET,A_SERVER_IP,&(my_net_online.sin_addr.s_addr));
    int ret_bind_online=bind(online_sock,(struct sockaddr*)&my_net_online,sizeof(struct sockaddr_in));
    if(ret_bind_online<0)
    {
        perror("ret_bind_online band socket fail");
        return -1;
    }
    //设置最大连接数量，listen
    int ret_lis_online=listen(online_sock,20);
    if(ret_lis_online<0)
    {
        perror("ret_lis_online listen set fail");
        return -1;
    }

    //定义接受client_sock，和存放其ip和port的结构体
    int client_sock;
    int client_key_sock;
    int client_mes_sock;
    int client_online_sock;
    

    struct sockaddr_in client;
    struct sockaddr_in client_key;
    struct sockaddr_in client_mes;//
    struct sockaddr_in client_online;

    int len=sizeof(struct sockaddr_in);
    #if 0
    //初始化client_list
    client_list * client_head=init_head();//直接用全局变量
    struct client_list client_ifo;
    #endif
    struct link_ifo link_mes;
    // printf("my_ip%smy_port:%d\n",A_SERVER_IP,A_SERVER_PORT);
    
    //初始化一个头结点
 
    struct client_list*  key_head=init_head();
    struct client_online_list*  online_head=init_online_head();
    int flag_print[2]={0};
    int client_mes_sock_store[2]={0};
    struct mes_trans mes;
    bzero(&mes,sizeof(mes));
    int j=0;
    int flag_mes[2]={0};
    int i=0;

    //开始建立连接
    while(1)
    {
     
        client_sock=accept(my_sock,(struct sockaddr *)&client,&len);
        if(client_sock<0)
        {
        perror("accpet client fail");
        return -1;
        }

        //client_key
        client_key_sock=accept(key_sock,(struct sockaddr *)&client_key,&len);
        if(client_key_sock<0)
        {
        perror("accpet client_key_sock fail");
        return -1;
        }

     
        //client_mes,
        client_mes_sock=accept(mes_sock,(struct sockaddr *)&client_mes,&len);
        if(client_mes_sock<0)
        {
        perror("accpet client_mes_sock fail");
        return -1;
        }
        client_mes_sock_store[j]=client_mes_sock;

   
        client_online_sock=accept(online_sock,(struct sockaddr *)&client_online,&len);
        if(client_online_sock<0)
        {
        perror("accpet client_online_sock fail");
        return -1;
        }


        bzero(&link_mes,sizeof(link_mes));
        //先传入ip和port

        //server的结构体sock初始化
        link_mes.my_sock=my_sock;
        link_mes.key_sock=key_sock;
        link_mes.mes_sock=mes_sock;
        link_mes.online_sock=online_sock;


        //接受的client_sock
        link_mes.client_sock=client_sock;
        link_mes.client_key_sock=client_key_sock;
        link_mes.client_mes_sock=client_mes_sock;
        link_mes.client_online_sock=client_online_sock;

        //传入需要写入的目标ip和port
        link_mes.client_s=(struct sockaddr *)&client;
        link_mes.client_key_s=(struct sockaddr *)&client_key;
        link_mes.client_mes_s=(struct sockaddr *)&client_mes;
        link_mes.client_online_s=(struct sockaddr *)&client_online;



        link_mes.key_head=key_head;
        link_mes.online_head=online_head;
        //创建线程接受，online信息
        pthread_t pthread_online;
        //online_mes需要包含什么信息，一个头指针(struct client_online_list*)，一个online_sock
        //包含进struct online_mes
        struct online_mes online_list;
        bzero(&online_list,sizeof(online_list));
        online_list.online_client_sock=client_online_sock;
        online_list.online_head=online_head;
        //初始化问题
        online_list.flag=i++;
        //下面为什么会有segment错误
        pthread_create(&pthread_online,NULL,online_fuc,&online_list);//考虑把什么传入线程响应函数
        printf("6\n");

       
        //client_ifo.client_name=
        //创建线程
        
        pthread_t pthread;
        pthread_create(&pthread,NULL,handle_fuc,&link_mes);//考虑把什么传入线程响应函数

 

        pthread_t pthread_mes;
        //flag_mes和数组地址int *
        //
        printf("********\n");
        // printf("mes_sock:%d\n",client_mes_sock);
        for(int k=0;k<2;k++)
        {
            printf("mes_sock:%d\n",client_mes_sock_store[k]);
            
        }

       
        // int * addr_store=client_mes_sock_store;
        mes.client_mes_sock=&client_mes_sock_store[0];
        // printf("cliennt_mes_sock:%d->%d",client_mes_sock_store[j],client_mes_sock);
        //西面
        mes.flag_mes=j;
        // mes.flag_flag=j++;
        pthread_create(&pthread_mes,NULL,mes_tras_fuc,&mes);//考虑把什么传入线程响应函数
        j++;
        
    }


    pause();




    return 0;
}