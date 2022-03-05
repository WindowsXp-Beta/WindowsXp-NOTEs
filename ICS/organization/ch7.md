# Linking

> 在三个阶段可以做
>
> 1. Compile time By compiler
> 2. Load time By loader
> 3. Run time By program

## 静态链接

### ELF

> Executable and Linkable Format (ELF)

<img src="./note_img/ELF_format.jpeg" style="zoom:40%;" />

#### Header

<img src="./note_img/ELF_header.jpeg" style="zoom:35%;" />

Notice that

- e_shoff    section header table offset
- e_phoff   program header table offset

More details

<img src="./note_img/ELF_header_detail.png" style="zoom:40%;" />

#### Section Header Table

一个section header的数组。

每个object file中的section有且仅有一个section header描述它。

<img src="./note_img/ELF_header_table.jpeg" style="zoom:35%;" />

More details

<img src="./note_img/ELF_header_table_detail.jpeg" style="zoom:35%;" />

<img src="./note_img/ELF_header_table_detail_2.png" style="zoom:40%;" />

- sh_addr    往内存中copy时内存中的地址
- sh_offset    在file中的偏移

#### Section

More details see on textbook P467

##### String Table

将ELF文件中的所有string首尾相接放在一起，包括symtab，debug section中的符号表，header section table,program header table中每一个section的名字等。

原来需要使用string的地方改为存放StringTable中的index，这样可以很好解决string变长的问题，字符串也可以共享节省空间。

##### Symbol Table

###### includes

1. 定义的全局变量

   - Nonstatic functions
   - Nonstatic variable

2. 引用的全局变量

   定义在其他文件中的变量。

3. local symbol

   static functions and variables

###### 构造过程

Compiler找出所有symbol（符号解析）并导出到.s文件中，Assembler使用这些symbol制作symbol table。

symbol Table包含一个Symbol数组。

###### Symbol结构

<img src="./note_img/symbol_table.png" style="zoom:50%;" />

Explanation

- size	symbol的大小，比如函数的大小、全局数组的大小等。

- section    section header Table的索引，表明这个object属于哪个section。

  还有三个伪节，section header Table中是没有的。

  ABS 不该被重定位的符号。

  UNDEF 未定义的符号。

  COMMON 还未分配位置的未初始化的数据。

  > <img src="./note_img/common_vs_bss.png" style="zoom:50%;" />

- value    对于可重定位目标文件，表示object在其对应section中的位置（offset）。对于可执行文件，表示object的运行时地址。

e.g.

<img src="./note_img/symbol_table_eg.png" style="zoom:50%;" />

<img src="./note_img/symbol_table_eg_2.jpeg" style="zoom:35%;" />

注意，对于COMMON，因为其在ELF文件中没有空间，所以Value实际上会被浪费掉，所以用Value的位置来放**alignment**对齐。

### 符号解析

> 由编译器compiler完成

强全局符号：函数和已初始化的全局变量。

弱全局符号：未初始化的全局变量。

#### 多重定义符号

1. 不允许有多个同名的强全局符号。
2. 一个强全局符号与多个弱符号同名，选取强符号。
3. 多个弱符号同名，任意选取一个。

### 静态库

静态库以一种存档（archive）的特殊文件格式（`.a`）存放在磁盘中，存档（archive）是一组连接起来的可重定位目标文件的集合。

在链接时，链接器将只复制**被程序引用**的目标模块。

### Relocate

效果：

> 跳转指令最常用的是PC-relative编码，即将 **目标指令的地址** 与 **紧跟在跳转指令后面的指令** 地址之间的差作为编码。即 （%rip + 编码）才是真实要跳转的地址。%rip是紧跟在跳转指令后面的指令，因为早年CPU会先更新PC的值。

e.g.

<img src="./note_img/relocate_eg.jpeg" style="zoom:50%;" />

#### Relocate procedure

See on textbook P479-P481

分两步：

第一步：合并相同类型的节。（包括data、text、符号表等）这一步完成时，每条指令和全局变量都有唯一运行时内存地址了。将其填到符号表里。

第二步：对所有重定位条目重定位。

**重定位的结果就是把一些0x000000替换成真实的东西**

##### 基本流程概括

做第一步，确定所有地址 =》遍历所有重定位条目 =》对于每条，先利用symbol =》去符号表中找到真实地址 =》再利用offset找到其在ELF中的位置 =》用真实地址替换原来的0x000000

> 即使对于bss和COM（其实合并完符号表就没有COM了），虽然没有bss段，但符号表里还有这个符号，也就有其地址。

#### Relocate entry structure

> 汇编器碰到每个位置未知的目标引用时就会生成一个重定位条目

两种entry

- rel.data

  <img src="./note_img/reloc_data_eg.png" style="zoom:50%;" />

- text.data

  <img src="./note_img/reloc_code_eg.png" style="zoom:50%;" />



<img src="./note_img/relocate_entry.png" style="zoom:50%;" />

- offset    在.text或者.data section中的偏移

  > Symbol Table中的symbol也有offset（value），这两者有何区别？
  >
  > Symbol中的offset是符号在其所属section中的偏移。符号有什么？函数（在text中），变量（在data中）。且重定位第一步做完后该值就被替换成真实地址了。
  >
  > relo的offset是引用在所属section中的偏移，对于变量（在data中），与symbol的offset相同。对于代码中的引用，分布在汇编码中。

- symbol    在symbolTable中的index

- type

  R_X86_64_PC32    32位PC相对寻址

  R_X86_64_32    32位绝对寻址

  ......	

- addend    将`ADDR(r.symbol)+r.addend`填入重定位的地址。

e.g.

<img src="./note_img/relocate_str_eg.jpeg" style="zoom:50%;" />

上面这条指令对应的C代码为`bufp1 = &buf[1];`，其中bufp1为global，buf为extern。

可以看出，对于bufp1采用了PC32相对寻址，-8则是因为下一条指令（即%rip）位于r.offset+8处。buf采用了32位绝对寻址，+4则是因为所需的地址为`buf[1]`。

### Overall procedure

编译器（Compiler）将每个.c文件生成汇编代码，同时进行符号解析。

汇编器（assembler）将汇编代码变成机器码（包含一些0x000000），同时构造符号表与重定位条目表，生成ELF文件即`.o`文件。

链接器（linker）将各个.o文件的section进行合并，合并完成后进行重定位。

## executable object file

<img src="./note_img/exe_ELF.png" style="zoom:40%;" />

ELF header

<img src="./note_img/ELF_exe_header.png" style="zoom:40%;" />

Segment Header Table(program header Table)

<img src="./note_img/Segment_Header_Table.png" style="zoom:40%;" />

主要描述了可执行文件连续的片被映射到连续的内存段，这种映射关系。

## 动态链接

> Load时链接
>
> Run时链接

相比静态链接的优势：

1. 对库函数的修改需要每一个app重新链接。
2. 可执行文件中的重复代码。（比如很多文件里都有printf）
3. 内存中的重复代码。（直接由上一条导致，这些可执行文件加载到内存中后就会导致这个问题）

