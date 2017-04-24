# 进程间通信

1. 进程控制: 调用fork函数创建进程. 创建的两个进程, 在`用户空间`是不可能进行通信的. 只能在内核空间通信. 线程相当于房间, 可以实现用户空间的通信. 
2. "unistd.h" 是 C 和 C++ 程序设计语言中提供对 POSIX 操作系统 API 的访问功能的头文件的名称。是Unix Standard的缩写。该头文件由 POSIX.1 标准（单一UNIX规范的基础）提出，故所有遵循该标准的操作系统和编译器均应提供该头文件（如 Unix 的所有官方版本，包括 Mac OS X、Linux 等）。  
对于类 Unix 系统，unistd.h 中所定义的接口通常都是大量针对系统调用的封装（英语：wrapper functions），如 fork、pipe 以及各种 I/O 原语（read、write、close 等等）。
3. sys/types.h，中文名称为基本系统数据类型，此头文件还包含适当时应使用的多个基本派生类型。用  
`locate sys/types.h`定位该头文件位置.
4. 函数名: sleep  
头文件: #include <windows.h> // 在VC中使用带上头文件  
        #include <unistd.h>  // 在gcc编译器中，使用的头文件因gcc版本的不同而不同  
功  能: 执行挂起指定的秒数  
语  法: unsigned sleep(unsigned seconds);  

函数名: usleep  
头文件: #include <unistd.h>  
功  能: usleep功能把进程挂起一段时间， 单位是微秒（百万分之一秒）；  
语  法: void usleep(int micro_seconds);  
返回值: 无  
内容说明：本函数可暂时使程序停止执行。参数 micro_seconds 为要暂停的微秒数(us)。  
注 意：  
这个函数不能工作在windows 操作系统中。用在Linux的测试环境下面。  
参 见:usleep() 与sleep()类似，用于延迟挂起进程。进程被挂起放到reday queue。  
是一般情况下，延迟时间数量级是秒的时候，尽可能使用sleep()函数。  
如果延迟时间为几十毫秒（1ms = 1000us），或者更小，尽可能使用usleep()函数。这样才能最佳的利用CPU时间  


5. 









