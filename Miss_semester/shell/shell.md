[toc]
## shell
> some proper words
> dash - 

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
### some basic command
1. `ls`
   - `ls -l`
   ![](ls_l.png)
   - `ls *.c (*.cpp)`
2.  `mv`  `cp`  the_previous_path -> the_path_you_want
3.  change stream input and stream output 
    `>`:change stream output
    `<`:change stream input
    ```shell
    $ echo hello > hello.txt
    $ cat < hello.txt > hello2.txt 
    //equivalent to cp command
    ```
    `>>` means append,`>`will overwrite
4.  The `|` 使得 output of one is the input of another.
    `ls -l / | tail -n1`
    将ls -l的内容输入到tail中，而tail输出尾部10行
    常与`xargs`搭配使用
5.  control+l can clear the terinmal(actually not clear just go to the top of it)
6.  `;` 在同一行执行多个命令

#### some normal commands:
`pwd` print working directory
`cd` change directory
`echo` write argument to the standard output 
`which` 在$PATH中，查找系统命令的位置（一些shell built in command是查不到的
> shell执行命令的基本途径，先找是否是shell built in command 再去PATH中找是否有这条命令

`mkdir -p` -p 确保目录名称存在，不存在的就建一个。
> mkdir -p wxp/test 在工作目录下的wxp目录中建立一个test目录，若不加-p，则若wxp不存在，便会报错。

`find` find path -option 
>将当前目录及其子目录下所有文件后缀为 .c 的文件列出来:
\# find . -name "*.c"

`locate` 定位指定文件

## shell script
#### bash
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