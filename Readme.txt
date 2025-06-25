arm开发版-ubantu服务器-ubantu客户端实现互撩（表情互撩）


多人聊天系统
项目简介
这是一个基于TCP协议的多人聊天系统，允许多个客户端连接到服务器并进行实时聊天。系统支持用户注册、登录、查看在线用户列表和发送表情等功能。
功能描述
用户注册：新用户可以注册账号。
用户登录：已注册用户可以登录系统。
查看在线用户：用户可以查看当前在线的用户列表。
发送表情：用户可以发送预设的表情（如抱拳、笑脸、郁闷等）。
环境要求
操作系统：Linux
编译器：GCC (GNU Compiler Collection)
库：glibc 2.28 或更高版本
编译和运行
编译
确保已安装GCC编译器和必要的开发库。
在项目根目录下打开终端。
使用以下命令编译服务器和客户端代码：

采用多任务并发服务器（1024个client容量）（在listen后面用多线程，实际上就连接两个线程）连接客户端（accept），信息存储进结构体（struct sockaddr*）指针里面，连接成功，把信息加入链表（client_list），信息在加入链表的时候应该加上mutex锁保证不会发生信息践踏，
pthread创建的时候应该往线程里面传入client_sock[i]和




//实现思路如下

//链表信息如何及时更新
thread1：第一个加入，链表更新1，
thread2：第二个加入，链表更新2




//arm开发板
进行与server连接，连接成功在开发板terminal上打印（connect sever success）

//逻辑结构
while(1)
{
初始就是登录界面（包含键盘和注册）
//登录界面，按钮识别

注册按钮：——转入新界面（register）
结构体login{
int password;
int id;
int flag;(用来标志是register还是login)
int flag_login;(标志是否登录成功)
}

bzero(清空结构体)
输入id，password，点击确认——发送信息（结构体login），server接受结构体login（新建链表，login(password,id都用整形），write==sizeof(struct register),写入成功就返回登录界面，continue

登录识别：输入id，password（只允许输入3位id，password）




输入的id，password存储进入struct login，点击登录的时候flag=1，远程server识别flag==1然后遍历链表login_list，遍历发现存在匹配的id和password就往回发送flag_login=1，client识别flag_login==0(continue),->flag_login==1（进入用户界面)


进入用户界面:直接发送结构体login给server,让server识别到login状态，然后进入第二段read（struct message）

如何发送接受链表信息：send_client_list连续发送结构体,发送一个结构体，就入一个链表






}





