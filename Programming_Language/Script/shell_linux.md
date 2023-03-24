# SHELL & LINUX

> ref:
>
> [阮一峰bash教程](https://wangdoc.com/bash/)

## shell

> dash means `-`

### navigate around

Option + f/b: move a word forward/backword

> iTerm2: go to Preferences -> Profiles -> Keys -> Left/Right Option Key -> set to `Esc+`
>
> vscode: `"terminal.integrated.macOptionIsMeta": true`

Ctrl + e/a: move to the end/start of the line

### 命令基本格式

`command flag 参数`参数只有一个单词，如果想要输入词组，需使用"",flag是命令的一些选项，starts with dash -

### 一些特殊的文件夹
`/dev/null`： 在类Unix系统中，/dev/null，或称空设备，是一个特殊的设备文件，它丢弃一切写入其中的数据（但报告写入操作成功），读取它则会立即得到一个EOF。它又被被称为位桶(bit bucket)或者黑洞(black hole)。空设备通常被用于丢弃不需要的输出流，或作为用于输入流的空文件。

### getting help
1.  `cmd --help`
2.  `man cmd`
3. [TLDR pages](https://tldr.sh) Simplified and community-driven man pages

### basic Info
#### 输入输出重定向

change stream input and stream output
`>`:change stream output
`<`:change stream input

```bash
echo hello > hello.txt
cat < hello.txt > hello2.txt
# equivalent to cp command
```
`>>` means append	`>`will overwrite

<img src="https://img-blog.csdnimg.cn/20190514150119510.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdWN5MDA3,size_16,color_FFFFFF,t_70" style="zoom:80%;" />

<img src="https://img-blog.csdnimg.cn/20190514150920867.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdWN5MDA3,size_16,color_FFFFFF,t_70" style="zoom:80%;" />

还有一个冷门的类似特性是 进程替换（process substitution）， `<( CMD )` 会执行 `CMD` 并将结果输出到一个临时文件中，并将 `<( CMD )` 替换成临时文件名。这在我们希望返回值通过文件而不是STDIN传递时很有用。例如， `diff <(ls foo) <(ls bar)`: 会显示文件夹 foo 和 bar 中文件的区别

#### heredoc

```shell
cat <<EOF
This is coming from the stdin
we can write multiple lines
EOF
```

heredoc is originating in Unix shells, is `<<` followed by a delimiting identifier (often the word *EOF* or *END*), followed, starting on the next line, by the text to be quoted, and then closed by the same delimiting identifier on its own line

the content of the document is redirected to stdin(standard input) of the preceding command

#### pipe

The `|` 使得 output of one is the input of another.
`ls -l / | tail -n1`
将ls -l的内容输入到tail中，而tail输出尾部10行
常与`xargs`搭配使用

#### ctrl+l

control+l can clear the terinmal(actually not clear just go to the top of it)

#### ;

`;` 在同一行执行多个命令

#### regular expression

[a-z] \[\^abc](except)

a\* zero or more a+ one or more

| `a(?=b)`  |  Match `a` in `baby` but not in `bay`   |
| :-------: | :-------------------------------------: |
| `a(?!b)`  |  Match `a` in `Stan` but not in `Stab`  |
| `(?<=a)b` | Match `b` in `crabs` but not in `cribs` |
| `(?<!a)b` |   Match `b` in `fib` but not in `fab`   |

### commands

#### ls

- `ls -l`
  <img src="note_img/ls_l.png" style="zoom:80%;" />
  
  还可以用来查看某个文件是否软链接指向另外一个文件
  
- glob

    ls使用[glob](https://tldp.org/LDP/abs/html/globbingref.html)而不是regex的方式匹配文件名

    - *多个字符，?匹配单个字符

    - [a, b, c]匹配a or b or c

        ```
        [[:upper:]] or [A-Z]
        [[:lower:]] or [a-z]
        [[:digit:]] or [0-9]
        [[:alpha:]] or [a-zA-z]
        [[:alnum:]] or [a-zA-Z0-9]
        ```

    - $ for ending character

    - {} 可以匹配多个glob pattern

        > 多个pattern之间用逗号连接，但不要带空格

#### which

`which` 在$PATH中，查找系统命令的位置（shell built in command是查不到的）

> shell执行命令的基本途径，先找是否是shell built in command 再去PATH中找是否有这条命令

#### mkdir

`mkdir -p` -p 确保目录名称存在，不存在的就建一个。

> mkdir -p wxp/test 在工作目录下的wxp目录中建立一个test目录，若不加-p，则若wxp不存在，便会报错。

#### find

find directory options expression

options:

1. -type f: file d: directory l: symbolic link c: character special device file
2. -name * matches multiple character ? matches a single character

> 将当前目录及其子目录下所有文件后缀为 .c 的文件列出来:
> \# find . -name "*.c"
>
> 列出空文件
>
> \# find . -size 0

#### crontab

`crontab`   ref: [Linux Crontab 定时任务](https://www.runoob.com/w3cnote/linux-crontab-tasks.html)    [Linux crontab 命令](https://www.runoob.com/linux/linux-comm-crontab.html)

别忘了输出重定向，crontab默认会将输出信息（包括error message）发送至mail文件夹中，比如`/var/mail`（我的mac） 或者 `/var/spool/mail`。

<img src="https://www.linuxprobe.com/wp-content/uploads/2017/01/how-cron-task02.jpg" style="zoom:67%;" />

*/3  每过3分钟/小时/...

/path/to/script要写绝对路径，且script中的命令要写绝对路径，比如`/usr/bin/du`，写文件的话文件尽量也写绝对路径。

> ubuntu的mail好像没有，导致邮件发不出去。
>
> 可以用这个查看`grep CRON /var/log/syslog` 输出来debug。毕竟这玩意儿的stderr会发到邮件里，而邮件文件夹很可能找不到。。。

#### df

df 显示所有文件系统和它们的磁盘使用情况（-h以 human readable的方式）。

#### du

`du` disk usage用于查看目录或文件大小。

`du -hd N 目标文件夹 | sort -hr`  列出一个目录和任何子目录的可读大小，最深可达 n 级。并排序。

#### ps

[ps查看进程](https://www.linuxprobe.com/linux-look-process.html)

- ps aux | less 查看所有进程并分页显示。

- ps -A。

- ps -u user 查看user的进程。

- kill掉指定的thread

    ps -a | grep "identity_string" | awk  "{print $1}" | xargs kill -9

#### grep

grep 字符串匹配。

grep search_pattern -x (completely match)

1. [path/to/file1 path/to/file2 ...] 找到文件中包含这个字符串的东西，并高亮输出。
2. \* 查找directory下的所有文件

也可以通过管道输入 ... | grep "search_pattern"

#### fdisk

查看挂载的磁盘，以及磁盘分区。

`fdisk -l`

#### tail

Display the last part of a file.

-f 持续查看文件直到ctrl+c

`tail -f /var/log/syslog` 查看系统log，包括新usb设备的插入等等。

#### lsusb

显示usb设备连接情况。

-t 可以显示usb的驱动信息。

#### dmesg

显示内核信息。

#### scp

transport file or directory

`scp -r (if directory) /local/path/to/file user@ip:/remote/path/to/file`

#### rsync

rsync path/to/local_file remote_host:path/to/remote_directory

rsync -a path/to/dir**/** remote_host:path/to/remote_directory

如果没有上面dir最后那一个slash，就会将dir添加到remote_directory下面

> `-a` flag, which is a combination flag and stands for “archive”. This flag syncs recursively and preserves symbolic links, special and device files, modification times, groups, owners, and permissions. It’s more commonly used than `-r` and is the recommended flag to use

#### netstat

determine which process is using a port

`netstat -ltnp | grep -w ':$port_num'`

l: tell netstat 

#### ip

**modern replacement of the classic (and now deprecated) `ifconfig`**

you can adjust the way a Linux computer handles IP addresses, network interfaces controllers (NICs), and routing rules. The changes also take immediate effect—you don’t have to reboot.

## shell script

> most is based on BASH

### Shebang 行

> sharp means `#` bang means `!`

#!（空格可有可无）脚本解释器的位置（也可以是perl或者Python） 放在.sh的第一行。

然后就可以在终端中直接用`./file.sh`调用脚本。

如果没有，就需要自己指定，或者将使用`$SHELL`执行该脚本。

### 变量

定义变量：

1. In most cases it is enough with an implicit declaration in `bash`

2. sometimes you want a variable's value to only be integer

    ```bash
    declare -i num
    declare -i num=15
    ```

    or arrays

    ```bash
    declare -a asdf   # indexed type
    ```

1. `''`定义的字符串为原意字符串 `""`定义的字符串会进行转义 \` \` 反引号中可以输入bash的命令（可以用`$(cmd)`替换，而且后者更好，因为它可以嵌套命令`$(... $())`）
> Be careful about the SPACE
2. 使用已定义过的变量 `$var`

   此时会做直接替换，所以如果这是个字符串，要用`"$var"`防止字符串中有引号。

3. 特殊的变量：
   argument|refer
   :---:|:---:
   \$0|脚本名
   \$1 ~ \$9|脚本参数
   \$@|脚本所有参数
   !!|完整的上一条命令
   \$_|上一条命令的最后一个参数
   \$?|前一个命令的返回值（0表示正常，其他非零表示不正常）true 1 false 0

#### 字符串

- 字符串拼接

  ```bash
  str1=$name$url  #中间不能有空格
  str2="$name $url"  #如果被双引号包围，那么中间可以有空格
  str3=$name": "$url  #中间可以出现别的字符串
  str4="$name: $url"  #这样写也可以
  str5="${name}Script: ${url}index.html"  #这个时候需要给变量名加上大括号
  ```

#### 数组

```bash
a=(1 2 3)
for i in 1 2 3; do
for i in $a; do
for i in {1..3}; do
```

### 使用命令执行结果

当您通过 `$( CMD )` 这样的方式来执行CMD 这个命令时，然后它的输出结果会替换掉 `$( CMD )` 。例如，如果执行 for file in `$(ls)` ，shell首先将调用ls ，然后遍历得到的这些返回值。

> 和c等比较不同的是，ls或者cat等命令的输出不是返回值对于bash来说命令的返回值和命令的输出是不同的。
>
> 命令的返回值0表示正常，其他非零表示不正常。

### 正则表达式

1. 通配   ？匹配一个字符 * 匹配任意个字符
   e.t. `ls *.php` `rm foo?`

2. 花括号 `{}` 一系列命令有公共子串时，可以通过花括号展开它们。
   >e.t. cp /path/to/project/{foo,bar,baz}.sh /newpath
   会展开为
   cp /path/to/project/foo.sh /path/to/project/bar
   sh /path/to/project/baz.sh /newpath

### 条件判断

#### if

#### case

#### test

## Linux

### [apt VS apt-get](https://blog.csdn.net/liudsl/article/details/79200134)

apt 命令的引入就是为了解决命令过于分散的问题，它包括了 apt-get 命令出现以来使用最广泛的功能选项，以及 apt-cache 和 apt-config 命令中很少用到的功能。

- `apt` 可以看作 `apt-get` 和 `apt-cache` 命令的子集, 可以为包管理提供必要的命令选项。
- `apt-get` 虽然没被弃用，但作为普通用户，还是应该首先使用 apt。

### [.bashrc VS .bash_profile](https://linuxize.com/post/bashrc-vs-bash-profile/)

When invoked as an interactive login shell, Bash looks for the `/etc/profile` file, and if the [file exists](https://linuxize.com/post/bash-check-if-file-exists/) , it runs the commands listed in the file. Then Bash searches for `~/.bash_profile`, `~/.bash_login`, and `~/.profile` files, in the listed order, and executes commands from the first readable file found.

When Bash is invoked as an interactive non-login shell, it reads and executes commands from `~/.bashrc`, if that file exists, and it is readable.

> login shell, interactive shell, non-interactive shell etc. Also check the link above.

### update VS upgrade VS dist-upgrade

apt-get cmd

update: 当执行apt-get update时，update重点更新的是来自软件源的软件包的索引记录(即index files)。

upgrade：当执行apt-get upgrade时，upgrade是根据update更新的索引记录来下载并更新软件包。

dist-upgrade:当执行apt-get dist-upgrade时，除了拥有upgrade的全部功能外，dist-upgrade会比upgrade更智能地处理需要更新的软件包的依赖关系。

### ubuntu查看当前版本。

[lsb_release](https://ipcmen.com/lsb_release) -a （-a是查看全部信息）

cat /etc/os-release

uname -a 查看内核版本

### Ctrl+Alt+F1 VS terminal

### 系统设置

#### DNS

/etc/resolv.conf

`nameserver dns_server_ip`

#### proxy

/etc/environment

#### apt.conf

vi /etc/apt/apt.conf

### file permission

```
owner   -rwx------
group   ----rwx---
other   -------rwx

----------            0000               no permissions
---x--x--x            0111               execute
--w--w--w-            0222               write
--wx-wx-wx            0333               write & execute
-r--r--r--            0444               read
-r-xr-xr-x            0555               read & execute
-rw-rw-rw-            0666               read & write
-rwxrwxrwx            0777               read. write & execute
-rwxr-xr-x            0755               default permissions
```



## 一些常用命令行软件使用

### wget

```sh
wget -r -nH --cut-dirs=2 --no-parent --reject="index.html*" http://mysite.com/dir1/dir2/data
```

download a directory recursively, which rejects index.html* files and downloads without the hostname, parent directory and the whole directory structure。

### dig

```bash
dig example.com +noall +answer
```

+noall不要任何数据段，+answer添加answer section

返回结果各项的意义：[ref-link](https://linuxize.com/post/how-to-use-dig-command-to-query-dns-in-linux/)

answer section: name, expiration time, class, type, data

type includes A (the IP address), CNAME (canonical name), TXT (text record), MX (mail exchanger), and NS (name servers) 可以直接查询这些记录using `dig example.com a/cname/etc`



## 问题处理方案

1. apt-get install时碰到unmet的package，就把那些报错的package一个个apt-get。

2. [Ubuntu输入密码后无法进入桌面，但是可以ctrl+alt+f1进入命令行界面](https://blog.csdn.net/e01528/article/details/79532932)

3. [dpkg 被中断、sudo apt-get upgrade失败](https://blog.csdn.net/weixin_44649870/article/details/89636997)

4. 升级Ubuntu
   1. [Ubuntu全盘备份与恢复，亲自总结，实测可靠](https://blog.csdn.net/sinat_27554409/article/details/78227496)
   2. [如何安全的从ubuntu16.04升级到18.04？](https://blog.csdn.net/a850565178/article/details/107517874)
   
5. [Ubuntu挂载硬盘](https://zhuanlan.zhihu.com/p/35774442)

6. [ssh断开后会停止ssh中运行的进程](https://www.cnblogs.com/lomper/p/7053694.html)。
   - 因此当网络断开或终端窗口关闭后, 也就是SSH断开以后, 控制进程收到 SIGHUP 信号退出, 会导致该会话期内其他进程退出。
   - 简而言之: 就是 ssh 打开以后, bash等都是他的子程序, 一旦ssh关闭, 系统将所有相关进程杀掉!! 导致一旦ssh关闭, 执行中的任务就取消了。
   
7. [No such file or directory? But the file exists!](https://askubuntu.com/questions/133389/no-such-file-or-directory-but-the-file-exists)

   有可能在64位机器上执行32位指令且没有安装相关依赖。

   `file file-name` 检查是否为

   `ELF 32-bit LSB  executable, Intel 80386 ...`

   ```bash
   sudo dpkg --add-architecture i386
   sudo apt-get update
   sudo apt-get install libc6:i386 libncurses5:i386 libstdc++6:i386
   ./file-name
   ```

## 我在学长的机器上做的一些操作log

1. 2021.10.23 

   reason: 安装docker时解决

   ```
   The aufs storage-driver is no longer supported.
   Please ensure that none of your containers are
   using the aufs storage driver, remove the directory
   /var/lib/docker/aufs and try again.
   ```

   因此`sudo rm -rf /var/lib/docker/aufs` 但进行了备份：将`/var/lib/docker`进行了一个备份`/var/lib/docker.bk`

