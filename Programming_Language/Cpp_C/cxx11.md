# modern C plus plus

## rvalue and move semantics

> [Move semantics and rvalue references in C++11](https://www.cprogramming.com/c++11/rvalue-references-and-move-semantics-in-c++11.html)
>
> [一文读懂C++右值引用和std::move](https://zhuanlan.zhihu.com/p/335994370)

### rvalue

An expression is an rvalue if it results in a temporary object.

左值**可以取地址、位于等号左边**；而右值**没法取地址，位于等号右边**。

> 除了string literals之外的所有literals都是右值。

e.g.

```cpp
int x;
int getVal () {
    return x;
}
string getName () {
    return "Alex";
}
```

> [ref](https://stackoverflow.com/a/9552880/16598178) 其实除了lvalue和rvalue，C++11中还有
>
> 1. xvalue: a new kind of value category for unnamed rvalue references, e.g. the return value of std::move. (As you may remember, **named rvalue references are lvalues**)
>
>     it can be placed on the left side of a expressioin
>
>     ```cpp
>     std::vector<int> v1, v2;
>     std::move(v1) = v2;
>     ```
>
> 2. glvalue: (“generalized” lvalue) is an lvalue or an xvalue.
>
> 3. prvalue: (“pure” rvalue) is an rvalue that is not an xvalue.

### rvalue reference

An rvalue reference is a reference that will bind only to a temporary object.

Before c++11, you can use const lvalue reference(`const T&`) to bind a temporary object.

> 比如vector中的push_back (const value_type& val)可以调用push_back(5)这样的右值

现在我们可以使用右值引用(`T&&`) bind mutable reference to a rvalue. 它不能指向左值。

```cpp
void printReference(string& str) { cout << "1 " << str << endl; }
void printReference(string&& str) { cout << "2 " << str << endl; }
printReference(getName()); // getName is defined in the previous code block
// Output: 2 Alex
int &&ref_a_right = 5; // ok
int a = 5;
int &&ref_a_left = a; // 编译不过，右值引用不可以指向左值
ref_a_right = 6; // 右值引用的用途：可以修改右值
```

### move

考虑一个Array类的移动构造函数

```cpp
class ArrayWrapper {
 public:
  ArrayWrapper(int n) : _p_vals(new int[n]), _size(n) {}
  ~ArrayWrapper() { delete[] _p_vals; }
  // copy constructor
  ArrayWrapper(const ArrayWrapper& other)
      : _p_vals(new int[other._size]), _size(other._size) {
    for (int i = 0; i < _size; ++i) {
      _p_vals[i] = other._p_vals[i];
    }
  }
  // move constructor
  ArrayWrapper(ArrayWrapper&& other)
      : _p_vals(other._p_vals), _size(other._size) {
    other._p_vals = NULL;
    other._size = 0;
  }
 private:
  int* _p_vals;
  int _size;
};
```

#### std::move

但是**右值引用本身是左值**，考虑这个类：

```cpp
class MetaData {
  private:
    string _name;
    int _size;
  public:
    // move constructor
    MetaData (MetaData&& other)
        : _name( other._name )
        , _size( other._size ) {}
    ...
};
```

所以`_name(other._name)`并不会调用string的move constructor，因为`type(other._name) != string&&`。

因此我们要这么调用 `_name(std::move(other._name))`

而比如一个函数是`void foo(T&& a)`, 而你通过一个右值变量去显示调用它，比如`T&& b = ...; foo(b);`是无法调用的。会报错

> 无法引用函数void foo(const T&)

还是这个原因，右值引用本身，是个左值。

> **右值引用既可以是左值也可以是右值，如果有名称则为左值，否则是右值**。
>
> **作为函数返回值的 && 是右值，直接声明出来的 && 是左值**。
>
> 可以通过能不能取地址来判断。

其实move并没有move任何东西，它只是做了个类型转换。

```cpp
int &&ref_a = 5;
ref_a = 6;
// 等同于以下代码：
int temp = 5;
int &&ref_a = std::move(temp);
ref_a = 6;
```

#### std::forward

`std::forward<T>(u)`有两个参数：T与u

1. 当T为左值引用类型时，u将被转换为T类型的左值。e.g. `forward<int &>(var)`
2. 否则u将被转换为T类型右值。

### STL

Move semantics has been added to the standard library. This means that you can now efficiently return vectors, maps, strings and whatever other standard library objects you want, taking full advantage of move semantics.

#### guideline

可移动对象在*需要拷贝且被拷贝者之后不再被需要*的场景，建议使用`std::move`触发移动语义，提升性能。

```cpp
std::string str1 = "aacasxs";
std::vector<std::string> vec;

vec.push_back(str1); // 传统方法，copy
vec.push_back(std::move(str1)); // 调用移动语义的push_back方法，避免拷贝，str1会失去原有值，变成空字符串
vec.emplace_back(std::move(str1)); // emplace_back效果相同，str1会失去原有值
vec.emplace_back("axcsddcas"); // 当然可以直接接右值
```

#### Q&A

Q: 使用一个moved的container会发生什么？

A: [ref](https://stackoverflow.com/a/7930386/16598178). move会让一个container进入一个valid but unspecified state。

> Since the state is valid, this means you can safely operate on `v2` (e.g. by assigning to it, which would put it back to a known state). Since it is unspecified however, it means you cannot for instance rely on any particular value for `v2.empty()` as long as it is in this state (but calling it won't crash the program).

经实验，一个string被move之后就空了。

Q: c++中return vector会导致拷贝吗？

A: [ref](https://stackoverflow.com/a/15704602/16598178). With C++11, `std::vector` has move-semantics, which means the **local vector declared in your function will be moved on return** and in some cases even the **move can be elided** by the compiler.

##### return optimiaztion

copy elision

- named return value optimization:

    ```cpp
    Thing f() {
      Thing t;
      return t;
    }
    int main() {
    	Thing t2 = f();
    }
    ```

- return value optimization

    when a temporary is returned:

    ```cpp
    Thing f() {
      return Thing();
    }
    Thing t2 = f();
    ```

Q: How to use custom class in `std::map::emplace()`? *OR* Why is `m: map<char, pair<int, int>>.emplace('w', 1, 2)` or `m: map<char, pair<int, int>>.emplace('w', {1, 2})` wrong? *OR* Will constructing the class then passing it to emplace increase the overhead? e.g. extra copy?

A: [ref](https://stackoverflow.com/questions/68645539/how-to-use-emplace-in-map-for-custom-class). 先上结论，这么用：

```cpp
class MyData {
    int age;
    string name;
};
map<MyData, vector<string>> myMap{};
myMap.emplace(MyData{32, "SJ"s}, std::vector{"working"s});
myMap.emplace<MyData>({32, "SJ"s}, std::vector{"working"s});
```

首先调用MyData的构造函数，然后调用**拷贝构造**。

因此你需要给MyData实现一个move constructor，然后emplace就会调用move constructor。

所以你也不用担心STL的overhead，since they all have a move constructor.

第二个问题，为啥不能直接传，或者uniform initialization。因为

> braced-init-list like `{32, "SJ"s}` doesn't have type, which causes template argument deduction failing when calling `emplace`.
>
> [details](https://stackoverflow.com/a/68645571/16598178)

## auto

> [ref](https://blog.csdn.net/xiaoquantouer/article/details/51647865)

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
auto ptr = [](double x) { return x*x; };//类型为std::function<double(double)>函数对象
```

## smart pointer

> [ref: C++智能指针的正确使用方式](https://cloud.tencent.com/developer/article/1517336)

> use after free, double-free, memory leak
>
> Why C++ doesn't have GC?
>
> - C++ is built for efficiency (GC has its overhead)

RAII = Resource Acquisition is Initialization

> meaning: the lifetime of the object is bound to the scope of a variable, so when the variable goes out of scope then the destructor will release the resource.

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

### std::unique_ptr

> with little to no（几乎没有） overhead over built-in pointers :smile:

1. 自动delete管理的指针当
    1. 他们自己（unique_ptr）destroy了。
    2. 他们的值发生了变化通过1. assignment 2. unique_ptr::reset

支持部分指针操作比如：*, ->, `[]` for array

只有移动构造函数，因此只能移动(转移内部对象所有权，或者叫浅拷贝)，不能拷贝(深拷贝)。

```cpp
std::unique_ptr<A> ptr_a = std::make_unique<A>();
std::unique_ptr<A> ptr_b = std::move(ptr_a); // unique_ptr只有'移动赋值重载函数'，参数是&& ，只能接右值，因此必须用std::move转换类型
std::unique_ptr<A> ptr_b = ptr_a; // 编译不通过
```

- constructor

    ```cpp
    explicit unique_ptr (pointer p) noexcept;//from pointer
    ```

- `pointer get()`

    get the pointer

- 可以在 if() 中判断是否为空，等价于执行 `get()!=nullptr`

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


### std::shared_ptr

- A shared_ptr constructor: +1

- A shared_ptr destructor: -1

- Reaching 0: remove the objects

### std::make_unique

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

## uniform initialization

```c++
// uninitialized built-in type
int i; => int i{};

// initialized built-in type
int j = 10; => int j{10};

// initialized built-in type
int k(10); => int k{10};

// Aggregate initialization
int a[] = {1, 2, 3, 4}; => int a[]{1, 2, 3, 4};

// STL container
std::vector v1{1, 2};

// return objects
return {foo, bar};

// function parameter
f({foo, bar});

// default constructor
X x1; => X x1{};

// Parameterized constructor
X x2(1); => X x2{1};

// copy-constructor
X x4=x3; => X x4{x3};
```

### Q&A

Q: Doesn't `a = {something}` also result in an extra copy/move?

A: No, that's where "traditional" copy-init and copy-list-init differ: `foo f0 = 42;` converts `42` to a prvalue temporary `foo` and direct-initializes `f0` with that temporary (via a possibly elided copy/move), whereas `foo f1 = {42};` **selects a constructor of `f1` to be called with `42`** (the copy + move may be deleted in this case).

### initialization compare

```cpp
double d = 1.7789856453427678;
int a{d}; //Compile time error - value of d will not fit in a
int a(d); //ok - a is 1
int a = d; //ok - a is 1
```

`{}`初始化函数中不能做类型转换。即使是unsigned long到int都不行。

## structured binding

```c++
auto [a, b, c, ...] = expression;
auto [a, b, c, ...] { expression };
auto [a, b, c, ...] ( expression );
```

modifers:

```c++
auto& [a, b, c, ...] = expression;
const auto [a, b, c, ...] = expression;
```

不仅可以解析pair，tuple，array，还可以解析class（public member），struct。

## functional

### std::function

class function<R(Args...)>;

```cpp
void print_num(int i) {
    std::cout << i << '\n';
}
std::function<void(int)> f_display = print_num;
```

Q: Why do we need it?

A: `std::function` is a type erasure object. That means it erases the details of how some operations happen, and provides a uniform run time interface to them. `std::function` can contain almost any object that acts like a function pointer in how you call it.

### lambda expression

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

## cocurrent

### std::condition_variable

`wait(lock, function<bool(...)> stop_waiting)`

> Atomically unlocks `lock`, blocks the current executing thread, and adds it to the list of threads waiting on *this.
>
> 原子防止在unlock和block间另一线程调用wakeup。

等价于

```cpp
while (!stop_waiting()) cv.wait(lock);
```

cv.notify_one() / notify_all()
