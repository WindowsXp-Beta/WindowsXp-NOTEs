# C plus plus

> Since I claimed that I'm proficient in cpp in my CV, I should write a cpp note.

## 面向对象

### 继承

![](./note_img/继承.png)

继承类型表示，基类中的元素在派生类中的访问类型。

>  Attention：基类的数据成员不能用派生类的构造函数列表赋值，要在构造函数函数体中赋值。

### 默认构造函数

今天`(2021.4.3)`在写qt的时候碰到的问题，我使用了`QMap<int, class>`class是我自己定义的一个类，然后我使用`QMap[key] = class(index...)`为`QMap`赋初值，`class(index...)`是类的构造函数。然后这报了一个错，它说我没有class的默认构造函数。这是为何呢？

首先` QMap[key]`返回一个`value &`，即value的引用，但此时我的value是没有定义的，所以它需要先构造一个value，相当于这样

```c++
class QMap[key];//引用 == 别名
QMap[key] = class(index...);
```

但它又没有参数，所以只能调用默认构造函数，但我没有默认构造函数，所以报错了。

**警示：以后写类尽量写一个默认构造函数，这样`class A`就不会报错**

> 构造函数加上参数的缺省值也是可以作为默认构造函数的，但这个缺省值需要**在头文件中声明**。

### explicit

类构造函数的explicit声明表名该构造函数是显示的, 而非隐式的（用implicit来表示，类构造函数默认值）。

若没有这个声明，那么类的构造函数会在特定情况下发生转换。特定情况：当构造函数只有一个参数，或有n个参数，但n-1个参数都指定了缺省值。比如：

```c++
CxString(int size)  
{  
    _size = size;                // string的预设大小  
    _pstr = malloc(size + 1);    // 分配string的内存  
    memset(_pstr, 0, size + 1);  
}  
CxString string2 = 10;    // 这样是OK的, 为CxString预分配10字节的大小的内存  
```

在编译的时候就会有一个缺省的转换操作:将该构造函数对应数据类型的数据转换为该类对象. 也就是说 "CxString string2 = 10;" 这段代码, 编译器自动将整型10转换为CxString类对象。

### 纯虚函数和抽象类

虚函数：基类中将一个函数定义为虚函数。在派生类中可以重新定义这个函数。这样当用一个基类的指针指向派生类对象并调用这个函数时，会调用派生类的函数。指向不同的派生类对象就会调用不同的函数，这样就实现了运行时的多态性。

`virtual return_type fun_name() = 0`

虚析构函数：对于析构函数，最好是虚函数。这样delete基类指针指向的派生类对象时，就会调用派生类的析构函数，防止内存泄漏。

> 派生类在对虚函数重定义时，`virtual`关键字写不写，该函数都被认为是虚函数。最好写上。
>
> 在派生类中重定义虚函数时，它的函数原型（包括返回类型，函数名，参数类型和参数个数必须与基类中的虚函数完全一致）

当一个类中有纯虚函数时，它就是一个抽象类，不可以定义抽象类的对象，但可以让指针指向抽象类。

## C++ new feature

### auto

