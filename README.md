# Linux Study Notes

<br/>
<br/>
1
<br/>
Kernel: 内核 包裹在硬件之上 控制系统程序与硬件之间打交道的功能
Shell: 包裹在内核之上 提供人机交互功能 类似Windows CMD功能
不同Shell 对命令的解释不一样 e.g. Bourne Shell(Sh), C Shell (Csh), Bourne-Again Shell(Bash)
不同Shell命令提示符不一样
sh,bash: #root      $user
csh:        #root      %user

ubuntu
GUI转命令行:ctrl+alt+F2/F3/F4
命令行转GUI:ctrl+alt+F7
<br/>
<br/>
2 文件系统
<br/>
定义:操作系统中封装的系统服务程序,实际上是一个软件程序,用来存储和管理计算机文件和资料
(1)EXT3
基于日志方式的文件系统.每个文件都有索引 用户对文件的每一个操作都会记录日志,行成一个任务队列排着执行 性能比较好
(2)SWAP
交换分区的文件系统 类似Windows虚拟内存
虚拟内存的实现方式:
内存空间不足时 把硬盘的部分空间作为内存;
进行内存的排列像内存池一样,进行一个优化
SWAP就是Linux的虚拟内存

特点:
一切皆文件(硬件设备,文件夹)
以颜色和字母标示文件类型: 蓝色 表示目录文件(d); -表示普通文件; 浅蓝绿色 表示链接文件(l) 指向某个连接;
绿色 可执行文件(- 普通文件);黄色 字符设备(c); 紫红色 socket文件(s)

```Bash
pwd #显示当前目录
ls #列出当前目录下的文件
ls -l #以长内容显示
cd / #回到根目录
```
目录结构:
Linux磁盘逻辑结构管理物理结构 格式化将磁盘分为很多文件块区
Windows物理结构管理逻辑结构 先分区再格式化建立结构

/bin 一般用户可用的 可执行的 系统的指令
/boot 引导 开关设定
/dev 设备文件 硬盘 光驱
/etc 配置目录 相关配置文件
/home 用户主目录 每个用户名都可以建立目录
/lib 库文件 模型库 函数库 各种版本的模组
/media 光驱 软驱 媒体
/sys 系统和兴
/srv 网络服务提供的资料
/sbin 用户可执行的程序
/proc 核心的进程程序
/opt 第三方软件
/usr 用户相关文件
/var 变量文件

Linux: / Windows: \
<br/>
<br/>
3 命令
<br/>
命令名 空格 选项(可选) 空格 参数
命令区别大小写

别名:
alias 别名 = ‘value' 建立别名
alias 显示所有别名
unalias 别名 表示取消别名
可以两个命令一起用一个别名表示e.g.
```Bash
alias test = ‘cd;ls’ #回到主目录 并显示所有文件
```

通配符:用于代替字符 *,?,[ ]
*: 通配0个或多个字符 ?:通配任意单个字符 [ ]:通配一个范围内的任意字符
; : 一行执行多条命令

输入输出重定向:
输出>,>>:
>:将一个命令的输出放入文件而非屏幕
>>:输出重定向 但不会把源文件覆盖 在源文件末尾追加

cat 查看文件内容
```Bash
cat < test1.txt > test2.txt #复制test1.txt中的内容到test2.txt中
```
```Bash
cat < /dev/stdin > test.txt     #标准输入设备 输出到test.txt
```

管道符:| 将一个进程的输出 作为另一个进程的输入
```Bash
ls -l /etc | more # 分页显示
```
```Bash
cp /dev/stdin test3.txt #把接下来输入的文本拷贝到test3.txt文件中
man      #+ 命令 查看帮助文档
clear     #清屏
history n  #最近使用的n条命令
!n          #执行历史记录的第n条命令
```

