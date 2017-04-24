#include "stdio.h"
#include "sting.h"
#include "stdlib.h"
#include "unistd.h"

#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"

#include "fcntl.h"
#include "sys/epoll.h"

#define MAX_LISTEN_QUE 5
#define SERV_PORT 8888
#define MAX_BUFFER_SIZE 128
#define FD_MAXSIZE 1024
#define MAX_EVENTS

#define MCAST_PORT 8888
#define MCAST_ADDR "224.25.25.25"
#define MCAST_DATA "Multicast test"
#define MCAST_INTERVAL 3