1

应用层: web客户端 web服务器端
传输层: TCP协议 网络层: IP协议 两层都嵌入内核中
数据链路层: 以太网驱动程序

http:应用层协议 基于tcp

2

OSI七层模型: 应用层 表示层 会话层 传输层 网络层 数据链路层 物理层
TCP/IP协议族: 应用层                      TCP传输层  IP网络层   设备驱动程序和硬件
应用层可以利用socket套接字 将数据插入协议栈 然后发送出去

TCP 传输控制协议: 向用户提供可靠的全双工的传输字节流服务
UDP 用户数据报协议: 无连接的协议

3

服务器端工作工程:
绑定IPv4地址和端口号 bind
将套接字转换成监听套接字 listen
睡眠等待客户端连接
读取客户端数据

```C
//创建套接字
sockfd = socket(AF_INET,//IPV4 internet protocols
            SOCK_STREAM,//通信语义使用STREAM类型
            0);//specified protocols

```

 struct sockaddr_in{
   short sin_family;
   unsigned short sin_port;
   struct in_addr sin_addr;
   char sin_zero[8];

};

参数

sin_family

地址系列（必须是 AF_INET）。

sin_port

IP 端口。

sin_addr

IP 地址。

sin_zero

填充结构使其与 SOCKADDR 的大小一致。

4

```C
struct sockaddr {
unsigned  short  sa_family;     /* address family, AF_xxx */
char  sa_data[14];                 /* 14 bytes of protocol address */
};
```
sa_family是地址家族，一般都是“AF_xxx”的形式。好像通常大多用的是都是AF_INET。
sa_data是14字节协议地址。
此数据结构用做bind、connect、recvfrom、sendto等函数的参数，指明地址信息。

sockaddr_in和sockaddr是并列的结构，指向sockaddr_in的结构体的指针也可以指向

sockadd的结构体，并代替它。也就是说，你可以使用sockaddr_in建立你所需要的信息,
在最后用进行类型转换就可以了

5

int bind(int sockfd, const struct sockaddr *addr,
                socklen_t addrlen);

DESCRIPTION
       When a socket is created with socket(2), it
       exists in a name space (address family) but
       has  no  address  assigned  to  it.  bind()
       assigns the address specified  by  addr  to
       the socket referred to by the file descrip‐
       tor sockfd.

6

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

The argument addr is a pointer to  a  sock‐
       addr  structure.   This structure is filled
       in with the address of the peer socket,  as
       known  to  the  communications  layer.

7 段错误调试过程

```Bash
gcc -g -rdynamic server.c #用gcc编译带调试信息的可执行程序
gdb ./a.out     #调用gdb

(gdb)r          #run a.out
(gdb)where      #定位错误位置
```

8.

网络字节序:
The htons() function converts the unsigned short integer hostshort from
       host byte order to network byte order.
套接字地址结构:
通用地址结构:
```C
struct sockaddr{
     sa_family_t sa_family;     /* 地址族, AF_xxx */
     char            sa_data[14];        /* 14字节的协议地址 */
}
```
IPv4
```C
struct in_addr {
    unsigned long s_addr;
}
struct in_addr {
    unsigned long s_addr;
}
```
IPv6
```C
struct in6_addr {
      uint8_t s6_addr[16];    /* 128-bit IPv6 address */
                              /* network byte ordered */
  }
 #define SIN6_LEN            /* required for compile-time tests */


  struct sockaddr_in6 {
      uint8_t             sin6_len;            /* length of this struct (28) */
     sa_family_t            sin6_family;        /* AF_INET6 */
     in_port_t            sin6_port;            /* transport layer port# */
                                             /* network byte ordered */
     uint32_t            sin6_flowinfo;        /* flow information, undefined */
     struct in6_addr        sin6_addr;            /* IPv6 address */
                                             /* network byte ordered */
     uint32_t            sin6_scope_id;        /* set of interfaces for a scope */
 }
```

绑定端口的几个函数
```C
    server.sin_addr.s_addr = htonl(INADDR_ANY);//绑定服务器上所有网络接口
    //或者用inet_addr
    //server.sin_addr.s_addr = inet_addr("192.168.1.108");//把IP地址转换为网络字节序
    //或者用inet_aton
    //inet_aton("192.168.1.108",&server.sin_addr.s_addr);
    //或者用inet_pton IPv4或者IPv6都可以用
    //inet_pton(AF_INET,"192.168.1.108",&server.sin_addr);
```

从进程到内核传递地址结构的函数:
bind connect
从内核传递到进程:accept

9

