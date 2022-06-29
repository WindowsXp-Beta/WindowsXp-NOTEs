# C plus plus

> Since I claimed that I'm proficient in cpp in my CV, I should write a cpp note.

## basic

### 进制

八进制（octal）以`0`开头

16进制（hexadecimal）以`0x` or `0X`开头

### 运算符优先级

1. `* / %`

2. `+ -`

3. `>> <<`
4. `< <= > >=`

### 初始化数组

```c++
int array[5] = {0}// 所有元素初始化为0
//类似可以
bool myBoolArray[ARRAY_SIZE] = { false };
char* myPtrArray[ARRAY_SIZE] = { nullptr };
```

对于class内的数组

```c++
class Something {
 private:
	int myArray[10];
 public:
	Something() : myArray { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 } {}
```

### 函数指针

```c
void fun(int a) {
    printf("Value of a is %d\n", a);
}
void fun2(int a) {}
void fun3(int a) {}
int main() {
    // 定义一个函数指针同样需要参数类型和返回值类型
    void (*fun_ptr)(int) = &fun;
    // 也可以直接使用函数名
	void (*fun_ptr)(int) = fun;
    /* The above line is equivalent of following two
       void (*fun_ptr)(int);
       fun_ptr = &fun;
    */
    // Invoking fun() using fun_ptr
    (*fun_ptr)(10);
   	// 定义一个函数指针数组
    void (*fun_ptr_arr[])(int) = {fun, fun2, fun3};
    (*fun_ptr_arr[i])(para);
    return 0;
}
```

### 变长参数

> variadic function

C: one fixed argument and then any number of arguments can be passed

```c
int function_name(data_type variable_name, ...);
```

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

### 类模板的友元函数

方法一：

```c++
template<class T>
class A{
  template<class U>
	friend A<U> foo(A<U> &a);
};
```

坏处：所有foo的实例是所有A的实例的友元。

比如`foo<int>`和`foo<double>`都是`A<int>`的友元。

方法二：

```c++
template<class T> class A;
template<class T> A<T> foo(A<T> &a);
template<class T>
class A {
  friend A foo<T>(A &a);
  //为什么不用在A后面加T，因为
  //C++ assumes that any reference to that class is templated, so adding the <T> is redundant.
};
template<class T>
A<T> foo(A<T> &a) {
  //implementation
}
```

这可以避免方法一的问题

> In general, this is how template friend functions are done in best practices.

## 类型转换

### string和各种type互转

1. stringstream

   ```cpp
   stringstream ss;
   ss << class_you_want_to_convert_to_string;
   ss.str();
   ```

2. to_string

   支持 int，unsigned，(unsigned) long，(unsigned) long long，float，(long) double转string。

