#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h>
#include "main.h"
// #include "fun.h"
#include "bmp.h"
#include "ts.h"
#include "font.h"


#if 0
void * fuc_mes(void * arg)
{
    int my_sock=*(int *)arg;
    struct login  mesage;
    while(1)
    {
        bzero(&mesage,sizeof(mesage));
        read(my_sock,&mesage,sizeof(mesage));
        if(mesage.mes==1)

        if(mesage.mes==2)

        if(mesage.mes==3)

    }

}


int chat_view(int my_sock)
{
    //界面图片
    show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y );
    pthread_t pthread;
    pthread_create(&pthread,NULL,fuc_mes,&my_sock);
    //
    int x=0,y=0;
    struct login  mesage;

    //创建data的sock
    int data_sock=socket(AF_INET,SOCK_STREAM,0);


    while(1)
    {
        bzero(&mesage,sizeof(mesage));
        get(&x,&y);
        if()//1
        {
            mesage.mes=1;
            send(my_sock,mesage,sizeof(mesage));
        }
        if()//2
        {
            mesage.mes=2;
            send(my_sock,mesage,sizeof(mesage));
        }
        if()//3
        {
            mesage.mes=3;
            send(my_sock,mesage,sizeof(mesage));
        }


    }


//308,609

}
void * fuc_list(void * arg)//需要传入my_sock_list
{
    //初始化头部
    struct client_list * client_head=init_head();
    struct client_list read_client;
    while(1)
    {
        bzero(read_client,sizeof(read_client));
        //怎么反复刷新_>对面来一个我接受一个，接受一个刷新一次图片
        read(my_sock_list,&read_client,sizeof(read_client));
        //把读入的client_list 插入client_head
        head_insert_data(client_head,read_client);
        //贴图片，遍历链表插入图片
        list_draw(client_head);

    }
    //线程什么时候退出


}
#endif
void * show_online_list(void * arg)
{
            printf("5\n");

    sleep(1);
    struct online_mes show_list=*(struct online_mes*)arg;
    int i=0;
    while(1)
    {

            printf("6\n");

        struct client_online_list  recv_mes;
        bzero(&recv_mes,sizeof(recv_mes));
 

            printf("7\n");
        //为什么没有阻塞
        // #include <fcntl.h>

        // int flags = fcntl(show_list.online_sock, F_GETFL);
        // if (flags & O_NONBLOCK) {
        //     printf("Socket is in non-blocking mode\n");
        // }
        if (show_list.online_sock < 0) {
    perror("Invalid socket descriptor");
 
}
        int size_read=read(show_list.online_sock,&recv_mes,64);//为什么是64字节，不能直接sizeof,sizeof是56
            printf("8\n");
    printf("size_read:%d",size_read);
    printf("test error\n");
    
        // int recv_ip=ntohl(recv_mes.client_ip);
        int recv_ip=recv_mes.client_ip;

        char name[20]={0};
        char ip[20]={0};//就显示ip和name把，strcat(name,":");strcat(name,ip);
        int port=0;
        inet_ntop(AF_INET,&recv_mes.client_ip,ip,20);
    // struct in_addr ip_addr;

    // // 假设client_mes->kunkun中的错误IP地址以点分十进制形式存储在ip_string中
    // strcpy(ip_string, ip);

    // // 将错误的IP字符串转换为网络字节序的二进制格式
    // if (inet_pton(AF_INET, ip_string, &ip_addr) <= 0) {
    //     perror("inet_pton failed");
  
    // }

    // // 将网络字节序转换为主机字节序
    // ip_addr.s_addr = htonl(ip_addr.s_addr);

    // // 手动交换字节顺序以纠正IP地址
    // unsigned char *bytes = (unsigned char *)&ip_addr.s_addr;
    // unsigned char temp = bytes[0];
    // // bytes[0] = bytes[3];
    // // bytes[3] = temp;
    // temp = bytes[1];
    // // bytes[1] = bytes[2];
    // // bytes[2] = temp;
    // printf("change\n");
    // // 将纠正后的二进制格式转换回字符串格式
    // char correct_ip[INET_ADDRSTRLEN];
    // if (inet_ntop(AF_INET, &ip_addr, correct_ip, sizeof(correct_ip)) == NULL) {
    //     perror("inet_ntop failed");
        
    // }


        strcpy(name,recv_mes.client_name);
        port=ntohs(recv_mes.client_port);
        strcat(name,"->");
        strcat(name,ip);
        printf("recv:%s",name);

        //把文字贴上去,dispay
        // Display_characterX(unsigned int x,//x坐标起始点
        //                  unsigned int y,//y坐标起始点//y=y+i*height
		// 				 unsigned char *string,//GB2312 中文字符串//上面cat好了就直接name就行了
		// 				 unsigned int color ,//字体颜色值
		// 				 int size);//字体放大倍数 1~8
        Display_characterX(0,//x坐标起始点
                         0+i*40,//y坐标起始点//y=y+i*height
						 name,//GB2312 中文字符串//上面cat好了就直接name就行了
						0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
        //贴完了下一次往下面贴，用i标志次数
        i++;
        
    }


}
void * read_mes_fuc(void * arg)
{
    struct show_ifo show=*(struct show_ifo*)arg;
    int * addr=show.addr;
    int mes_sock=show.mes_sock;
    while(1)
    {
        printf("read mes\n");
        char buf[20];
        bzero(buf,20);
        //为什么没收到
        printf("error1\n");
        read(mes_sock,buf,20);
        printf("buf:%s",buf);
        if(strcmp(buf,"1")==0)
        {
                    show_bmp_size(addr,"1_show.bmp",0,115);

        }
        if(strcmp(buf,"2")==0)
        {
                    show_bmp_size(addr,"2_show.bmp",0,115);

        }if(strcmp(buf,"3")==0)
        {
                    show_bmp_size(addr,"3_show.bmp",0,115);

        }

    }


}

int show_login_success(int mes_sock,int* addr)
{

    int x=0,y=0;
    // pause();
   Clean_Area(0,//x坐标起始点
                 0,//y坐标起始点
				 800,//绘制的宽度
				 480,//绘制的高度
				 0x00ffffff);//往屏幕指定区域填充颜色
    //创建线程收取数据
    pthread_t read_mes;
    struct show_ifo show;
    show.mes_sock=mes_sock;
    show.addr=addr;

    pthread_create(&read_mes,NULL,read_mes_fuc,&show);
    show_bmp_size(addr,"chat_btn.bmp",0,0);
    //获取坐标
    while(1)
    {
    get_xy(&x,&y);
    x=x*800/1024;
    y=y*480/600;

    //点击聊天"chat start"
    if(x>278&&y>245&&x<473&&y<447)
    {
        //展示图片背景，字，按钮图片，获取对应xy
        show_bmp_size(addr,"fi_bg.bmp",0,0);

        while(1)
        {




        show_bmp_size(addr,"1.bmp",650,20);
        show_bmp_size(addr,"2.bmp",650,140);
        show_bmp_size(addr,"3.bmp",650,260);
        Display_characterX(0,//x坐标起始点
                         0,//y坐标起始点//y=y+i*height
						 "other_pic",//GB2312 中文字符串//上面cat好了就直接name就行了
						0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
        Display_characterX(300,//x坐标起始点
                         0,//y坐标起始点//y=y+i*height
						 "my_pic",//GB2312 中文字符串//上面cat好了就直接name就行了
						0x00000000 ,//字体颜色值
						 3);//字
        //获取按键
        get_xy(&x,&y);
        x=x*800/1024;
        y=y*480/600;
        char buf[20]={0};
        if(x>650&&y>20&&x<750&&y<120)
           {
            strcpy(buf,"1");
            show_bmp_size(addr,"1_show.bmp",309,115);

            send(mes_sock,buf,20,0);

           } 

        if(x>650&&y>140&&x<750&&y<240)
{
            strcpy(buf,"2");
            show_bmp_size(addr,"2_show.bmp",309,115);

            send(mes_sock,buf,20,0);

           } 

        if(x>650&&y>260&&x<750&&y<360)
{
            strcpy(buf,"3");
            show_bmp_size(addr,"3_show.bmp",309,115);

            send(mes_sock,buf,20,0);

           } 



        }
        


        
        
        
        // strcpy(buf,"1");
        // send(mes_sock,buf,20,0);
        // printf("send succuess:%s\n",buf);
    }
    //点击"exit"
    }

    return 0;
}


int show_view_login(int my_sock)
{

    //展示界面
    //int show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y )
    int x=0,y=0;
    int password_len=0;
    int id_len=0;
    // char a[3];
    int password=0,id=0;
    printf("test\n");
    // int pic_len=?//自己设置，贴图的宽
    int flag_change=0;

    while(1)
    {
       
        //获取触摸屏信息，输入进行id赋值
        //int get_xy(int *x, int *y),x=x*800/1024;,y=y*480/600
        printf("id:%d->password:%d\n",id,password);

        get_xy(&x,&y);
        x=x*800/1024;
        y=y*480/600;
        //判断是否在键盘区域，按键{1...9}{"enter"}{"register"}{"login"}

        //例子如下
        //按钮1
        //为什么字符串会消失
        printf("id_len:%d",id_len);
        if(id_len==3)
            flag_change=1;
        printf("flag_change:%d\n",flag_change);
        if(x>465&&y>122&&x<553&&y<203)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                // strcat(a,"1");
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "1",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*1+id;
                //100*(id_len==0)   +10*(id_len==1) + 1*(id_len==2)
                // if(id_len==0)
                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "1",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*1+password;
                password_len++;
                printf("password_len:%d\n",password_len);
            }
            
        }
       
         //按钮2
        if(x>575&&y>122&&x<661&&y<203)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "2",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*2+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "2",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*2+password;
                password_len++;
            }
            
        }
         //按钮3
        if(x>674&&y>122&&x<763&&y<203)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "3",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*3+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*10,//x坐标起始点
                         172,//y坐标起始点
						 "3",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 2);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*3+password;
                password_len++;
            }
            
        }
         //按钮4
        if(x>465&&y>219&&x<553&&y<294)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "4",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*4+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "4",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*4+password;
                password_len++;
            }
            
        }
         //按钮5
        if(x>570&&y>219&&x<661&&y<296)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "5",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*5+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "5",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*5+password;
                password_len++;
            }
            
        }
         //按钮6
        if(x>674&&y>215&&x<763&&y<294)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "6",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*6+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "6",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*6+password;
                password_len++;
            }
            
        }
         //按钮7
        if(x>465&&y>324&&x<553&&y<404)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "7",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*7+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "7",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*7+password;
                password_len++;
            }
            
        }
         //按钮8
        if(x>574&&y>321&&x<665&&y<402)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "8",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*8+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "8",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*8+password;
                password_len++;
            }
            
        }
         //按钮9
        if(x>675&&y>321&&x<763&&y<403)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "9",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*9+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "9",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*9+password;
                password_len++;
            }
            
        }
         //按钮0
        if(x>513&&y>52&&x<739&&y<110)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "0",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*0+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "0",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8、
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*0+password;    
                password_len++;
            }
        }
            
            


      
        //判断是否按了"login",涉及创建结构体struct login
        //到主函数进行还是直接嵌套，选择直接嵌套
        if(x>218&&y>329&&x<388&&y<398)
        {
            
               struct login login_ifo;
            bzero(&login_ifo,sizeof(login_ifo));
            //整形需要装换字节序
            login_ifo.id=htons(id);
            login_ifo.password=htons(password);
            login_ifo.flag=htons(2);
            strcpy(login_ifo.client_name,"misaya");

            // printf("id-%dpasword-%dflag-%d\n",login_ifo.id,login_ifo.password,login_ifo.flag);
            //先验证是否注册
            send(my_sock,&login_ifo,sizeof(login_ifo),0);
            printf("test error\n");
            int ret_login_state=read(my_sock,&login_ifo,40);
            printf("test error2\n");

            if(ntohs(login_ifo.flag_login)==1)
              {
                printf("login success\n");
                //创建线程接受struct client_online_list*  online_head
                return 2;
            
              }  
            if(ntohs(login_ifo.flag_login)==2)
              {  printf("login fail\n");
                return -3;
              }

            printf("test error3\n");

            #if 0
            //建立结构体client_list
            struct client_list key;
            bzero(&key,sizeof(key));
            key.client_id=htonl(id);
            key.client_password=htonl(password);
            //再发信息key_sock
            send(key_sock,&key,sizeof(key),0);
            #endif
            // int ret_state=login_state(password,id,my_sock,flag);//登录成功阻塞在这里
            // return ret_state;//登录失败退出函数//返回2

        }
     

        //判断是否按了register
        if(x>11&&y>329&&x<190&&y<398)
            return 1;//直接return 1； 


}


}