socket函数
int socket(int domain,int type,int protocol)
type
SOCK_STREAM(字节流套接字) 对应的是TCP
SOCK_DGRAM(数据报套接字)  对应的是UDP
SOCK_RAW(原始套接字)

connect函数
服务器主机上 没有相应的端口与之连接(服务器进程未启动),称为硬错,收到RST,立马返回ECONNREFUSED

在发送请求的时候当前IP不可达错误,协议ICMP,称为软错(software error) 通常是发送arp请求无响应

listen函数 监听
int listen(int sockfd,int backlog)
backlog最大队列数量 已完成队列和未完成队列
close

10
```C
ssize_t recvfrom(int sockfd,//在服务器端用的哪个套接字

                 void *buf,//存放在哪里

                 size_t len, int flags,
                 struct sockaddr *src_addr, socklen_t *addrlen)//从哪里接收

ssize_t sendto(int sockfd, const void *buf, size_t len,int flags,
               const struct sockaddr *dest_addr,socklen_t *addrlen)
               //用某个套接字 发送某个buf中的数据 发送给某个地址的端口
```


11

GNU是一个自由操作系统，其内容软件完全以GPL方式发布。这个操作系统是GNU计划的主要目标，名称来自GNU's Not Unix!的递归缩写，因为GNU的设计类似Unix，但它不包含具著作权的Unix代码。
ssize_t send(int sockfd, const void *buf, size_t len, int flags);//类似write函数
ssize_t recv(int sockfd, void * buf, size_t len, int flags);//类似read函数
flags一般为0 特殊情况使用下列值

fork可以由一个进程产生多个子进程并发执行

12

multi-task: accept ==> fork 产生子进程
fork返回值: 成功返回0 失败返回-1
On success, the PID of the child process is returned in the parent, and
       0  is returned in the child.  On failure, -1 is returned in the parent,
       no child process is created, and errno is set appropriately.


exit - cause normal process termination
```C
      #include 'stdlib.h'

       void exit(int status);
```
关闭accept返回的已连接的套接字是为了节省资源
recv,recvfrom,recvmsg返回值:
       These calls return the number of bytes received,  or  -1  if  an  error
       occurred.   In  the  event  of  an  error, errno is set to indicate the
       error.

       When a stream socket peer has performed an orderly shutdown, the return
       value will be 0

13

首先内核会释放终止进程(调用了exit系统调用)所使用的所有存储区，关闭所有打开的文件等，但内核为每一个终止子进程保存了一定量的信息。这些信息至少包括进程ID，进程的终止状态，以及该进程使用的CPU时间，所以当终止子进程的父进程调用wait或waitpid时就可以得到这些信息。

而僵尸进程就是指：一个进程执行了exit系统调用退出，而其父进程并没有为它收尸(调用wait或waitpid来获得它的结束状态)的进程。

任何一个子进程(init除外)在exit后并非马上就消失，而是留下一个称外僵尸进程的数据结构，等待父进程处理。这是每个子进程都必需经历的阶段。另外子进程退出的时候会向其父进程发送一个SIGCHLD信号。

The  wait() system call suspends execution of the calling process until
one of its children terminates.  The call wait(&status)  is  equivalent
to:
```C
          waitpid(-1, &status, 0);


       #include <sys/types.h>
       #include <sys/wait.h>

       pid_t wait(int *status);

       pid_t waitpid(pid_t pid, int *status, int options);

```

 The value of pid can be:

 < -1   meaning wait for any child process whose  process  group  ID  is
        equal to the absolute value of pid.

 -1     meaning wait for any child process.

 0      meaning  wait  for  any  child process whose process group ID is
        equal to that of the calling process.

 > 0    meaning wait for the child whose process  ID  is  equal  to  the
        value of pid.

option value:
WNOHANG     return immediately if no child has exited.

</br>

14 IO

阻塞式IO: 例如recv 数据未准备好就等待 直到数据准备好 然后从内核空间复制到进程空间 耗费时间
非阻塞式IO: 调用一次就返回一次 可能有数据 也有可能没数据 比较耗资源
信号驱动IO: 注册SIGIO函数 系统调用 数据未准备好 不阻塞 返回. 直到数据准备好 进程捕获SIGIO. 系统再次调用 然后从内核空间复制到进程空间
IO复用: 调用select函数, 等待(可以等待多个套接字), 数据准备好后返回. 再调用recv函数从内核空间复制到进程空间
异步IO: 注册aio_read函数,系统调用, 数据未准备好 不阻塞 返回. 等待数据准备好 直接返回给该函数的某个缓冲区

IO复用示意图

(1)栈区（stack）— 由编译器自动分配释放 ，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈

