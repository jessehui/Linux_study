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
