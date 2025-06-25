#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "font.h"
#include <arpa/inet.h>

#if 0
struct client_list * init_head()
{
    struct client_list * head=malloc(sizeof(struct client_list));
    if(head==NULL)
    {
        printf("malloc failed !\n");
        return NULL;
    }
    bzero(head->title,20);
    bzero(head->color,10);
    head->page=0;

    head->prev=head;
    head->next=head;
    return head;

}
int head_insert_data(struct client_list * head,char * title,char * color,int page)
{
    //初始化node节点
    struct client_list * node=malloc(sizeof(struct client_list));
    if(node==NULL)
    {
        printf("malloc fail\n");
        return 0;
    }
    strcpy(node->title,title);
    strcpy(node->color,color);
    node->page=page;

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
int list_draw(struct client_list * head)
{
   struct client_list * p=NULL;
        int i=0;
        int x=0,y=0;//后续修改偏移量
        Init_Font(void);
        //后续添加
        int width=0;
        int height=0;
        for(p=head->next;p!=head;p=p->next)
        {
            Clean_Area(int x,//x坐标起始点
                 int y,//y坐标起始点
				 int width,//绘制的宽度
				 int height,//绘制的高度
				 unsigned long color);//往屏幕指定区域填充颜色
            Display_characterX(unsigned int x,//x坐标起始点
                                unsigned int y,//y坐标起始点
                                unsigned char *string,//GB2312 中文字符串
                //string怎么用strcat(p->client_name,p->client_ip);
                                unsigned int color ,//字体颜色值
                                int size);//字体放大倍数 1~8
                //注意y=y+len_y*i;//主机设置y
            show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y);
            y=y+y*i;
            i++;
        }
    return 0;
}
#endif


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
    // strcpy(node->client_ip,ip);
    node->client_ip=ip;
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






