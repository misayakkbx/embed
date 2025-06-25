#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include "main.h"



#if 0
int fuc_episode2(struct client_list * head)
{
    //发送链表，一直发，用线程，怎么发，怎么接


    return 0;
}
#endif
//线程函数
//为什么
void * handle_fuc(void * arg)//arg里面还是应该添加一个head_list
{

    struct link_ifo  link_mes=*(struct link_ifo *)arg;//注意里面的ip和port都是网络信息，后面需要转换
    struct login read_ifo;


    while(1)
    {
        bzero(&read_ifo,sizeof(read_ifo));
        //fgets(send_buf,sizeof(send_buf),stdin);
        //send(client_id,send_buf,strlen(send_buf)-1,0);
        printf("3\n");
    #if 0
        int flags = fcntl(link_mes.my_sock, F_GETFL);
if (flags & O_NONBLOCK) {
    printf("Socket is in non-blocking mode\n");
} else {
    printf("Socket is in blocking mode\n");
}
    #endif



        //read应该要从client_sock地方读取
        int ret_r=read(link_mes.client_sock,&read_ifo,60);//监听什么信息，监听登录信息
        //ret_r==0断开连接，//ret_r<0读取sock错误
        if(ret_r==0)
        {
            perror("connect ");
        
        }
        printf("read data:%d\n",ret_r);
        printf("4\n");
        if(read_ifo.flag==htons(1))//给链表里面添加//表示注册
        {
            //两个链表1，一个是存password和id
            //2登录成功了才会加入ip和name和port，struct login_client

            printf("进入register\n");
            //结构体client_list
            struct client_list client_ifo;
            bzero(&client_ifo,sizeof(client_ifo));
            //从key_sock里面读取数据
            read(link_mes.client_key_sock,&client_ifo,sizeof(client_ifo));
            // char client_ip;
            // char client_name[20];
            // int client
            int password=ntohl(client_ifo.client_password);
            int id=ntohl(client_ifo.client_id);
            printf("%d->%d\n",id,password);

// int head_insert_data(struct client_list * head,char * ip,char * name,int port)

            //插入数据进链表
            head_insert_data(link_mes.key_head,id,password);

            //遍历查看
            display_key(link_mes.key_head);
        }
            


        if(read_ifo.flag==htons(2))//遍历链表看是否有对应的账号密码
        {
            //遍历链表查看是否有
            printf("login enter\n");
            int id=ntohs(read_ifo.id);
            int password=ntohs(read_ifo.password);
            printf("client id:%d\nclient_assowrd:%d\n",id,password);
            printf("key_list:\n");
            display_key(link_mes.key_head);
            
            int ret_check=check_key(link_mes.key_head,id,password);
            if(ret_check==1)
            {
                printf("login success\n");
                //改变read_ifo.flag_login=1,成功,0表示失败
                read_ifo.flag_login=htons(1);
                send(link_mes.client_sock,&read_ifo,sizeof(read_ifo),0);

            }
            else 
               {
                printf("login fail\n");
                read_ifo.flag_login=htons(2);
                send(link_mes.client_sock,&read_ifo,sizeof(read_ifo),0);
               } 
            #if 0
            for()//遍历链表找
            {
                if()//找到了该对应信息
                {
                    //把red_ifo的red_ifo.flag_login=1；
                    

                    
                    //发送red_ifo回去
                    send(link_mes.my_sock,&read_ifo,sizeof(read_ifo),0);
                    //进入fuc_episode2()
                    fuc_episode2(link_mes.head_client);

                }
            }
        //没找到的话把red_ifo的red_ifo.flag_login=0；
                    red_ifo.flag_login=0;

        //发送red_ifo,回去
                    send(link_mes.my_sock,&read_ifo,sizeof(read_ifo),0);
                    #endif
        }
      
    }


}