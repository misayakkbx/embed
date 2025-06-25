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

struct trans_ifo
{
    char buf[20];
    struct sockaddr_in aim_ip_p;
    // struct client_ifo * point_zero;

};
void *fuc(void * arg)
{
    int my_sock=*(int *)arg;
    char read_buf[20];
    while(1)
    {
        bzero(read_buf,sizeof(read_buf));
        int recv_ret=read(my_sock,read_buf,20);
       if(recv_ret<0) {
        perror("disconnected");
        }
        printf("%s\n",read_buf);
    }



}

int main(int argc,char **argv)
{

    int my_sock=socket(AF_INET,SOCK_STREAM,0);
    if(my_sock<0)
    {
        perror("socket create fail");
        return -1;
    }
    struct sockaddr_in my_net;
    my_net.sin_addr.s_addr=inet_addr(A_CLIENT_IP);
    my_net.sin_port=htons(A_CLIENT_PORT);
    my_net.sin_family=AF_INET;

    int ret_bind=bind(my_sock,(struct sockaddr *)&my_net,sizeof(struct sockaddr_in));
    if(ret_bind<0)
    {
        perror("bind fail");
        return -1;
    }
    struct sockaddr_in server_net;
    server_net.sin_addr.s_addr=inet_addr(SERVER_IP);
    server_net.sin_port=htons(SERVER_PORT);
    server_net.sin_family=AF_INET;

    struct sockaddr_in aim_net;
    aim_net.sin_addr.s_addr=inet_addr(B_CLIENT_IP);
    aim_net.sin_port=htons(B_CLIENT_PORT);
    aim_net.sin_family=AF_INET;

    int ret_connect=connect(my_sock,(struct sockaddr *)&server_net,sizeof(struct sockaddr_in));
    if(ret_connect<0)
    {
        perror("connect server_net fail");
        return -1;
    }
    pthread_t pthread;

    pthread_create(&pthread,NULL,fuc,&my_sock);

    struct trans_ifo send_ifo;

    while(1)
    {
        bzero(&send_ifo,sizeof(send_ifo));
        send_ifo.aim_ip_p=aim_net;
        scanf("%s",send_ifo.buf);
        int ret_send=send(my_sock,&send_ifo,sizeof(send_ifo),0);
        printf("send:%d\n",ret_send);

    }





    return 0;

}