(2)堆区（heap） — 一般由程序员分配释放，若程序员不释放，程序结束时可能由OS回收。注意它与数据结构中的堆是两回事，分配方式倒是类似于链表，呵呵。
(3)全局区（静态区）（static）—，全局变量和静态变量的存储是放在一块的，初始化的全局变量和静态变量在一块区域， 未初始化的全局变量和未初始化的静态变量在相邻的另一块区域。 - 程序结束后有系统释放
(4)文字常量区 —常量字符串就是放在这里的。 程序结束后由系统释放


```C
/* According to POSIX.1-2001 */
       #include 'sys/select.h'

/* According to earlier standards */
       #include 'sys/time.h'
       #include <sys/types.h>
       #include 'unistd.h'

       int select(int nfds, //等待的最大套接字的文件描述符+1
                      fd_set *readfds,//要读数据的套接字是哪些
                      fd_set *writefds,//要写数据的套接字是哪些
                      fd_set *exceptfds,//关注的套接字
                      struct timeval *timeout);//等待时间

//对fd_set进行操作
       void FD_CLR(int fd, fd_set *set);
       int  FD_ISSET(int fd, fd_set *set);
       void FD_SET(int fd, fd_set *set);
       void FD_ZERO(fd_set *set);

```
nfds is the highest-numbered file descriptor in any of the three  sets, plus 1.

Those  listed in  readfds  will  be watched to see if characters become available for reading (more precisely, to see if a read will not block;  in  particular, a file descriptor is also ready on end-of-file), those in writefds will be watched to see if space is available for write (though a  large write  may  still  block),  and  those in exceptfds will be watched for exceptions.

 Four  macros  are  provided to manipulate the sets.  FD_ZERO() clears a set.  FD_SET() and FD_CLR() respectively add and remove  a  given  file descriptor from a set.  FD_ISSET() tests to see if a file descriptor is part of the set; this is useful after select() returns.

套接字分配从最小的空闲的套接字开始,0,1,2分别对应标准输入 标准输出 标准错误 已被占用.
一个客户端对应一个套接字

15 IO复用高并发效率提高

利用epoll实现
函数:epoll_create, epoll_crl, epoll_wait

epoll_create: 创建epoll对象,int epoll_create(int size)
epoll_ctl: 增加/删除事件
epoll_wait:等待 直到注册的事件的发生

```C
int epoll_create(int size)

int epoll_ctl(int epfd, int op,//op参数:EPOLL_CTL_ADD,EPOLL_CTL_MOD,EPOLL_CTL_DEL
           int fd, struct epoll_event *event)
//fd: target file descriptor

//The struct epoll_event is defined as :

           typedef union epoll_data {
               void        *ptr;
               int          fd;
               uint32_t     u32;
               uint64_t     u64;
           } epoll_data_t;

           struct epoll_event {
               uint32_t     events;      /* Epoll events */
               epoll_data_t data;        /* User data variable */
           };

int epoll_wait(int epfd, struct epoll_event *events,int maxevents,int timeout)

```

16

accept函数是从等待接续的request中取出一个，并确立连接的函数。

一旦确立连接，新的Socket就被做成。和客户端的通信就是用那个新的Socket。

accept函数的定义
SOCKET t=accept(SOCKET s,struct sockaddr FAR* addr,int FAR* addrlen);
等待接续的队列中没有request时、一实行accept函数，程序就停在这里、然后一旦有接续要求，就再从这里开始运行

17

并发编程方法的比较
(1) ache模型(process per connection,简称ppc). tpc模型(thread per connection)
    各做各的事情
(2) select模型和poll模型
    效率低
(3) epoll模型
    只关注活跃的连接 效率高


####18

* 单播 unicast
* 任播 anycast    IPV6中提出
* 广播 broadcast 
* 组播(多播) multicast

广播组播都需要使用UDP 不能使用TCP

IPv4 地址的表示 {子网ID,主机ID} 例如192.168.1.104: 104表示主机地址

套接字选项
```C
int setsockopt(
SOCKET s,
int level,
int optname,
const char* optval,
int optlen
);
```
* level:(级别)： 指定选项代码的类型。
  - SOL_SOCKET: 基本套接口
  - IPPROTO_IP: IPv4套接口
  - IPPROTO_IPV6: IPv6套接口
  - IPPROTO_TCP: TCP套接口

* optname(选项名)： 选项名称
   SO_DEBUG 打开或关闭排错模式
   SO_REUSEADDR 允许在bind ()过程中本地地址可重复使用
   SO_TYPE 返回socket 形态.
   SO_ERROR 返回socket 已发生的错误原因
   SO_DONTROUTE 送出的数据包不要利用路由设备来传输.
   SO_BROADCAST 使用广播方式传送
   SO_SNDBUF 设置送出的暂存区大小
   SO_RCVBUF 设置接收的暂存区大小
   SO_KEEPALIVE 定期确定连线是否已终止.
   SO_OOBINLINE 当接收到OOB 数据时会马上送至标准输入设备
   SO_LINGER 确保数据安全且可靠的传送出去