[Ref-link](https://blog.csdn.net/xiaoquantouer/article/details/51647865)

声明变量时根据**变量初始值的类型**自动为此变量选择类型。

```c++
auto f = 3.14;  //double
auto s("hello");  //const char*
auto z = new auto(9);  //int *
auto x1 = 5, x2 = 5.0, x3 = 'r';   //错误，必须是初始化为同一类型
```

不建议为这么简单的变量声明使用auto，而应该清晰写出其类型。

应该使用在**拥有复杂类型变量声明**时来**简化代码**。

```c++
std::vector<int>::iterator p = vec.begin();
/* 变为如下 */
auto p = vec.begin();
```

还可以保存lambda表达式类型的对象声明

```c++
auto ptr = [](double x){return x*x;};//类型为std::function<double(double)>函数对象
```

### lambda表达式

[Ref-link](https://www.cnblogs.com/jimodetiantang/p/9016826.html)

```c++
[函数对象参数] (操作符重载函数参数) mutable 或 exception 声明 -> 返回值类型 {函数体}
```

1. 函数对象参数

   - 标识一个lambda表达式的开始。
   - 传递给编译器自动生成的**函数对象类**的构造函数。
   - 只能使用那些到定义lambda表达式为止时，Lambda所在范围内可见的局部变量。

   有以下形式

   - 空。没有任何函数对象参数。
   - =。函数体内可以使用 Lambda 所在范围内所有可见的局部变量（包括 Lambda 所在类的 this），并且是值传递方式（相当于编译器自动为我们按值传递了所有局部变量）。
   - &。函数体内可以使用 Lambda 所在范围内所有可见的局部变量（包括 Lambda 所在类的 this），并且是引用传递方式（相当于是编译器自动为我们按引用传递了所有局部变量）。
   - this。函数体内可以使用 Lambda 所在类中的成员变量。
   - 将 a 按值进行传递。按值进行传递时，函数体内不能修改传递进来的 a 的拷贝，因为默认情况下函数是 const 的，要修改传递进来的拷贝，可以添加 mutable 修饰符。
   - &a。将 a 按引用进行传递。
   - a，&b。将 a 按值传递，b 按引用进行传递。
   - =，&a，&b。除 a 和 b 按引用进行传递外，其他参数都按值进行传递。
   - &，a，b。除 a 和 b 按值进行传递外，其他参数都按引用进行传递。

2. (操作符重载函数参数)表示传入函数的参数。

   可以使用值传递（int a, int b）和引用传递（int &a, int &b）。

3. mutable 或 exception 声明

   加上 mutable 修饰符后，可以修改传递进来的拷贝（注意是能修改拷贝，而不是值本身）。exception 声明用于指定函数抛出的异常，如抛出整数类型的异常，可以使用 throw(int)。

4. -> 返回值类型

   标识函数返回值的类型，当返回值为 void，或者函数体中只有一处 return 的地方（此时编译器可以自动推断出返回值类型）时，这部分可以省略。

5. {函数体}

   标识函数的实现，这部分不能省略，但可以为空。

## 标准库

### std::string

`#include <string>`

string 是c++

replace(size_t pos, size_t size, const string&)

没有terminator

## Preprocessor

> 其实这部分更像是C的内容，但先记在这吧。

[cpp reference doc —— preprocessor](https://en.cppreference.com/w/cpp/preprocessor)

### [Replacing text macros](https://en.cppreference.com/w/cpp/preprocessor/replace)

- #define identifier replacement-list

将identifier替换为replacement-list。还有一个用处就是写function-like text macro。

#### function-like macro

- #define *identifier*( *parameters* ) replacement-list(optional)

- #define identifier (parameters, ...) replacement-list

- #define identifier (...) replacement-list

  `...` is additional arguments (called *variable arguments*) can be accessed using `__VA_ARGS__` identifier

  e.g.

  ```c
  #define debug_log(flag, ...) do{ \
      if(DEBUG){ \
        if(flag) printf("[INFO]File: %s line: %d: ", __FILE__, __LINE__); \
        else printf("[ERROR]File: %s line: %d: ", __FILE__, __LINE__); \
        printf(__VA_ARGS__); \
        fflush(stdout); \
      } }while(0);
  ```

##### tips

- 为什么要写成 do {} while(0); [answer](https://hownot2code.com/2016/12/05/do-while-0-in-macros/)

- 我们应当使用macro还是inline function。

  > Macros should generally be avoided; prefer inline functions to them at all times. Any compiler worth its salt should be capable of inlining a small function as if it were a macro, and an inline function will respect namespaces and other scopes, as well as evaluating all the arguments once. [from stackoverflow](https://stackoverflow.com/questions/163365/how-do-i-make-a-c-macro-behave-like-a-function#:~:text=49-,Macros,-should%20generally%20be)

  [When are C++ macros beneficial?](https://stackoverflow.com/questions/96196/when-are-c-macros-beneficial)

  1. As wrappers for debug functions, to automatically pass things like `__FILE__`, `__LINE__`, etc

     对于debug函数，可以直接传入这些预定义宏。

  2. 函数必须完整，宏可以是代码片段。比如我们可以定义一个foreach宏。

     `#define foreach(list, index) for(index = 0; index < list.size(); index++)`

### Pre-defined C++ Macros

| `__LINE__` | This contains the current line number of the program when it is being compiled. |
| ---------- | ------------------------------------------------------------ |
| `__FILE__` | This contains the current file name of the program when it is being compiled. |
| `__DATE__` | This contains a string of the form month/day/year that is the date of the translation of the source file into object code. |
| `__TIME__` | This contains a string of the form hour:minute:second that is the time at which the program was compiled. |

