#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>



struct client_list * init_head()
{
    struct client_list * head=malloc(sizeof(struct client_list));
    if(head==NULL)
    {
        printf("malloc failed !\n");
        return NULL;
    }
    head->client_password=0;
    head->client_id=0;

    



    head->prev=head;
    head->next=head;
    return head;

}
int head_insert_data(struct client_list * head,int id,int password)
{
    //初始化node节点
    struct client_list * node=malloc(sizeof(struct client_list));
    if(node==NULL)
    {
        printf("malloc fail\n");
        return 0;
    }
    node->client_password=password;
    node->client_id=id;

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


//遍历链表
int display_key(struct client_list * head)
{
    struct client_list * p=NULL;
    for(p=head->next;p!=head;p=p->next)
    {
        printf("id:%d->password:%d\n",p->client_id,p->client_password);
    }
    printf("\n");
    return 0;
}
int check_key(struct client_list * head,int id,int password)
{
    struct client_list * p=NULL;
    for(p=head->next;p!=head;p=p->next)
    {
        if(p->client_id==id&&(p->client_password==password))
            return 1;
    }
    printf("\n");
    return 0;
}


struct client_online_list * init_online_head()
{
    struct client_online_list * head=malloc(sizeof(struct client_online_list));
    if(head==NULL)
    {
        printf("malloc failed !\n");
        return NULL;
    }
    bzero(head->client_name,sizeof(head->client_name));
    // bzero(head->client_ip,sizeof(head->client_ip));
    head->client_ip=0;
    head->client_port=0;

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
    // strcpy(node->client_ip,ip);
    node->client_ip=ip;//字节序
    node->client_port=port;


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
int print_send_online(struct client_online_list * head,int online_client_sock,int i)
{
    printf("send_online1\n");
    struct client_online_list * p=NULL;
    
    for(p=head->next;;p=p->next)
    {
        //跳过head,不发送head节点
   

        if(p==head)
            continue;
        // if(p==NULL)
        //     continue;


        if(p->flag_print[i]==0)
         {

    // printf("send_online5\n");
            char ip[20]={0};
            inet_ntop(AF_INET,&p->client_ip,ip,20);
            int ip_change=htonl(p->client_ip);
            printf("ip->%d,%s,%d->change_ip:%d\n",p->client_ip,ip,ip_change,ntohl(ip_change));
            //这里发的时候不会要htons
            struct client_online_list send_mes;
            strcpy(send_mes.client_name,p->client_name);
            send_mes.client_ip=ip_change;
            send_mes.client_port=p->client_port;//已经是网络字节序p->port
            send(online_client_sock,&send_mes,sizeof(struct client_online_list),0);
            // printf("send_online3\n");

            p->flag_print[i]=1;
         }
    }
    printf("\n");
    return 0;
}