```Bash
cd ~ #用户主目录
cd .. #父目录
cd ~username #+用户名可以跳转到指定用户的根目录
cd / #系统根目录

ls -a #显示所有文件 包括隐藏文件
ls -F #显示文件类型
ls -R #列出当前开始的所有子目录,文件并一层一层显示下去
ls -t #以修改时间倒序显示所有文件和目录

file filename #显示文件具体类型
```
<br/>
<br/>
4 文件
<br/>
```Bash
mkdir -p dir2/dir3      #本身没有的目录 新建用-p参数 (parent) 在需要的情况下建立父目录
rm -r dir                    #删除目录
rmdir                         #删除空目录
rm file                       #删除文件
rm -f                         #强力删除
rm -rf                        #等效 rm -r -f
```

文件都有文件名和数据. Linux上被分成两个部分 用户数据(userdata) 和元数据(metadata)
用户数据: 文件数据块 记录文件真实内容的地方
元数据: 记录附加属性 文件大小 创建时间 所有者信息等
linux元数据中的iNode号才是文件的唯一标示而非文件名 iNode号即索引节点号
<br/>
<br/>
5 链接
<br/>
为解决文件共享问题 Linux系统引入链接 同时带来了隐藏文件路径 增加权限安全 节省存储等好处
硬链接(hard link) : 一个iNode号对应多个文件名, 则称这些文件为硬链接, 就是一个文件使用多个别名.只能在同一个文件系统中链接,
软链接(soft link or symbolic link) : 若文件用户数据块中存放的内容是另一个文件路径名的指向,则该文件就是软链接文件.本身就是个普通文件, 只是数据块内容比较特殊. 软链接本身有自己的iNode号和数据块 类似Windows的快捷方式. 红色代表死链接, 源文件不存在

```Bash
ln      -s/-P     source_file      target_file           #建立硬链接(-p),软链接(-s)
```

6显示文件内容

```Bash
cat < /dev/stdin > test.txt     #标准输入设备 输出到test.txt
cat /dev/null > test.txt          #清空test.txt
cat filename                         #不分屏显示文件内容
more filename                     #分屏显示文件内容
\                                            #换行符号
head -n filename               #显示文件前n行
tail -m filename               #显示文件后m行
```

7
```Bash
cp [-i] source_file  target_file      #拷贝文件到另一个文件中
cp [-i] source_file  target_directory          #拷贝文件到一个目录中
cp -r  source_dir   target_dir               #拷贝目录

mv [-i] source_file target_file       #移动或者重命名文件
mv [-i] source_file  target_directory #移动文件到目标目录
```
-i: 询问是否覆盖选项

8 权限
r 读权限 w 写权限 x 可执行权限 - 无权限
权限所属对象: 拥有者(u) 同组人(g) 其他人(o) 所有人(a)
```Bash
jesse@ubuntu:~$ ls -l
total 256
drwxrwxr-x 2 jesse jesse  4096  2月 22 16:29 arm      #权限按 拥有者 同组人 其他人 顺序排列 -代表无权限
```

chmod 修改文件权限 注意必须是文件
(1) 使用字母
who: u,g,o,a
operation: =(设置),+(添加),-(删除)
permission: r, w, x
```Bash
chmod a+w test.txt      #所有人都加上写权限
chmod u+w, g+w, o+r test.txt #同时设置加逗号
```
设置为可执行时 文件会变成绿色

(2) 使用数字
r w x
0 0 0  无权限
1 1 1  有权限
```Bash
chmod 555 test.txt #三部分人都拥有5所对应的权限 即101 即可读不可写可执行文件
```
ubuntu新建文件默认权限 664 (拥有者和同组人 可读可写不可执行)

chown 更改某个文件或目录的属组和属主 可用于授权
-R 递归的改动目录下所有文件和子目录的拥有者
chown [-选项]  要指定的用户或组 文件
```Bash
chown -R zhangsan  Users/media
```

chgrp 改动文件或 目录所属的组
chgrp [-选项] group filename
-R 递归的改动目录下所有文件和子目录的属组
```Bash
chgrp -R book /opt/local/book          #改动/opt/local/book 及其子目录下所有文件属组为book
```

