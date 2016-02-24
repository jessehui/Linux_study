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