int show_view_register(int my_sock,int key_sock,int mes_sock)
{

    //展示界面
    //int show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y )
    int x=0,y=0;
    int password_len=0;
    int id_len=0;
    // char a[3];
    int password=0,id=0;
    printf("test\n");
    // int pic_len=?//自己设置，贴图的宽
    int flag_change=0;

    while(1)
    {
       
        //获取触摸屏信息，输入进行id赋值
        //int get_xy(int *x, int *y),x=x*800/1024;,y=y*480/600
        printf("id:%d->password:%d\n",id,password);

        get_xy(&x,&y);
        x=x*800/1024;
        y=y*480/600;
        //判断是否在键盘区域，按键{1...9}{"enter"}{"register"}{"login"}

        //例子如下
        //按钮1
        //为什么字符串会消失
        printf("id_len:%d",id_len);
        if(id_len==3)
            flag_change=1;
        printf("flag_change:%d\n",flag_change);
        if(x>465&&y>122&&x<553&&y<203)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                // strcat(a,"1");
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "1",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*1+id;
                //100*(id_len==0)   +10*(id_len==1) + 1*(id_len==2)
                // if(id_len==0)
                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "1",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*1+password;
                password_len++;
                printf("password_len:%d\n",password_len);
            }
            
        }
       
         //按钮2
        if(x>575&&y>122&&x<661&&y<203)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "2",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*2+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "2",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*2+password;
                password_len++;
            }
            
        }
         //按钮3
        if(x>674&&y>122&&x<763&&y<203)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "3",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*3+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*10,//x坐标起始点
                         172,//y坐标起始点
						 "3",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 2);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*3+password;
                password_len++;
            }
            
        }
         //按钮4
        if(x>465&&y>219&&x<553&&y<294)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "4",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*4+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "4",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*4+password;
                password_len++;
            }
            
        }
         //按钮5
        if(x>570&&y>219&&x<661&&y<296)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "5",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*5+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "5",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*5+password;
                password_len++;
            }
            
        }
         //按钮6
        if(x>674&&y>215&&x<763&&y<294)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "6",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*6+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "6",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*6+password;
                password_len++;
            }
            
        }
         //按钮7
        if(x>465&&y>324&&x<553&&y<404)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "7",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*7+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "7",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*7+password;
                password_len++;
            }
            
        }
         //按钮8
        if(x>574&&y>321&&x<665&&y<402)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "8",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*8+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "8",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*8+password;
                password_len++;
            }
            
        }
         //按钮9
        if(x>675&&y>321&&x<763&&y<403)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "9",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*9+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "9",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*9+password;
                password_len++;
            }
            
        }
         //按钮0
        if(x>513&&y>52&&x<739&&y<110)//限定长度为3
        {
            if(flag_change==0&&id_len<3)
            {
                Display_characterX(156+id_len*20,//x坐标起始点
                         65,//y坐标起始点
						 "0",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8
                         //把按钮图片贴到位置，偏移量设置id，x+id_len*id_len,
                id=(100*(id_len==0) +10*(id_len==1) + 1*(id_len==2))*0+id;

                id_len++;
            }
            if (flag_change==1&&password_len<3)
            {
                Display_characterX(156+password_len*20,//x坐标起始点
                         172,//y坐标起始点
						 "0",//GB2312 中文字符串
						 0x00000000 ,//字体颜色值
						 3);//字体放大倍数 1~8、
                password=(100*(password_len==0) +10*(password_len==1) + 1*(password_len==2))*0+password;    
                password_len++;
            }
        }
            

        //判断是否按了register
        if(x>11&&y>329&&x<190&&y<398)
        {
            struct login login_ifo;

            bzero(&login_ifo,sizeof(login_ifo));
            //整形需要装换字节序
            login_ifo.id=htons(id);
            login_ifo.password=htons(password);
            login_ifo.flag=htons(1);
            strcpy(login_ifo.client_name,"misaya");

            // printf("id-%dpasword-%dflag-%d\n",login_ifo.id,login_ifo.password,login_ifo.flag);
            //先验证是否注册
            send(my_sock,&login_ifo,sizeof(login_ifo),0);
            //建立结构体client_list
            struct client_list key;
            bzero(&key,sizeof(key));
            key.client_id=htonl(id);
            key.client_password=htonl(password);
            //再发信息key_sock
            send(key_sock,&key,sizeof(key),0);
            // send(key_sock,);
            // printf("id-%dpasword-%dflag-%d\n",login_ifo.id,login_ifo.password,login_ifo.flag);
            // return 3;//直接return 1； 
            // close(my_sock);
            return 0;


        }


}
    return 0;

}



