# Memory Hierarchy

> Author: Wei xinpeng
>
> Date: 2021.4.19

<img src="./note_img/memery_hierarchy.png" style="zoom:60%;" />

## RAM

> random access memory 随机访问存储器

SRAM（static）静态比动态快，但价格昂贵。不需要刷新，对噪声干扰不敏感。但晶体管更多，功耗大。

DRAM（dynamic）主要用作主存。需要刷新，会在10~100ms内失去电荷。

<img src="./note_img/DRAM_SRAM.png" style="zoom:50%;" />

## cache

> 两种解释
>
> 1. 位于k层的更快更小的存储设备作为位于更大更慢的存储设备的缓存。
> 2. cache memory L1 L2 L3高速缓存

### 访问数据

#### Miss

1. Cold miss: 第k层缓存是空的。
2. Conflict miss: 多个k+1层的块映射到了k层的一个块上。
3. Capacity miss: 工作集的大小超过了缓存的大小。

### cache memory

<img src="./note_img/cache_physical.png" style="zoom:40%;" />

cache memory的物理表示，由$S=2^s$个**集合**组成，每个集合里有E**行**，每行由一个标志位，标志这行是否有数据，t个tag位和存储了$B=2^b$个字节（一个**块block**）的存储区域组成。

<img src="./note_img/cache_memory.png" style="zoom:50%;" />

<img src="./note_img/cache_parameter.png" style="zoom:50%;" />

对于一个物理内存地址（比如32位64位）：将其分为三部分：tag、set index、block offset

tag的位数由后两个决定，set index表示该数据在cache memory的哪一个集合（一共有$2^s$个集合，所以可以用s个二进制位来标识每一个集合），block offset表示在block中从哪一个byte开始读（每个block有$2^b$个字节，所以可以用b个二进制位来表示每一个字节）（至于读几位，就由指令来决定，movq、movl...）。剩下的位构成tag，用来标识这一个地址。因为有可能不同的内存中的数据（不同地址）映射到同一行。

#### 用直接映射高速缓存演示一次数据访问

> Direct-mapped cache 每个集合只有一行

1. 选择集合，通过读取set index位找到那个集合（行），检查valid位。
2. 比较tag：比较tag和集合（行）的tag位。
3. 找到起始位置：读取block set找到访问起始位置。

#### 迁移block

当没有在cache中找到时（miss），就要去下一级的存储中找，并迁移一整个block到这一级的cache中（充分利用locality）

<img src="./note_img/transport_block.jpeg" style="zoom:40%;" />

比如找上图第一个地址时没有找到，那么就将其block offset位全部置0，然后去内存（main memeory，这里还是考虑direct-mapped）中找到这个地址，然后将数据迁移到cache memory中的对应**行**的block的第一个字节，重复若干次（一般高速缓存的block大小为64bytes，也就是要重复64次），直到将这行的block填满。

> 这里解释一下为什么要置0：假设不置0，那么就不能充分利用locality，你只能取小于64个bytes的数据，你也许会问，从这个miss的数据开始，还取64个bytes不行吗？确实不行，因为这样会导致set index的变化，你要存到其它集合去了，这显然是不行的。
>
> 「将cache和main memory的映射想象成一个hash。」——CSAPP

### Associative Cache

即每个set可以有多个line。

首先按照set位找set，再比较每一行的valid bit，若设置为1，再去比较该行的tag位。

> 名词解释：4-way associative 每个set有4路

### write

#### write hits

> 即待写入的块已经被加载到了cache中

1. write through

   cache更新，并且直接将这块cache block写到memory中。

2. write back

   延迟memory的写入，直到该块被evict才进行写入。

   需要维护一个dirty bit表示该块是否被写过。

#### write misses

> 即待写入的块还没被加载到cache中

1. write-allocate

   先加载到cache中再写。

2. 直接写到内存里。

**现代处理器往往采用`write back`与`write allocate`的组合。**

## Cache friendly code

1. 对局部变量的反复利用是好的，因为他们会存储在寄存器中。
2. 步长为1的引用模式是好的，因为存储器会将内存存储为连续的块。