9 查找
find 查找文件和目录
find path expression 内容
e.g.
```Bash
find / -name b*     #在根目录下按名字查找以b开头的文件
find . -mtime 10 -print      #在当前目录下查找修改时间在距今10天之内的文件 并打印出来
find ~ -perm 777 > ~/holes     #在用户主目录下查找权限为777(任何人可读可写可执行)的文件\
并将结果打印到holes文件中
find /etc -user 0 -size +400 -print #在/etc目录下的user ID为0, 大小大于400的文件 并打印
```

locate 他会去保存文件和目录内容的数据库里查找合乎范本样式条件的文件和目录
速度快很多 他是通过iNode文件索引来找 他会把文件索引维护在一个数据库里

grep 查出包含某些字符串的结果 对文件或输出结果进行过滤 大小写敏感
grep [-options] string filename
-i 忽略大小写      -v 反向过滤
```Bash
ls -la | grep -i ’sep 18’      #列出目录下的所有结果 然后传输给grep命令 查出包含sep 18字符串的所有文件
ls test*.txt | xargs grep .profile     #列出以test开头的所有txt文件 分别(参数xargs)传给过滤命令grep \
显示含有.profile的字符串
```

wc 统计文件或输出结果
wc [options] filename
-l 统计行 -w 统计多少单词 -c 统计多少个字符
e.g.
```Bash
grep li /etc/passwd | wc -l     #过滤/etc/passwd中包含li字符串的所有文件 把结果传送给wc 统计有多少行
```
ps列出当前系统中已在运行的进程
进程: 一个能完成一定功能的程序
-e 列出正在运行的进程
-f 列出完整的进程列表
-U 查找由某个用户启动的进程

10
su 用户名 跟上要切换的用户名
shutdown 安全地关闭或者重启计算机
-h 将系统关机
-r  shutdown后重新启动
e.g.
```Bash
shutdown -r +10 #系统在10分钟后关机 并重新启动
shutdown -h now #系统马上关机并重新启动
```
who 查看用户详细信息
whoami 查看当前用户自己的用户名
who am i 查看当前用户自己的信息
users 查看当前已经登录到系统中的用户

du 显示磁盘使用的摘要信息 默认以block为单位方式显示
-k 以k字节显示 -m以m字节方式显示
1k字节 = 2个block

df 显示整个文件系统的空间使用磁盘情况

11 网络
ping 查看当前机器与另一台机器的联通情况
ping 主机名/IP

ifconfig 查看和配置当前机器的网络参数信息
```Bash
ifconfig eth0 up(down)      #激活或者关闭某个网络适配卡
ifconfig eth0 [ipaddress] netmask [address] #设置IP和子网掩码
```


12
软件安装包: rpm主要是redhat deb主要是ubuntu下边的
安装卸载方式:
```Bash
#dpkg 离线安装和卸载
dpkg -i [package] #安装
dpkg -p [package] #卸载

#aptitude 程序包在线安装
apt-get install <package> #安装
apt-get remove -purge <package> #完全卸载
```

vi的使用模式: 命令模式 插入模式 末行模式
命令模式(光标移动 文本选择)
h,j,k,l,(左,下,上,右)
G调到尾部 1G顶部 n+向下移动n行 n-向上移动n行
x删除光标前的字符 dw删除当前词 dd删除当前行
yw 复制光标所在的一个词 yy复制当前行 p从当前向下粘贴

最后行模式
```Bash
:[n1], [n2]co[n3] #n1 和n2复制到n3行之后
:[n1], [n2]m[n3] #n1 和n2移动到n3行之后

w #保存
w filename      #存成新文件
q #退出
ql #强行退出不保存
wq #保存并退出

:set nu #显示行号
:set nonu #隐藏
```

13
io: 文件IO, 目录IO, 标准IO
文件IO: open(), write(), read(),close()
open(char *, flag, mode);//包含文件名和路径;打开文件的方式;创建文件的权限
成功返回文件描述符,即文件的ID号(iNode 内核中的表示) 出错返回-1
程序刚刚启动的时候，0是标准输入，1是标准输出，2是标准错误。如果此时去打开一个新的文件，它的文件描述符会是3。POSIX标准要求每次打开文件时（含socket）必须使用当前进程中最小可用的文件描述符号码，因此，在网络通信过程中稍不注意就有可能造成串话。

