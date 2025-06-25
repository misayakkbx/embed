#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>


struct client_online_list * init_online_head()
{
    struct client_online_list * head=malloc(sizeof(struct client_online_list));
    if(head==NULL)
    {
        printf("malloc failed !\n");
        return NULL;
    }
    bzero(head->client_name,sizeof(head->client_name));
    head->client_port=0;
    head->client_ip=0;

    head->prev=head;
    head->next=head;
    return head;

}
int head_insert_online(struct client_online_list * head,char * name,int ip,int port)
{
    //初始化node节点
    struct client_online_list * node=malloc(sizeof(struct client_online_list));
    if(node==NULL)
    {
        printf("malloc fail\n");
        return 0;
    }
    strcpy(node->client_name,name);
    node->client_port=port;
    node->client_ip=ip;


    node->next=NULL;
    node->prev=NULL;

    //开始头部插入
    if(head->next==head)
    {
        node->next=head;
        node->prev=head;
        head->prev=node;
        head->next=node;
        return 0;
    }
    node->prev=head;
    node->next=head->next;
    head->next->prev=node;
    head->next=node;
    return 0;
}
int display_online(struct client_online_list * head)
{
    struct client_online_list * p=NULL;
    for(p=head->next;p!=head;p=p->next)
    {
        char client_name[20]={0};
        char client_ip[20]={0};
        int client_port=0;
        strcpy(client_name,p->client_name);
        inet_ntop(AF_INET,&(p->client_ip),client_ip,20);
        client_port=ntohs(p->client_port);

        printf("client_name:%s\nclient_ip:%s\nclient_port:%d\n",client_name,client_ip,client_port);
    }
    printf("\n");
    return 0;
}





