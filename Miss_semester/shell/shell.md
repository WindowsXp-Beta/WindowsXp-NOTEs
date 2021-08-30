# SHELL & LINUX

## shell

> dash means `-`

`command flag 参数`参数只有一个单词，如果想要输入词组，需使用"",flag是命令的一些选项，starts with dash -

### 一些特殊的文件夹
`.` current direcotry 
`..` parent directory
`cd ~` back to your home directory
`cd -` to the previous directory you are in 
### getting help
**on linux** `command-name --help`
**both on linux and Mac OS** `man conmand-name`
**[TLDR pages](https://tldr.sh)** Simplified and community-driven man pages usage:直接在终端中输入 `tldr + cmd`
### basic Info
1. 输入输出重定向

   change stream input and stream output 
   `>`:change stream output
   `<`:change stream input

   ```shell
   $ echo hello > hello.txt
   $ cat < hello.txt > hello2.txt 
   //equivalent to cp command
   ```
   `>>` means append	`>`will overwrite

   <img src="https://img-blog.csdnimg.cn/20190514150119510.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdWN5MDA3,size_16,color_FFFFFF,t_70" style="zoom:80%;" />

   <img src="https://img-blog.csdnimg.cn/20190514150920867.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdWN5MDA3,size_16,color_FFFFFF,t_70" style="zoom:80%;" />

2. The `|` 使得 output of one is the input of another.
   `ls -l / | tail -n1`
   将ls -l的内容输入到tail中，而tail输出尾部10行
   常与`xargs`搭配使用

3. control+l can clear the terinmal(actually not clear just go to the top of it)

4. `;` 在同一行执行多个命令

#### commands
- `ls`

  - `ls -l`
    <img src="note_img/ls_l.png" style="zoom:80%;" />
  - `ls *.c (*.cpp)`

- `mv`move  `cp`copy  the_previous_path -> the_path_you_want

- `echo` write argument to the standard output 

- `which` 在$PATH中，查找系统命令的位置（shell built in command是查不到的）

  > shell执行命令的基本途径，先找是否是shell built in command 再去PATH中找是否有这条命令

- `mkdir -p` -p 确保目录名称存在，不存在的就建一个。

  > mkdir -p wxp/test 在工作目录下的wxp目录中建立一个test目录，若不加-p，则若wxp不存在，便会报错。

- `find` find path -option 

  > 将当前目录及其子目录下所有文件后缀为 .c 的文件列出来:
  > \# find . -name "*.c"

- `locate` 定位指定文件

- `crontab`   ref: [Linux Crontab 定时任务](https://www.runoob.com/w3cnote/linux-crontab-tasks.html)    [Linux crontab 命令](https://www.runoob.com/linux/linux-comm-crontab.html)

  别忘了输出重定向，crontab默认会将输出信息发送至mail文件夹中，比如`/var/mail` 或者 `/var/spool/mail`。

  <img src="https://www.linuxprobe.com/wp-content/uploads/2017/01/how-cron-task02.jpg" style="zoom:67%;" />

  */3  每过3分钟/小时/...

- `du` disk usage用于查看目录或文件大小。ref: [du](https://www.runoob.com/linux/linux-comm-du.html)

- [查看进程](https://www.linuxprobe.com/linux-look-process.html)

## shell script
### bash

变量
1. `''`定义的字符串为原意字符串 `""`定义的字符串会进行转义
> Be careful about the SPACE
2. 使用已定义过的变量 `$var`
3. 特殊的变量：
   argument|refer
   :---:|:---:
   \$0|脚本名
   \$1 ~ \$9|脚本参数
   \$@|脚本所有参数
   !!|完整的上一条命令
   \$_|上一条命令的最后一个参数
   \$?|前一个命令的返回值（0表示正常，其他非零表示不正常）true 1 false 0
4. 当您通过 `$( CMD )` 这样的方式来执行CMD 这个命令时，然后它的输出结果会替换掉 `$( CMD )` 。例如，如果执行 for file in `$(ls)` ，shell首先将调用ls ，然后遍历得到的这些返回值。
5. 还有一个冷门的类似特性是 进程替换（process substitution）， `<( CMD )` 会执行 `CMD` 并将结果输出到一个临时文件中，并将 `<( CMD )` 替换成临时文件名。这在我们希望返回值通过文件而不是STDIN传递时很有用。例如， `diff <(ls foo) <(ls bar)`: 会显示文件夹 foo 和 bar 中文件的区别
6. 通配   ？匹配一个字符 * 匹配任意个字符
   e.t. `ls *.php` `rm foo?`
7. 花括号 `{}` 一系列命令有公共子串时，可以通过花括号展开它们。
   >e.t. cp /path/to/project/{foo,bar,baz}.sh /newpath
   会展开为
   cp /path/to/project/foo.sh /path/to/project/bar
   sh /path/to/project/baz.sh /newpath

## Linux

- [apt VS apt-get](https://blog.csdn.net/liudsl/article/details/79200134)

  apt 命令的引入就是为了解决命令过于分散的问题，它包括了 apt-get 命令出现以来使用最广泛的功能选项，以及 apt-cache 和 apt-config 命令中很少用到的功能。

  - `apt` 可以看作 `apt-get` 和 `apt-cache` 命令的子集, 可以为包管理提供必要的命令选项。
  - `apt-get` 虽然没被弃用，但作为普通用户，还是应该首先使用 apt。

- [.bashrc VS .bash_profile](https://linuxize.com/post/bashrc-vs-bash-profile/)

  When invoked as an interactive login shell, Bash looks for the `/etc/profile` file, and if the [file exists](https://linuxize.com/post/bash-check-if-file-exists/) , it runs the commands listed in the file. Then Bash searches for `~/.bash_profile`, `~/.bash_login`, and `~/.profile` files, in the listed order, and executes commands from the first readable file found.

  When Bash is invoked as an interactive non-login shell, it reads and executes commands from `~/.bashrc`, if that file exists, and it is readable.

  > login shell, interactive shell, non-interactive shell etc. Also check the link above.