利用open函数创建的文件权限并不是设置为多少就是多少. 而且与umask(掩码)有关.

main(int argc, char *argv[ ], char **env)才是UNIX和Linux中的标准写法。
argc: 整数,用来统计你运行程序时送给main函数的命令行参数的个数
* argv[ ]: 字符串数组，用来存放指向你的字符串参数的指针数组，每一个元素指向一个参数
**env:字符串数组。env[ ]的每一个元素都包含ENVVAR=value形式的字符串。其中ENVVAR为环境变量，value 为ENVVAR的对应值。

```Bash
int main(argc, char *argv[], char**env)
```

设置权限为:
```Bash
fd = open(argv[1],//文件名，路径
          O_CREAT | O_RDWR, // 表示新建一个文件 同时可以以读写方式打开
            777); // 新建文件的权限 777 所有可读可执行可写
```
掩码为(异或运算):
```Bash
jesse@ubuntu:~/Git/Linux/io_prog$ umask
0002
```
0777(10) = 000 111 111 111 (2)
0022(10) = 000 000 010 010 (2)

                  000 111 101 101 (2)
更改掩码 umask 0000即可

open函数第二个参数 flag  打开文件方式:
O_RDONLY 只读
O_WRONLY 只写
O_RDWR 读写
O_CREAT 创建一个文件
O_APPEND 追加方式打开文件 不会把已经存在的文件删除
O_TRUNC 打开文件 会把已经存在的内容删除
O_EXCL 使用O_CREAT时文件存在 则返回错误信息. 这一参数可以来测试文件是否存在. 如果不加的话 只有O_CREAT则都会创建成功

14 write(),read()函数
并不是想读多少 想写多少就能读/写多少
```Bash
write(int fd, // 向哪一个文件中写
         void *buf, //向文件中写什么内容
         size_t count // 向文件中写多少个
)
//返回值: 实际写的字节数

read( int fd, // 从哪一个文件中读
         void *buf, //读到哪里去
         size_t count // 向文件中读多少个
)
//返回值:实际读的字节数
```

15 快捷键:
ctrl+a:光标移到行首。
ctrl+b:光标左移一个字母
ctrl+c:杀死当前进程。
ctrl+d:退出当前 Shell。
ctrl+e:光标移到行尾。
ctrl+h:删除光标前一个字符，同 backspace 键相同。
ctrl+k:清除光标后至行尾的内容。
ctrl+l:清屏，相当于clear。
ctrl+r:搜索之前打过的命令。会有一个提示，根据你输入的关键字进行搜索bash的history
ctrl+u: 清除光标前至行首间的所有内容。
ctrl+w: 移除光标前的一个单词
ctrl+t: 交换光标位置前的两个字符
ctrl+y: 粘贴或者恢复上次的删除
ctrl+d: 删除光标所在字母;注意和backspace以及ctrl+h的区别，这2个是删除光标前的字符
ctrl+f: 光标右移
ctrl+z : 把当前进程转到后台运行，使用’ fg ‘命令恢复。比如top -d1 然后ctrl+z ，到后台，然后fg,重新恢复
esc组合
esc+d: 删除光标后的一个词
esc+f: 往右跳一个词
esc+b: 往左跳一个词
esc+t: 交换光标位置前的两个单词。

16 lseek()函数
调整读写的位置指针
```C
lseek( int fd, //文件描述符
          off_t offset, //偏移量,每一个读写操作需要移动的距离
          int whence // 当前位置的基点
           //三个标志: SEEK_SET(当前位置为文件开头,新位置为偏移量的大小)
          //SEEK_CUR: 当前位置为文件指针的位置, 新位置为当前位置加上偏移量
          //SEEK_END: 当前位置为文件的结尾, 新位置为文件的大小加上偏移量的大小
)
//成功返回:文件当前位置 出错返回:-1
```

