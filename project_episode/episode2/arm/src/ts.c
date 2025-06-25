#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <linux/input.h> //触摸屏的头文件

// 滑屏算法的状态
enum SLIDE
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    CLICK
};

/*
    点击的功能：获取x和y轴的坐标值
*/
int get_xy(int *x, int *y)
{ // 打开触摸屏文件
    int fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        printf("open ts fail\n");
        return -1;
    }

    // 读写触摸屏(读出触摸屏里面的信息)
    struct input_event ts; // 官方的结构体(存储触摸屏的信息)

    while (1)
    {
        memset(&ts, 0, sizeof(struct input_event));

        // 将触摸屏的信息读到这个结构体中(这是一个阻塞的代码 如果你不点击屏幕 他就会一直停留在这个地方)
        read(fd_ts, &ts, sizeof(struct input_event));

        // 获取触摸屏的x轴和y轴的坐标值
        if (ts.type == EV_ABS && ts.code == ABS_X)
        {
            // printf("x=%d ",ts.value); //x轴的坐标值  蓝色
            // printf("x=%d ",ts.value*800/1024); //x轴的坐标值  黑色

            *x = ts.value;
        }
        if (ts.type == EV_ABS && ts.code == ABS_Y)
        {
            // printf("y=%d\n",ts.value); //y轴的坐标值 蓝色
            // printf("y=%d\n",ts.value*480/600); //y轴的坐标值 黑色

            *y = ts.value;
        }

        /*
            如果只做点击的功能 下面两个事件只需要取一个值
        */
        // 按下去的事件
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1)
        {
            printf("down x=%d y=%d\n", *x, *y);
            break;
        }

#if 0
        //松手后的事件
        // if(ts.type == 1 && ts.code == 330 &&ts.value == 0)
        if(ts.type == EV_KEY && ts.code == BTN_TOUCH &&ts.value == 0)
        {
            printf("up x=%d y=%d\n",x,y);
        }
#endif
    }

    // 关闭触摸屏
    close(fd_ts);
}

/*
    滑屏算法
*/
int get_slide()
{
    // 打开触摸屏文件
    int fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        printf("open ts fail\n");
        return -1;
    }

    // 读写触摸屏(读出触摸屏里面的信息)
    struct input_event ts; // 官方的结构体(存储触摸屏的信息)
    int x1 = 0;            // x轴的值
    int y1 = 0;            // y轴的值
    int x2 = 0;
    int y2 = 0;

    while (1)
    {
        // 获取按下去的值
        while (1)
        {

            memset(&ts, 0, sizeof(struct input_event));

            // 将触摸屏的信息读到这个结构体中
            read(fd_ts, &ts, sizeof(struct input_event));

            // 获取触摸屏的x轴和y轴的坐标值
            //  if(ts.type == 3 && ts.code == 0)
            if (ts.type == EV_ABS && ts.code == ABS_X)
            {
                // printf("x=%d ",ts.value); //x轴的坐标值  蓝色
                // printf("x=%d ",ts.value*800/1024); //x轴的坐标值  黑色
                // x1 = ts.value*800/1024;
                x1 = ts.value;
            }
            // if(ts.type == 3 && ts.code == 1)
            if (ts.type == EV_ABS && ts.code == ABS_Y)
            {
                // printf("y=%d\n",ts.value); //y轴的坐标值 蓝色
                // printf("y=%d\n",ts.value*480/600); //y轴的坐标值 黑色

                y1 = ts.value;
            }

            // 按下去的事件
            if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1)
            {
                printf("down x1=%d y1=%d\n", x1, y1); // 调试代码
                break;
            }
        }

        // 获取松手后的值
        while (1)
        {

            memset(&ts, 0, sizeof(struct input_event));

            // 将触摸屏的信息读到这个结构体中
            read(fd_ts, &ts, sizeof(struct input_event));

            // 获取触摸屏的x轴和y轴的坐标值
            //  if(ts.type == 3 && ts.code == 0)
            if (ts.type == EV_ABS && ts.code == ABS_X)
            {
                // printf("x=%d ",ts.value); //x轴的坐标值  蓝色
                // printf("x=%d ",ts.value*800/1024); //x轴的坐标值  黑色

                x2 = ts.value;
            }
            // if(ts.type == 3 && ts.code == 1)
            if (ts.type == EV_ABS && ts.code == ABS_Y)
            {
                // printf("y=%d\n",ts.value); //y轴的坐标值 蓝色
                // printf("y=%d\n",ts.value*480/600); //y轴的坐标值 黑色

                y2 = ts.value;
            }
            // 松手后的事件
            if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
            {
                printf("up x2=%d y2=%d\n", x2, y2); // 调试代码
                break;
            }
        }

        // 查看滑动的状态
        if (x2 - x1 > 50)
            return RIGHT;
        // printf("right\n");
        if (x2 - x1 < -50)
            return LEFT;
        // printf("left\n");
        if (y2 - y1 > 50)
            return DOWN;
        // printf("down\n");
        if (y2 - y1 < -50)
            return UP;
        // printf("up\n");
    }
    // 关闭触摸屏
    close(fd_ts);

    return 0;
}