int main(int argc,char **argv)
{
    
    int x=0,y=0;
    int fd_lcd = open("/dev/fb0",O_RDWR);
    if(fd_lcd < 0)
    {
        printf("open lcd fail\n");
        return -1;
    }
    Init_Font();

    //LCD��ӳ��(��ȡlcd��Ļ��0�����ص������)
    int *addr = mmap(NULL,  //If addr is NULL, then the kernel chooses the address
                     800*480*4, //LCD�ĳ����ܵ��ֽ���
                     PROT_READ|PROT_WRITE, //�ڴ�ռ�Ķ�дȨ��
                     MAP_SHARED,//LCD�ı�־�� �ɼ�
                     fd_lcd,//LCD���ļ�������
                     0); //ƫ����
    // Init_Font();
    if(addr == NULL)
    {
        printf("mamp fail\n");
        return -1;
    }    
    //进行server连接
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
    my_net.sin_port=htons(A_CLIENT_PORT);
    inet_pton(AF_INET,A_CLIENT_IP,&(my_net.sin_addr.s_addr));

     int key_sock=socket(AF_INET,SOCK_STREAM,0);
    if(key_sock<0)
    {
        perror("my_sock_list socket create fail");
        return -1;
    }
    //
    struct sockaddr_in my_net_key;
    my_net_key.sin_family=AF_INET;
    my_net_key.sin_port=htons(KEY_CLIENT_PORT);
    inet_pton(AF_INET,A_CLIENT_IP,&(my_net_key.sin_addr.s_addr));

    //登录成功后的mes_sock
    int mes_sock=socket(AF_INET,SOCK_STREAM,0);
    if(mes_sock<0)
    {
        perror("mes_sock socket create fail");
        return -1;
    }
    
    struct sockaddr_in my_net_mes;
    my_net_mes.sin_family=AF_INET;
    my_net_mes.sin_port=htons(DATA_CLIENT_PORT);
    inet_pton(AF_INET,A_CLIENT_IP,&(my_net_mes.sin_addr.s_addr));

    int online_sock=socket(AF_INET,SOCK_STREAM,0);
    if(online_sock<0)
    {
        perror("online_sock socket create fail");
        return -1;
    }
    
    struct sockaddr_in my_net_online;
    my_net_online.sin_family=AF_INET;
    my_net_online.sin_port=htons(ONLINE_CLIENT_PORT);
    inet_pton(AF_INET,A_CLIENT_IP,&(my_net_online.sin_addr.s_addr));

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
    //创建server_net_mes结构体         //什么时候开是连接
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
    if(ret_connect_online<0)
    {
        perror("connect ret_connect_online fail");
        return -1;
    }

    // printf("aim_ip:%s,aim_port%d\n",A_SERVER_IP,A_SERVER_PORT);
    // printf("ret_connect:%d\n",ret_connect);
    
    struct client_online_list*  online_head=init_online_head();




    //开始展示界面

    while(1)
    {

    int ret_login=0;
    show_bmp_size(addr,"bg_login.bmp",0,0);
    // munmap(addr,800*480*4);
    ret_login=show_view_login(my_sock);
    // printf("main\n");
    
    if(ret_login==1)
    {
        Clean_Area(0,//x坐标起始点
                 0,//y坐标起始点
				 800,//绘制的宽度
				 480,//绘制的高度
				 0x00ffffff);//往屏幕指定区域填充颜色
        show_bmp_size(addr,"bg_register.bmp",0,0);
        show_view_register(my_sock,key_sock,mes_sock);
        // continue;

    }
        // pause();
 
    if(ret_login==2)
    {
        //创建结构体struct client_online_list
        printf("1\n");
        struct client_online_list online_mes;
        char name[20]={0};
        int ip=0;
        int port=0;
        inet_pton(AF_INET,A_CLIENT_IP, &ip);
        printf("2\n");

        bzero(&online_mes,sizeof(online_mes));
        //下面字节序都是装换了的
        strcpy(online_mes.client_name,A_CLIENT_NAME);
        online_mes.client_ip=htonl(ip);
        online_mes.client_port=htons(ONLINE_CLIENT_PORT);
        printf("3\n");

        //先发送自己的ip和port和name
        send(online_sock,&online_mes,sizeof(online_mes),0);
            //贴登录成功界面图片
        //show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y );
        //用线程及时刷新链表
        pthread_t pthread;
        //传入什么进去，online_head,addr
        struct online_mes show_list;
        show_list.online_head=online_head;
        show_list.addr=addr;
        show_list.online_sock=online_sock;

        printf("4\n");

        pthread_create(&pthread,NULL,show_online_list,&show_list);


        // pause();
        show_login_success(mes_sock, addr);
 }

    // munmap(addr,800*480*4);
    // UnInit_Font();
    // close(fd_lcd);
    // return 0;

    }
 

    munmap(addr,800*480*4);
    UnInit_Font();
    close(fd_lcd);
    return 0;
    
    }




    
