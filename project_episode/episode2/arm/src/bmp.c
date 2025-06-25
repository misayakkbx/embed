#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h> //触摸屏的头文件

/*
    功能:实现一张800*480的bmp图片
*/
int show_bmp(int *addr,char *bmp_path)
{
    //打开bmp图(800*480)
    int fd_bmp = open(bmp_path,O_RDWR);
    if(fd_bmp < 0)
    {
        printf("open bmp fail\n");
        return -1;
    }

    //读取bmp图
    //去掉bmp图片的头54字节
    lseek(fd_bmp,54,SEEK_SET);

    char buf[800*480*3] = {0}; //存储bmp图片的buffer
    read(fd_bmp,buf,800*480*3);

    //读写lcd文件
    int x = 0; //横轴
    int y = 0; //纵轴
    for(y=0;y<480;y++)
    {
        for(x=0;x<800;x++)
        {
            //bmp图片读取的方式是从左到右 从下到上，所以要(479-y)
            //左边的第479行=右边的第0行
            //int0 = char0 | char1<<8 | char2<<16
            *(addr+(479-y)*800+x) = buf[(y*800+x)*3 +0] | 
                                    buf[(y*800+x)*3 +1]<<8 |
                                    buf[(y*800+x)*3 +2]<<16;
        }
    }

    //关闭bmp
    close(fd_bmp);
}

/*
    功能:实现一张小于800*480的任意大小的bmp图片
*/
int show_bmp_size(int *addr,char *bmp_path,int offset_x,int offset_y )
{
   //打开bmp图(任意大小:长宽必须是4的倍数)
   int fd_bmp = open(bmp_path,O_RDWR);
   if(fd_bmp < 0)
   {
       printf("open bmp fail\n");
       return -1;
   }

   //计算bmp图片的高度和高度
   int height = 0; //高度
   int width = 0; //宽度
   lseek(fd_bmp,18,SEEK_SET);
   read(fd_bmp,&width,4); //读取bmp宽度
   read(fd_bmp,&height,4);//读取bmp高度
   printf("bmp width:%d height:%d\n",width,height);

   //读取bmp图
   //去掉bmp图片的头54字节
   lseek(fd_bmp,54,SEEK_SET);
   char buf[width*height*3]; //变长数组不能初始化
   read(fd_bmp,buf,width*height*3);

   //读写lcd文件
   int x = 0; //横轴
   int y = 0; //纵轴
   for(y=0;y<height;y++)
   {
       for(x=0;x<width;x++)
       {
           //bmp照片最后一行的起始点的坐标是(offset_x,offset_y+height-1)
           *(addr+((offset_y+height-1)-y)*800 + offset_x+x) = 
                                   buf[(y*width+x)*3 +0] |  
                                   buf[(y*width+x)*3 +1]<<8 |
                                   buf[(y*width+x)*3 +2]<<16;
       }
   }

   //关闭bmp
   close(fd_bmp);
}