/*
    点击+滑屏算法的合并
*/
int get_click_slide(int *x, int *y)
{
    // 打开触摸屏文件
    int fd_ts = open("/dev/input/event0", O_RDWR);
    if (fd_ts < 0)
    {
        printf("open ts fail\n");
        return -1;
    }

    // 读写触摸屏(读出触摸屏里面的信息)
    struct input_event ts; // 官方的结构体(存储触摸屏的信息)
    int x1 = 0;            // x轴的值
    int y1 = 0;            // y轴的值
    int x2 = 0;
    int y2 = 0;

    while (1)
    {
        // 获取按下去的值
        while (1)
        {

            memset(&ts, 0, sizeof(struct input_event));

            // 将触摸屏的信息读到这个结构体中
            read(fd_ts, &ts, sizeof(struct input_event));

            // 获取触摸屏的x轴和y轴的坐标值
            //  if(ts.type == 3 && ts.code == 0)
            if (ts.type == EV_ABS && ts.code == ABS_X)
            {
                // printf("x=%d ",ts.value); //x轴的坐标值  蓝色
                // printf("x=%d ",ts.value*800/1024); //x轴的坐标值  黑色
                // x1 = ts.value*800/1024;
                x1 = ts.value;
                *x = x1;
            }
            // if(ts.type == 3 && ts.code == 1)
            if (ts.type == EV_ABS && ts.code == ABS_Y)
            {
                // printf("y=%d\n",ts.value); //y轴的坐标值 蓝色
                // printf("y=%d\n",ts.value*480/600); //y轴的坐标值 黑色

                y1 = ts.value;
                *y = y1;
            }

            // 按下去的事件
            if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 1)
            {
                printf("down x1=%d y1=%d\n", x1, y1); // 调试代码
                break;
            }
        }

        // 获取松手后的值
        while (1)
        {

            memset(&ts, 0, sizeof(struct input_event));

            // 将触摸屏的信息读到这个结构体中
            read(fd_ts, &ts, sizeof(struct input_event));

            // 获取触摸屏的x轴和y轴的坐标值
            //  if(ts.type == 3 && ts.code == 0)
            if (ts.type == EV_ABS && ts.code == ABS_X)
            {
                // printf("x=%d ",ts.value); //x轴的坐标值  蓝色
                // printf("x=%d ",ts.value*800/1024); //x轴的坐标值  黑色

                x2 = ts.value;
            }
            // if(ts.type == 3 && ts.code == 1)
            if (ts.type == EV_ABS && ts.code == ABS_Y)
            {
                // printf("y=%d\n",ts.value); //y轴的坐标值 蓝色
                // printf("y=%d\n",ts.value*480/600); //y轴的坐标值 黑色

                y2 = ts.value;
            }
            // 松手后的事件
            if (ts.type == EV_KEY && ts.code == BTN_TOUCH && ts.value == 0)
            {
                printf("up x2=%d y2=%d\n", x2, y2); // 调试代码
                break;
            }
        }

        if (x2 != 0)
        {
            // 查看滑动的状态
            if (x2 - x1 > 50)
                return RIGHT;
            if (x2 - x1 < -50)
                return LEFT;
            if (y2 - y1 > 50)
                return DOWN;
            if (y2 - y1 < -50)
                return UP;
        }
        else
        {
            return CLICK;
        }

        // 清空坐标值
        x1 = y1 = 0;
        x2 = y2 = 0;
    }

    // 关闭触摸屏
    close(fd_ts);

    return 0;
}