VIM 复制粘贴方法:
鼠标选择 然后 按y
鼠标放到需要粘贴的地方 按p

17
文件IO: 直接调用内核提供的系统调用函数 头文件 “unistd.h"
标准IO: 间接调用系统调用函数 头文件”stdio.h”
printf,scanf, putchar, put, getchar,get与普通文件的读写没有关系 他们不能读写普通文件

缓存类型:
user 用户空间缓存
kernel 内核空间缓存
标准IO的库函数 还有一个缓存 叫库缓存 lib buffer
库缓存特点: printf遇到\n才会将库缓存的内容写到内核中, 即调用系统函数
库缓存写满时 才会调用系统函数 将lib buffer 写到 kernel buffer中去

标准IO: fopen(), fclose(), fseek(), 读写函数较多, 分三类, 全缓存, 行缓存, 无缓存

```Bash
FILE *fopen(const char *path, const char *mode);
//返回值: FILE * 文件流指针, 类似文件IO中的文件描述符(文件IO中指内核空间中的文件在进程里对应的ID号)
```

参数mode(字符串 加引号): 打开文件方式
b: 二进制文件
r:只读方式打开, 文件必须存在
w/a: 只写方式打开文件, 文件不存在则创建 区别: W类似 O_TRUNC(先删除), A类似O_APPEND(原来基础上添加)
+: 读写方式打开文件, 文件必须存在

fopen函数生成文件的权限跟umask有关

18 读写函数
三类: 行缓存, 无缓存, 全缓存
行缓存: 遇到新行符(\n) 或写满缓存时 则调用系统函数
e.g. fgets, gets, scanf(读)
fputs, puts, scanf, printf, fprintf, sprintf

无缓存: 只要用户调用这个函数, 就会将其内容写到内核中

全缓存: 只有写满缓存才会调用系统函数 如fread, fwrite

不管用哪种缓存, 只要调用了fclose(), 在该文件被关闭之前, 刷新缓存中的数据. 如果标准IO已经为该流自动分配了一个缓存,则释放此缓存.

fputs, fgets:
char *fputs(const char *s, FILE *stream);//写命令
第一个参数 缓存 即写什么内容
第二个参数 文件流 写到哪里
返回值: 成功返回非负值 出错返回EOF

char *fgets(char *s, int size, FILE *stream);//读命令
第一个参数 读到哪个字符串里
第二个参数 读多少字节
第三个参数 从哪个文件中读
返回值: 成功则返回s(缓存的地址) , 如果出错返回NULL

fflush(FILE *fp); 把库函数中的缓存内容强制写到内核中去
( fclose()函数中包含fflush() )

```C
fputs("hellow linux\n", stdout);//或者不加\n 而加上fflush函数
    //或者
    //fputs("hellow linux",stdout);
    //fflush(stdout);

     //或者
     //fputs(“hellow linux”,stderr);//也可以显示
```
所以, stdout是行缓存的, 而stderr是无缓存的

19
fseek()函数和lseek()函数参数类似 第一个为要调整的文件 第二个为偏移量 第三个为基准(SEEK_SET,SEEK_END,SEEK_CUR)
lseek()返回值为当前文件的位置指针 fseek()返回值成功返回0,失败返回-11

rewind(FILE *fp)等价于 (void) fseek(fp,0,SEEK_SET)
用于设定流的文件位置 指示为文件开始

ftell( FILE *fp ) 用于取得当前的文件指针 调用成功则返回当前文件位置 失败返回-1

20
char *gets( char *s )//读
与fgets 相比 (1)不能指定缓存的长度 可能造成缓存越界 (2)只能从标准输入中读 (3)gets不将换行符存入缓存

int puts(const char *s)//写
puts只能向标准输出中写 puts输出时会自动添加换行符 fputs不会

fprintf(FILE *stream,”string") 可以输出到显示器 也可以输出到文件 行缓存

int sprintf(str *, “string”) 输出内容到一个字符串中 经常用在数据库语言中 行缓存
