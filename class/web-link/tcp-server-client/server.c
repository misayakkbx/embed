#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.2.137"
#define SERVER_PORT 60000

#define B_CLIENT_IP "192.168.2.137"
#define B_CLIENT_PORT 60001

#define A_CLIENT_IP "192.168.2.136"
#define A_CLIENT_PORT 60000

struct client_ifo
{

    int client_fd;
    struct sockaddr_in recv_ip_p;
    struct client_ifo * point_zero;

};
struct trans_ifo
{
    char buf[20];
    struct sockaddr_in aim_ip_p;
    // struct client_ifo * point_zero;

};

void * fuc(void * arg)
{
    struct client_ifo client= *(struct client_ifo *)arg;
    int client_fd=client.client_fd;
    // char buf[20];
    struct trans_ifo ifo_buf;

    while(1)
    {
        bzero(&ifo_buf,sizeof(ifo_buf));
        int ret=read(client_fd,&ifo_buf,sizeof(ifo_buf));
        if(ret==0)
        {
            perror("connect disconnected");
        }
        //遍历是否有目标ip和p
        for(int i=0;i<1024;i++)
        {
            struct client_ifo * check_struct=client.point_zero+i;

            if((check_struct->recv_ip_p.sin_addr.s_addr==ifo_buf.aim_ip_p.sin_addr.s_addr)&&
                (check_struct->recv_ip_p.sin_port==ifo_buf.aim_ip_p.sin_port)
            )
            send(check_struct->client_fd,ifo_buf.buf,20,0);
        }

    }









}

int main(int argc,char **argv)
{
    struct client_ifo client[1024];
    int client_fd,my_sock;
    my_sock=socket(AF_INET,SOCK_STREAM,0);
    if(my_sock<0)
    {
        perror("socket create fail");
        return -1;
    }
    struct sockaddr_in my_net;
    my_net.sin_addr.s_addr=inet_addr(SERVER_IP);
    my_net.sin_port=htons(SERVER_PORT);
    my_net.sin_family=AF_INET;

    int ret_bind=bind(my_sock,(struct sockaddr *)&my_net,sizeof(struct sockaddr_in));
    if(ret_bind<0)
    {
        perror("bind fail");
        return -1;
    }

    int ret_listen=listen(my_sock,128);
    if(ret_listen<0)
    {
        perror("listen fail");
        return -1;
    }

    int i=0;
    int len=sizeof(struct sockaddr_in);
    struct sockaddr_in recv_net;
    //建立服务器
    while(1)
    {
        bzero(&recv_net,sizeof(recv_net));
        
        client_fd=accept(my_sock,(struct sockaddr *)&recv_net,&len);
        if(client_fd<0)
        {
            perror("accept fail");
            return -1;
        }
        client[i].recv_ip_p=recv_net;
        client[i].client_fd=client_fd;
        client[i].point_zero=&client[0];


        pthread_t pthread;
        
        pthread_create(&pthread,NULL,fuc,&client[i++]);



    }




    return 0;
}