3. [std::stoi, std::stol, std::stoll](https://en.cppreference.com/w/cpp/string/basic_string/stol)

   [std::stoul, std::stoull](https://en.cppreference.com/w/cpp/string/basic_string/stoul)

## new feature

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
[函数对象参数] (操作符重载函数参数) mutable 或 exception 声明 -> 返回值类型 {函数体
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

### typeid

对于定义了虚函数的基类，当基类指针指向它的派生类时，可以用typeid(*pointer)来检查该类的运行时类型。

```c++
class A{
public:
  virtual void show();
};
class B : public A{
  void show() override;
};
int main(){
  A* p;
  B b;
  p = &b;
  cout << (typeid(*b) == typeid(B));//don't forget the *
}
//output will be 1
```

### 智能指针

> use after free, double-free, memory leak
>
> Why C++ doesn't have GC?
>
> - C++ is built for efficiency (GC has its overhead)

#### RAII

> Resource Acquisition is Initialization

**Not a specific implementation, but a methodology.**

The life cycle of resource = its corresponding object

some example: 

- std::lock_guard

- a naive file handler class, release resource in deconstructor

```c++
class File_Struct {
public:
  File_Struct(char *file_name, char *mode) {
    file_handle = fopen(file_name, mode);
    if (!file_handle) error(...);
  }
  ~File_Struct() {
    fclose(file_handle);
  }
private:
  FILE file_handle;
};
```

So we get "smart pointers":

#### std::unique_ptr

> with little to no（几乎没有） overhead over built-in pointers :smile:

1. 自动delete管理的指针当
   1. 他们自己（unique_ptr）destroy了。
   2. 他们的值发生了变化通过1. assignment 2. unique_ptr::reset

支持部分指针操作比如：*, ->, `[]` for array

不支持指针的算术运算，只支持move assignment。

> p1 = std::move(unique_ptr p)
>
> 转移pointer的ownership

##### porperties

- constructor

  ```cpp
  explicit unique_ptr (pointer p) noexcept;//from pointer
  ```

- `pointer get()`

  get the pointer

- 可以在 if() 中判断是否为空，等价于执行 get()!=nullptr

- `pointer release()`

  release所存储的pointer，返回指针的值并将本身unique_ptr置空

- `void reset(pointer another_pointer)`

  delete当前stored的pointer，然后take ownership of another_pointer

  赋给一个新指针，应该使用reset

- assignment  `=` 

  只接受unique_ptr或者nullptr_t

  如果为空（=nullptr_t）等价于 `reset(/* nothing */)`

  不然，operator=(unique_ptr u)等价于

  ```c++
  reset(u.release());
  get_deleter() = forward<deleter_type>(u.get_deleter());
  ```

  

#### std::shared_ptr

- A shared_ptr constructor: +1

- A shared_ptr destructor: -1

- Reaching 0: remove the objects



#### std::make_unique

new一个class T，返回`std::unique_ptr<T>`。

```cpp
class Vec3{
public:
  Vec3 (int a = 0, int b = 0, int c = 0) {
    ...
  }
};
std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0,1,2);
std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);	//返回五个元素的数组
```

[Advantages of using std::make_unique over new operator](https://stackoverflow.com/questions/37514509/advantages-of-using-stdmake-unique-over-new-operator)

> currently not quite understand :cry:



## namespace

```c++
namespace name1 {
	//your code
}
//命名空间可以是不连续的，因此上面的代码可以是定义一个新的命名空间，也可以是为一个已有的命名空间增加元素

//anonymous namespace
//The “anonymous” namespace you have created will only be accessible within the file you created it in.
namespace {
  //your code
}
//调用某个名字空间下的函数
name1::code;
//下面这行将告诉编译器，之后的代码会使用指定名字空间
using namespace name1;
//也可以指定名字空间中的特定项
using name1::fun1;
```

## keyword

### noexcept

> operator

The `noexcept` operator performs a compile-time check that returns true if an expression is declared to not throw any exceptions.

### override

> specifier

Specifies that a virtual function overrides another virtual function.



## std

### std::iota

### std::shuffle

[How to shuffle a std::vector?](https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector)

```c++
#include <algorithm>
#include <random>

auto rng = std::default_random_engine {};
std::shuffle(std::begin(cards_), std::end(cards_), rng);
```

**Make sure to reuse the same instance of `rng` throughout multiple calls to [`std::shuffle`](https://en.cppreference.com/w/cpp/algorithm/random_shuffle) if you intend to generate different permutations every time!**

### std::string

```c++
size_t length() const noexcept;
size_t size() const noexcept;//两者返回同样的值
char& operator[] (size_t pos);
const char& operator[] (size_t pos) const;//当pos为length时返回跟在最后一个字符后面的null character，当超出length时undefined behaviour
char& at (size_t pos);
const char& at (size_t pos) const;//当pos>=length时抛out_of_range
void push_back (char c);
char& back();
const char& back() const;
char& front();
const char& front() const;
```

`#include <string>`

string 是c++的字符串类。

string中没有terminator，即`\0`也可以是string的一部分。但是当使用`string(char c[])`来初始化一个string时，会按照`\0`作为终结符判断`c[]`的长度，`\0`之后的部分不考虑。

这与c的string有很大不同，根据[ref](https://stackoverflow.com/questions/47288881/are-c-constant-character-strings-always-null-terminated) C中string是

> A *string* is a contiguous sequence of characters terminated by and including the first null character.

```c
char x[3] = "abc";
char y[4] = "abc";
char z[] = "abc";
```

x不是string，而只是个char数组，y和z都是string。所以c中的const string（或者叫字符串字面量）可以用`\0`来判断终止。

### std::string_view

c++17

[ref link](https://www.learncpp.com/cpp-tutorial/an-introduction-to-stdstring_view/)

每次新建一个std::string会复制一遍，这样就可以更改内容，但这样效率不高，且占空间。

string_view提供了对一个在另外地方定义的string的view，你不可以修改它，这样也不会发生复制，修改原char[]后string_view也会发生改变。

#### modify view

- 你可以改变你想看到的内容
  - remove_prefix 从左边开始去掉字符
  - remove_suffix 从右边开始去掉字符

#### Best practices

Prefer `std::string_view` over `std::string` for read-only strings, unless you already have a `std::string`.

## Struct

C++中的struct和C中的有很大不同。C++中struct和class几乎是一样的。

The *only* difference between a **struct** and **class** in C++ is the default accessibility of member variables and methods. In a **struct** they are public; in a **class** they are private. ——[struct vs class in C++](https://blogs.sw.siemens.com/embedded-software/2014/06/02/struct-vs-class-in-c/)

## algorithm

### reverse

```c++
//Reverse range
//Reverses the order of the elements in the range [first,last).
template <class BidirectionalIterator>
	void reverse (BidirectionalIterator first, BidirectionalIterator last);
```

### accumulate

```c++
template <class InputIterator, class T, class BinaryOperation>
   T accumulate (InputIterator first, InputIterator last, T init,
                 BinaryOperation binary_op);
```

- 从first加到last **[first,last)** 再加上init。

- 可以自定义BinaryOperation

  比如：减：`std::minus<int>()`，自定义函数

```c++
int myfunction (int x, int y) {return x+2*y;}
```

### sort

```c++
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

- 默认升序

- 自定义比较函数

  ```c++
  bool myfunction (int i,int j) { return (i<j); }
  ```

### binary_search

```c++
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val);
ForwardIterator lower_bound (ForwardIterator first, ForwardIterator last, const T& val, Compare comp);
ForwardIterator upper_bound (ForwardIterator first, ForwardIterator last, const T& val);
//返回lower bound\upper bound
//默认用小于比较
bool binary_search (ForwardIterator first, ForwardIterator last, const T& val);// 返回是否存在
```

## STL

### iterator

介绍stl中的两种迭代器：bidirectional iterators 和 random-access iterators。

bidirectional iterator: It is to be noted that containers like **list, map, multimap, set and multiset** support bidirectional iterators.

random-access iterators: It is to be noted that containers like **vector, deque** support random-access iterators.

std::sort only supports random-access iterators. std::list has its own sort method——std::list::sort

<img src="./note_img/iterator_hierarchy.png" style="zoom:50%;" />

### std::next

std::next(iterator, n)

返回当前迭代器的第n个后继

1. for random-access iterators, std::next use just operator, operator + or operator – for advancing. 
2. Otherwise, the function uses repeatedly the increase or decrease operator (operator ++ or operator –-)

### map

operator[key] VS at(key)

当key存在时两者效果相同，返回key对应的value的引用。

当key不存在时，[]用value的默认构造函数构造一个新的value然后返回这个引用，at则抛出一个异常。

### unordered_map

```c++
bool empty();//Test whether container is empty
int size();//Return container size
mapped_type& at ( const key_type& k );//返回的是引用，找不到throw out_of_range
iterator find ( const key_type& k );//找不到返回unordered_map::end
size_type count ( const key_type& k ) const;//计数指定的key
iterator erase ( const_iterator position );
iterator erase ( const_iterator first, const_iterator last );//根据迭代器删
size_type erase ( const key_type& k );//根据key删
pair<iterator,bool> insert ( const value_type& val );
//iterator是新插入的或key相同的，bool表示是否插入成功
//value_type是pair<const key_type,mapped_type>
//insert(pair<., .>(p1, p2)) OR insert(make_pair(p1, p2)) OR use emplace
pair<iterator,bool> emplace (Args&&... args);
```

1. 撞hash时使用开散列（hash bucket）

2. 不同的编译器gcc，clang，MSCV使用的hash function不一样。

3. map中元素的个数除桶的个数是load factor。

   > By default, unordered_map containers have a `max_load_factor` of `1.0`.

   当超过max_load_factor时会发生增加bucket的个数从而rehash。

### set

```c++
pair<iterator,bool> insert (const value_type& val);
pair<iterator,bool> insert (value_type&& val);
void insert (initializer_list<value_type> il);
size_type erase (const value_type& val);//返回被删去的元素个数
iterator  erase (const_iterator position);
iterator  erase (const_iterator first, const_iterator last);//返回被删去的最后一个元素的下一个元素
const_iterator find (const value_type& val) const;
iterator       find (const value_type& val);
```

### list

```c++
iterator erase (const_iterator position);
iterator erase (const_iterator first, const_iterator last);//返回被删除的最后一个元素的下一个元素
void push_front (const value_type& val);
void push_front (value_type&& val);
iterator begin() noexcept;
const_iterator begin() const noexcept;//返回链表头的指针
reference front();
const_reference front() const;//返回list第一个元素的引用
reference back();
const_reference back() const;//返回list最后一个元素的引用
iterator end() noexcept;
const_iterator end() const noexcept;//返回最后一个元素的下一个元素！！！的迭代器
void pop_back();//删除最后一个元素
```

### vector

```c++
std::vector<int> second(4, 100); // 4个100
std::vector<int> third(second.begin(), second.end()); // 用另一个vector初始化
std::vector<int> v(myints, myints+5);// 用数组初始化：int myints[] = {10,20,30,5,15};
void resize (size_type n);
void resize (size_type n, const value_type& val);
void push_back (const value_type& val);
void push_back (value_type&& val);
void pop_back();
iterator erase (const_iterator position);
iterator erase (const_iterator first, const_iterator last);//删除的范围是[first, last)
```

```c++
vector<vector<int>> v;
v.push_back({1, 2, 3});/*RIGHT*/
v.emplace_back({1, 2, 3});/*WRONG*/
```

### array

```c++
template <class T, size_t N> class array;
at();
front();
back();
size();
max_size();
empty();
```



### stack

```c++
bool empty() const;
size_type size() const;
reference top();
const_reference top() const;
void push (const value_type& val);
void push (value_type&& val);
template <class... Args> void emplace (Args&&... args);//用args构造一个新对象并push到栈顶
void pop();
```

### queue

```c++
//构造函数e.g.
queue<int> first;                 // empty queue
queue<int, list<int> > third; // empty queue with list as underlying container
std::queue<int> second (mydeck);       //mydeck是deque<int>(3, 100)可以用deque初始化
std::queue<int,std::list<int> > fourth (mylist); // mylist是list<int>用list初始化需设置container为list
size_type size();
bool empty();
void push();
template <class... Args> void emplace (Args&&... args);
void pop();
reference& front();
const_reference& front() const;//返回队列中的下一个元素（也是队列中最老的元素）
reference& back();
const_reference& back() const;//返回队列中最后一个元素（也是队列中最新的元素）
```

### priority_queue

需要支持random access的容器作为internal container class，vector和deque都满足要求，默认if no container class is specified for a particular priority_queue class instantiation, the standard container vector is used.

```c++
std::priority_queue<int> second (myints,myints+4);// 使用数组初始化
std::priority_queue<int, std::vector<int>, std::greater<int> >third (myints,myints+4);// 小顶堆（小顶堆是greater），默认是大顶（std::less）
priority_queue (InputIterator first, InputIterator last, const Compare& comp, const Container& ctnr);// 因为有这个构造函数，所以其他线性容器初始化也是行的
const_reference top() const;
void push (const value_type& val);
void push (value_type&& val);
void pop();
```

## cctype

```c++
int isalnum ( int c );//是否是字母数字的
int isalpha ( int c );//是否是字母的
int isdigit ( int c );//是否是数字的
int isupper ( int c );//是否是大写字母
int islower ( int c );//是否是小写字母
```

```c++
int toupper ( int c )
int tolower ( int c );//转换成大（小）字母，没有对应字母，就不改变
```

## Thread

### thread sleep

`std::this_thread::sleep_for(std::chrono::milliseconds(20))`

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
| `__func__` | func                                                         |

## Exception

### throw

throw表达式接受一个参数，并且将这个参数传递给exception handler。

```c++
try {
  // code here
}
catch (int param) { cout << "int exception"; }
catch (char param) { cout << "char exception"; }
catch (...) { cout << "default exception"; }
```

多个catch可以级联，只执行参数类型符合的。

...表示这个handler会接受任何类型的exception。

### 动态类型声明

dynamic exception specifications：在函数声明后添加一个 `throw` specifier。但是现在已经deprecated in C++。

```c++
double myfunction (char param) throw (int);
```

如果没有返回int类型的exception，函数调用`std::unexpected()`，改函数的默认行为是调用terminate。

## BUG REPORT

1. 在遍历容器时修改容器需要注意。

   1. LSM tree

      ```c++
      for (auto p = cacheList[line]->begin(); p != cacheList[line]->end(); p++) {
          delete *p;
          cacheList[Line]->erase(p);
      }
      ```

      在删除迭代器后再对迭代器+1会导致不确定的行为。

      其实erase会返回被删除迭代器下一个迭代器。

      所以正确做法如下：

      ```c++
      for(auto p = cacheList[line]->begin(); p != cacheList[line]->end();){
          delete *p;
          p = cacheList[Line]->erase(p);
      }
      ```

   2. Tiger Compiler lab7——Gc

      ```c++
      for (auto it : std::list list) {}
      for (auto it : std::deque deque) {}
      ```

      对于list，在循环体中增加list循环会继续遍历。

      但对于deque，循环体中增加的元素不会参与遍历。