* optval 代表欲设置的值, 参数optlen 则为optval 的长度. true or false, 1或0


###19 组播
组播IP地址:224.0.0.0 - 239.255.255.255(D类)
组播以太网地址(mac地址)开头高三个字节总是 01:00:5e
MAC地址有单播、组播、广播之分。
单播地址(unicast address)表示单一设备、节点，多播地址或者组播地址(multicast address、group address)表示一组设备、节点，广播地址(broadcast address)是组播的特例，表示所有地址，用全F表示：FF-FF-FF-FF-FF-FF。当然，三层的IP地址也有单播、组播、广播之分。
组播分为两个部分:
向下的组播数据流
组播控制流(IGMP协议v1,v2,v3):分三种报文 report(join),leave, query.

client:
IP_MULTICAST_LOOP
IP_ADD_MEMBERSHIP
IP_DROP_MEMBERSHIP


###20 原始套接字

创建:
socket函数
int socket(int domain,int type,int protocol)
type
SOCK_STREAM(字节流套接字) 对应的是TCP
SOCK_DGRAM(数据报套接字)  对应的是UDP
SOCK_RAW(原始套接字)
```C
int socket(AF_INET,SOCK_RAW,protocol)//原始套接字创建
```

输出:
```c
ssize sendto(int sockfd, const void *buf, size_t len, int flags, 
const struct sockaddr *dest_addr, socklen_t addrlen) 
```

输入:
```c
ssize recvfrom(int sockfd, const void *buf, size_t len, int flags,
const struct sockaddr *src_addr, socklen_t addrlen)
```

哪些情况内核会将接收到的IP数据报传递给原始套接字(原始套接字只处理到IP层)
* 接收到的TCP, UDP不会, 这两者是传输层
* ICMP分组会在内核处理完其中的ICMP消息之后传递原始套接字
* IGMP同上
* 内核不认识其协议字段的IP数据报


###21 ICMP,IGMP

(1) 
ICMP（Internet 控制消息协议，Internet Control Message Protocol）协议用来给IP协议提供控制服务，允许路由器或目标主机给数据的发送方提供反馈信息。需要发送反馈信息的情况包括：数据包不能被发送到 目标主机，路由器缓冲区溢出导致数据包被删除，路由器想要把流量重定向到另外一个更短的路由上等。ICMP协议是IP协议的一部分，任何实现了IP协议的 设备同时也被要求实现ICMP协议。 
(2)
IGMP（互联网组管理协议）是一种互联网协议，提供这样一种方法,使得互联网上的主机向临近路由器报告它的广播组成员。 广播使得互联网上的一个主机向网上确认对于源主机发送内容感兴趣的计算机发送信息。

IP 不能提供差错控制和辅助机制（如：主机的管理和查询）！
为此，ICMP很好的承担了这个任务！
ICMP是网际控制包协议，它的功能是：差错报告和查询
ICMP发送的ICMP包并不能直接交到下1层，必须在加IP的包头！
ICMP的包分两类：1是差错报告包2是查询包


###22 ARP, RARP
* 在以太网（ARP协议只适用于局域网）中，如果本地主机想要向某一个IP地址的主机（路由表中的下一跳路由器或者直连的主机，注意此处IP地址不一定是IP数据报中的目的IP）发包，但是并不知道其硬件地址，此时利用ARP协议提供的机制来获取硬件地址，具体过程如下：

1) 本地主机在局域网中广播ARP请求，ARP请求数据帧中包含目的主机的IP地址。意思是“如果你是这个IP地址的拥有者，请回答你的硬件地址”。

2) 目的主机的ARP层解析这份广播报文，识别出是询问其硬件地址。于是发送ARP应答包，里面包含IP地址及其对应的硬件地址。

3) 本地主机收到ARP应答后，知道了目的地址的硬件地址，之后的数据报就可以传送了。

点对点链路不使用ARP协议。

* RARP：逆地址解析协议
将局域网中某个主机的物理地址转换为IP地址，比如局域网中有一台主机只知道物理地址而不知道IP地址，那么可以通过RARP协议发出征求自身IP地址的广播请求，然后由RARP服务器负责回答。RARP协议广泛应用于无盘工作站引导时获取IP地址。

RARP允许局域网的物理机器从网管服务器ARP表或者缓存上请求其IP地址。
