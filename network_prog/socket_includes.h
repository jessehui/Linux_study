#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"

#include "unistd.h"
#include "fcntl.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/wait.h>

//最大监听队列
#define MAX_LISTEN_QUE 5
//server port 
#define SERV_PORT 8888
//return value if error occcurs
#define RT_ERR (-1)
