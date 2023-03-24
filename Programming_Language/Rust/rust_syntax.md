# rust syntax

### 基本类型

- 数值类型: 有符号整数 (`i8`, `i16`, `i32`, `i64`, `isize`)（以补码存储）、 无符号整数 (`u8`, `u16`, `u32`, `u64`, `usize`) 、浮点数 (`f32`, `f64`)、以及有理数、复数
- 字符串：字符串字面量和字符串切片 `&str`
- 布尔类型： `true`和`false`
- 字符类型: 表示单个Unicode字符，存储为4个字节
- 单元类型: 即 `()` ，其唯一的值也是 `()`

> rust是静态类型语言，意味着编译器必须在编译期知道所有的变量类型。不用任何时候显示声明类型因为它可以动态推导，但有时候无法动态推导，这时候就要显示指定。

#### 整型

isize和usize视CPU类型决定 if 32位：则这两个32位。64则64

溢出见：

#### 浮点数

f32 和 f64，分别为 32 位和 64 位大小。默认浮点类型是 f64，在现代的 CPU 中它的速度与 f32 几乎相同，但精度更高。

- 避免在浮点数上测试相等性
- 当结果在数学上可能存在未定义时，需要格外的小心

那如果非要进行比较呢？可以考虑用这种方式 (0.1_f64 + 0.2 - 0.3).abs() < 0.00001 ，具体小于多少，取决于你对精度的需求。

对于数学上未定义的结果，例如对负数取平方根 -42.1.sqrt() ，会产生一个特殊的结果：Rust 的浮点数类型使用 NaN (not a number)来处理这些情况。

#### 序列

```rust
1..5	//生成1~4的序列
1..=5	//生成1~5的序列
```

序列只允许用于数字或字符类型，原因是：它们可以连续，同时编译器在编译期可以检查该序列是否为空，字符和数字值是 Rust 中仅有的可以用于判断是否为空的类型。

- 类型转换必须是显式的. Rust 永远也不会偷偷把你的 16bit 整数转换成 32bit 整数
- Rust 的数值上可以使用方法. 例如你可以用以下方法来将 13.14 取整： 13.14_f32.round()，在这里我们使用了类型后缀，因为编译器需要知道 13.14 的具体类型

#### 字符

Rust 的字符不仅仅是 `ASCII`，所有的 `Unicode` 值都可以作为 Rust 字符，每个字符占据4个字节，包括单个的中文、日文、韩文、emoji表情符号等等，都是合法的字符类型。

`is_numeric` `is_alphabetic`

通过`''`构造

#### byte

|  Symbol  |                         Explanation                          |
| :------: | :----------------------------------------------------------: |
| `b"..."` | Byte string literal; constructs a `[u8]` instead of a string |
| `b'...'` |                      ASCII byte literal                      |
| `"..."`  |                        String literal                        |
| `r"..."` |   Raw string literal, **escape characters** not processed    |

```rust
let a = b"abc";
assert_eq!(&[97, 98, 99], a);
let b = b'a'; // b is 97
assert_eq!(97, b);
```

因为是u8，使用非ascii字符会报错。

#### ()

单元类型就是 () 

main 函数就返回这个单元类型 ()，你不能说 main 函数无返回值，因为没有返回值的函数在 Rust 中是有单独的定义的：发散函数，顾名思义，无法收敛的函数。

例如常见的 println!() 的返回值也是单元类型 ()

可以用 () 作为 map 的值，表示我们不关注具体的值，只关注 key

### 内存布局

[ref](https://github.com/rustlang-cn/Rustt/blob/main/Articles/%5B2022-05-04%5D%20%E5%8F%AF%E8%A7%86%E5%8C%96%20Rust%20%E5%90%84%E6%95%B0%E6%8D%AE%E7%B1%BB%E5%9E%8B%E7%9A%84%E5%86%85%E5%AD%98%E5%B8%83%E5%B1%80.md)

- 整形 都在栈上

- 元组：类似c中的struct，有对齐要求

    ```rust
    use std::mem::{size_of, align_of};
    
    size_of::<(char, u8, i32)>(); // 12 字节
    
    align_of::<(char, u8, i32)>(); // 4 字节
    ```

- 数组

    数组的大小是固定的，而且它的大小是数据类型的一部分。数组中的每个元素都会在**栈上**相邻排放。

- Vec

    在堆上分配。栈上占据3个usize（堆上的地址，长度和容量）

    > 下图中的a是arr

    

    <img src="https://camo.githubusercontent.com/d5db9721631fdd4d07a7fee190bb71870e7dc89f0d43432b42e721c89fd56b4e/68747470733a2f2f67697465652e636f6d2f72757374636e2f72757374742d6173736574732f7261772f6d61696e2f32303232303530342d56697375616c697a696e672d6d656d6f72792d6c61796f75742d6f662d527573742d646174612d74797065732f3230323230353034313434333932392e706e673f7261773d74727565" style="zoom:30%;" />

    ```rust
    let v: Vec<String> = vec![
        "Odin".to_String(),
        "Thor".to_String(),
        "Loki".to_String(),
    ]
    ```

    ![image-20220818185740541](/Users/weixinpeng/git-repos/NOTE_github/Rust/rust_syntax.assets/vec_2.png)

- 切片

    切片就像是底层数组的一个视图。由于切片没有指定元素数量，编译时 Rust 编译器不知道它具体占了多少字节。同时，你也不能将切片存在变量中，因为它没有已知大小，所以不能被分配在栈上，这样的类型被称为 **DST 动态大小类型** 。

    **几乎在任何情况下，我们只会使用到切片的引用 `&[T]`**

    <img src="https://camo.githubusercontent.com/e6dabd6bb5eec16e7f9009187544082650c214c149a4f274184dada884996107/68747470733a2f2f67697465652e636f6d2f72757374636e2f72757374742d6173736574732f7261772f6d61696e2f32303232303530342d56697375616c697a696e672d6d656d6f72792d6c61796f75742d6f662d527573742d646174612d74797065732f3230323230353034323134393831382e706e673f7261773d74727565" style="zoom:30%;" />

- 字符串

    - String `String::from("hello")` 与vec类似

        <img src="https://camo.githubusercontent.com/0ff4e86bd67bd242f9ccfc528a28986a32fa26a6937755db19fe291190c45300/68747470733a2f2f67697465652e636f6d2f72757374636e2f72757374742d6173736574732f7261772f6d61696e2f32303232303530342d56697375616c697a696e672d6d656d6f72792d6c61796f75742d6f662d527573742d646174612d74797065732f3230323230353034313434343833372e706e673f7261773d74727565" style="zoom:30%;" />

    - &str

        ```rust
        let s2: &str = "hello";
        ```

        hello保存在.text段，具有static生命周期。

        两种引用切片：

        <img src="https://camo.githubusercontent.com/7f0fcf49b9ef63a4885dac06ba44f99bdf9e14f18962b5beadf423adac18b9c8/68747470733a2f2f67697465652e636f6d2f72757374636e2f72757374742d6173736574732f7261772f6d61696e2f32303232303530342d56697375616c697a696e672d6d656d6f72792d6c61796f75742d6f662d527573742d646174612d74797065732f3230323230353034313434353734352e706e673f7261773d74727565" style="zoom:30%;" />

- 结构体

    1.  普通结构体

        ```rust
        struct Data {
            nums: Vec<usize>,
            dimension: (usize, usize),
        }
        ```

        ![image-20220818183505478](/Users/weixinpeng/git-repos/NOTE_github/Rust/rust_syntax.assets/normal_struct.png)

    2. 单元结构体

    3. 元组结构体

- Box

    Box 是一个指针指向堆上的数据，所以 Box 在栈上只需要 1 个 `usize` 去存储地址。

- Rc

    ![image-20220818190425057](/Users/weixinpeng/git-repos/NOTE_github/Rust/rust_syntax.assets/rc.png)

    Arc is nearly same as Rc except that its ref cnt is updated atomicity.

### 高级类型

#### String与切片

> 字符串字面量被硬编码到程序代码中

String则被分配在堆上，因此可以动态伸缩。

字符串切片是对String类型中某一部分的引用。切片保存起始指针和长度

字符串切片的标识是&str

```rust
let word = &s[0..5];	//0~4 左闭右开区间
let slice = &s[4..];
let len = s.len();
let slice = &s[4..len];	//4~最后一个字符
```

其他切片

```rust
let a = [1, 2, 3];
let slice = &a[0..1];
```

数组切片的类型是`&[i32]`

slice可以使用`to_vec`转化成vec

**字符串字面量就是切片**

**字符串与字符**不同，字符串是UTF-8编码（每个字符占据1~4个字节的空间）。

```
fn push_str(&mut self, string: &str)
```

What is Slice？

> Slice行为如下图所示

```rust
struct &[i32] {
    first_element: *const i32,
    length: usize,
}
```

有一个指向首地址的指针和length。

##### 索引

String无法索引，因为UTF-8编码不定长，无法做到O(1)，每次索引都要O(n)

那如何操作UTF-8数组呢？

以Unicode的方式遍历：

```rust
for c in "中国人".chars() {
    println!("{}", c);
}
```

And the output is

```
中
国
人
```

```rust
for b in "中国人".bytes() {
    println!("{}", b);
}
```

And the output is

```
228
184
173
229
155
189
228
186
186
```

> 获取子串is hard，比如获取`holla中国人नमस्ते`的子串标准库是做不到的。

#### 数组

动态数组：Vec，存储在堆上。

静态数组：array，存储在栈上。

##### Array

- 长度固定
- 元素必须有相同的类型
- 依次线性排列

```rust
let a = [1, 2, 3];
let a: [i32; 3] = [1, 2, 3];
let a = [3; 5];	//<=>[3, 3, 3, 3, 3]
let first = a[0];
let error = a[5];	//index >= 5 will make Rust panic
```

##### Vec

```rust
pub const fn new() -> Vec<T, Global>
pub fn with_capacity(capacity: usize) -> Vec<T, Global>
let v = vec![1, 2, 3];	//可以在初始化时赋初值
get()	//返回Option<T>
[]	//越界时会直接退出
```

#### 元组

```rust
let tup: (i32, f64, u8) = (500, 6.4, 1);	//创建
let (x, y, x) = tup;	//解构赋值
let var_1 = tup.0;	//索引从0开始
```

#### 结构体

```rust
struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}
let user = User {
  	email: String::from("someone@example.com"),
    username: String::from("someusername123"),
    active: true,
    sign_in_count: 1,
};
```

1. 初始化实例时，**每个字段**都需要进行初始化。

   > 当函数参数和结构体字段同名时，可以直接使用缩略的方式进行初始化。
   >
   > ```rust
   > User {
   >       email, // shorthand for email: email
   >       username,
   >      ...
   > }
   > ```

2. 初始化时的字段顺序**不需要**和结构体定义时的顺序一致。

3. 必须要将结构体实例声明为可变才能修改其中字段，不支持将某个结构体字段标记为可变。

##### 内存中的组织

![](https://pic3.zhimg.com/80/v2-8cc4ed8cd06d60f974d06ca2199b8df5_1440w.png)

##### 元组结构体

```rust
struct Color(i32, i32, i32);
```

##### 解构赋值

```rust
let Cte {alias, query, ..} = cte_table;
// 不使用的field也可以再前面加下划线或者如果有多个多个unused fields就直接dot dot
foo(
    BoundSelect {
        from,
        where_clause,
        mut select_items,
        group_by,
        mut having,
        distinct,
        ..
    }: BoundSelect,) {}
// 函数传参的时候也可以
```



#### 枚举

枚举可以同一化类型。

**任何类型的数据都可以放入枚举成员中**: 例如字符串、数值、结构体甚至另一个枚举。

##### Option

```rust
enum Option<T> {
    Some(T),	//表示含有值
    None,	//表示没有值
}
```

> 因为 `Option`，`Some`，`None` 都包含在 `prelude` 中，因此你可以直接通过名称来使用它们，而无需以 `Option::Some` 这种形式去使用

#### 集合

##### HashMap

```rust
use std::collections::HashMap;
HashMap::new();
insert();
```

#### 迭代器

迭代器跟 `for` 循环：是否通过索引来访问集合。

> In rust: `for` 循环是迭代器的语法糖

- 惰性初始化：创建迭代器不会有任何额外的性能损耗，其中的元素也不会被消耗，只有使用到该迭代器的时候，一切才开始。
- **迭代器之所以成为迭代器，就是因为实现了 `Iterator` 特征**，要实现该特征，最主要的就是实现其中的 `next` 方法，该方法控制如何从集合中取值，最终返回值的类型是关联类型`Item`。

数组转为迭代器：

- `into_iter` 会夺走所有权
- `iter` 是借用
- `iter_mut` 是可变借用

> 对于数组：into_iter()和iter()返回的都是Iter\<T\>
>
> 对于Vec：into_iter()返回的是IntoIter\<T\>它的next是Option\<T\>，iter()返回的是Iter\<T\>，它的next是Option\<&T\>

iter1.zip(iter2)它的作用就是将两个迭代器的内容压缩到一起，形成 `Iterator<Item=(ValueFromA, ValueFromB)>` 这样的新的迭代器。如果两个迭代器不等长，那么会在其中一个end后停止。

zip_eq则如果不等长就panic

### 类型转换

#### as转换

```rust
let a = 3.1 as i8;
let b = 100_i8 as i32;
let c = 'a' as u8; // 将字符'a'转换为整数，97
```

#### TryInto

```rust
let a: u8 = 10;
let b: u16 = 1500;
let b_: u8 = b.try_into().unwrap(); // 会返回一个Result从而可以做错误处理
```

> 最主要的是 `try_into` 转换会捕获大类型向小类型转换时导致的溢出错误：

### 变量与赋值（绑定）

```rust
let a = 10;	//编译器会根据a的值为a推断类型：i32
let b: i32 = 20;	//也可以主动指定类型
let d = 30_i32;	//也可以在数值中带上类型，下划线让可读性更好
//以上为不可变变量，重新赋值会导致编译报错
let mut x = 5;	//定义一个可变对象
```

字符串使用双引号，单引号是单个字符类型(char)

```rust
const CONST_VAR: u32 = 100_000;
//常量自始至终不可变，不能标注为mut，且必须声明类型
//可以在任意作用域内声明
```

```rust
let x = 5;
let x = x + 1;	//对之前的x进行遮蔽
{
  let x = x * 2;	//在这个作用域内遮蔽x，此时x为12
}
//此时x又变为6
```

Q：我们何时要遮蔽变量？

A：在某个作用域内我们无需使用之前的变量，变量遮蔽可以使我们不用浪费脑细胞想变量名。

### 引用和借用

常规引用是一个指针类型，指向了对象存储的内存地址。

&取引用，*解引用，但是这样定义的引用是不能修改的。

```rust
let x = 5;	//x = 5
let y = &x;	//*y = 5
```

#### 可变引用

```rust
let mut s = String::from("hello");
some_function(&mut s);
```

- **同一作用域，特定数据只能有一个可变引用，但可以有多个不可变引用**

- **可变引用和不可变引用不能同时存在**

#### 引用的作用域

注意，引用的作用域 `s` 从创建开始，一直持续到它最后一次使用的地方。

> 这个跟变量的作用域有所不同，变量的作用域从创建持续到某一个花括号 `}`

#### 讨论

1. `foo: &mut T` VS `mut foo: T`

    前者意味着foo引用了一个可以修改的T类型的变量，后者则是声明了一个T类型的可变变量

2. clone reference

    [ref from reddit](https://www.reddit.com/r/rust/comments/d3wo9i/cloning_a_reference/)

    ```rust
    #[derive(Clone)]
    struct Test{
    	test : String
    }
    fn main() {
        let a : Test = Test{test : "Hallo".to_string()};
        let b : &Test = &a;
        let c = b.clone();
    }
    ```

    1. It will first try `<Test as Clone>` which gives the type `c: Test`.
    2. But if that doesn't work, it will try `<&Test as Clone>`. That *always* works and is the same as `let c: &Test = b;`

    But if we use `let c: Test = c.clone()` compiler will give you en error if it cannot clone `Test`.

### 表达式与语句

```rust
fn add_with_extra(x: i32, y: i32) -> i32 {
    let x = x + 1; // 语句
    let y = y + 5; // 语句
    x + y // 表达式
}
```

完成了一个具体的操作，但是并没有返回值，因此是语句。

表达式会进行求值，然后返回一个值。

> 调用一个函数是表达式，因为会返回一个值，调用宏也是表达式，用花括号包裹最终返回一个值的语句块也是表达式，总之，能返回值，它就是表达式。

```rust
let y = {
  let x = 3;
  x + 1	//return 4, so y is 4
};
```

#### 条件

```rust
if n < 0 {
    print!("{} is negative", n);
} else if n > 0 {
    print!("{} is positive", n);
} else {
    print!("{} is zero", n);
}
```

必须用{}把语句包起来

#### 循环

| 使用方法                      | 等价使用方式                                      | 所有权     |
| ----------------------------- | ------------------------------------------------- | ---------- |
| `for item in collection`      | `for item in IntoIterator::into_iter(collection)` | 转移所有权 |
| `for item in &collection`     | `for item in collection.iter()`                   | 不可变借用 |
| `for item in &mut collection` | `for item in collection.iter_mut()`               | 可变借用   |

- break 可以单独使用，也可以带一个返回值，有些类似 return

  > break counter * 2;

- loop 是一个表达式，因此可以返回一个值

**while vs for**

for 并不会使用索引去访问数组，因此更安全也更简洁，同时避免运行时的边界检查，性能更高。

#### 匹配

- match 的匹配必须要穷举出所有可能，因此这里用 _ 来代表未列出的所有可能性
- match 的每一个分支都必须是一个表达式，且所有分支的表达式最终返回值的类型必须相同
- X | Y，是逻辑运算符 或，代表该分支可以匹配 X 也可以匹配 Y，只要满足一个即可

```rust
match target {
    模式1 => 表达式1,
    模式2 => {
        语句1;
        语句2;
        表达式2
    },
    _ => 表达式3	//means default in cpp
}
```

```rust
if let Some(3) = v {
    println!("three");
}
```

当你只要匹配一个条件，且忽略其他条件时就用 if let ，否则都用 match。

##### 匹配枚举

```rust
match enum_var {
  &Some(v) => {},
  // Or
  Some(v) => {},
}
```

[ref from stack overflow](https://stackoverflow.com/questions/55625001/why-does-pattern-matching-on-optiont-yield-something-of-type-somet/55625204)

假设enum_var是一个枚举的引用

- before rust1.26，编译器会报错：the compiler should throw an error similar to "expected Option, found reference"
- Current versions of Rust support "match ergonomics"，这时Some(v)匹配一个引用值会将v取出，且v是一个引用类型。
- 如果用&Some(v)，那么v就将把enum_var中的值取出，如果这个值没有实现copy trait就会报错。

### 函数

```rust
// 定义一个函数，输入两个i32类型的32位有符号整数，返回它们的和
fn add(i: i32, j: i32) -> i32 {
  // 返回相加值，这里可以省略return
  i + j
}
```

<img src="https://pic2.zhimg.com/80/v2-54b3a6d435d2482243edc4be9ab98153_1440w.png" style="zoom:90%;" />

- 函数的位置可以随便放，Rust 不关心我们在哪里定义了函数，只要有定义即可
- 每个函数参数都需要标注类型
- 可以通过return提前返回

#### 特殊返回类型

1. `()`

   1. 函数没有返回值，那么返回一个 `()`
   2. 通过 `;` 结尾的表达式返回一个 `()`

2. `!`：当一个函数的返回值是这个是，该函数永不返回

   ```rust
   fn dead_end() -> ! {
     panic!("你已经到了穷途末路，崩溃吧！");
   }
   ```

### 方法

```rust
impl class_name {
  fn method_name(&self) -> return_type {	//&self means self: &Self
    /* your expression */
  }
}
```

- `self` 表示 `Rectangle` 的所有权转移到该方法中，这种形式用的较少
- `&self` 表示该方法对 `Rectangle` 的不可变借用
- `&mut self` 表示可变借用

> 根据self的参数格式rust可以知道对于一个对象是如何访问该方法，从而自动添加引用，可变引用之类的。

#### 关联函数

定义在 `impl` 中且没有 `self` 的函数。

比如构造器：`new()`

使用双冒号调用：`Point::new()`

### 泛型

```rust
// struct
struct Point<T> {x: T, y: T}
// function
fn add<T: std::ops::Add<Output = T>>(a:T, b:T) -> T {
    a + b
}
// enum
enum Result<T, E> {Ok(T), Err(E)}
enum Option<T> {Some(T), None}
// method
impl<T> Point<T> {	//这里的Point<T>是一个完整的结构体类型
    fn x(&self) -> &T {
        &self.x
    }
}
```

### 特征

特征定义了**一个可以被共享的行为，只要实现了特征，你就能使用该行为**。

```rust
pub trait Summary {
    fn summarize(&self) -> String {
    	/* 默认实现，可以不写 */
  	}
}
pub struct Post {
    pub title: String, // 标题
    pub author: String, // 作者
    pub content: String, // 内容
}
impl Summary for Post {
    fn summarize(&self) -> String {
        format!("文章{}, 作者是{}", self.title, self.author)
    }
}
```

**如果你想要为类型 `A` 实现特征 `T`，那么 `A` 或者 `T` 至少有一个是在当前作用域中定义的**

> 比如你在当前作用域中就没法为`String`类型实现`Display`特征。

#### 特征约束

```rust
pub fn notify(item: &impl Summary) {	//item是一个实现了Summary特征的类型
    println!("Breaking news! {}", item.summarize());
}
pub fn notify(item: &(impl Summary + Display)) {}	//实现多个特征
// 定义特征的时候也可以加约束
pub trait Test: Display {}
// 这样一个struct要impl Test它必须也要impl Display
```

等价于

```rust
pub fn notify<T: Summary>(item: &T) {
    println!("Breaking news! {}", item.summarize());
}
//过多特征时可以通过where美化
pub fn notify<T, U>(t: &T, u: &U) -> i32
	where T: Display + Summary,
				U: Clone + Copy {

}
```

##### 有条件的实现方法或特征

```rust
impl<T: Display + PartialOrd> Pair<T> {
    fn cmp_display(&self) {
        if self.x >= self.y {
            println!("The largest member is x = {}", self.x);
        } else {
            println!("The largest member is y = {}", self.y);
        }
    }
}
```

`cmp_display` 方法，并不是所有的 `Pair<T>` 结构体对象都可以拥有，只有 `T` 同时实现了 `Display + PartialOrd` 的 `Pair<T>` 才可以拥有此方法。

#### 关联类型

关联类型是在特征定义的语句块中，申明一个自定义类型，这样就可以在特征的方法签名中使用该类型：

```rust
pub trait Iterator {
    type Item;
    fn next(&mut self) -> Option<Self::Item>;
}
```

实现特征的时候就为type指定具体的类型

```rust
impl Iterator for Counter {
    type Item = u32;
    fn next(&mut self) -> Option<Self::Item> {
        // --snip--
    }
}
```

> Q：为什么不用泛型？
>
> A：为了代码的可读性。
>
> 为了代码的可读性，当你使用了泛型后，你需要在所有地方都写 `Iterator<Item>`，而使用了关联类型，你只需要写 `Iterator`，当类型定义复杂时，这种写法可以极大的增加可读性。
>
> 如果使用泛型，你将得到以下的代码：
>
> ```rust
> trait Container<A,B> {
>     fn contains(&self,a: A,b: B) -> bool;
> }
> fn difference<A,B,C>(container: &C) -> i32
>   where
>     C : Container<A,B> {...}
> ```
>
> 可以看到，由于使用了泛型，导致函数头部也必须增加泛型的声明，而使用关联类型，将得到可读性好得多的代码：
>
> ```rust
> trait Container{
>     type A;
>     type B;
>     fn contains(&self, a: &Self::A, b: &Self::B) -> bool;
> }
> fn difference<C: Container>(container: &C) {}
> ```

#### 特征对象

实现了某一特征的的类型的实例。

类型声明要使用`dyn`关键字。

```rust
pub struct Screen {
    pub components: Vec<Box<dyn Draw>>,	//Vec中的所有对象都实现了Draw方法
}
```

> Why not use genericity?
>
> Because otherwise it can only contain one type of objects.(When the T is confirmed)

泛型是静态分发，是在编译器完成的，对运行性能完全无影响。

特征对象是动态分发，直到运行时才知道调用什么代码。

**Rust 需要在编译时知道类型占用多少空间，如果一种类型在编译时无法知道具体的大小，那么被称为动态大小类型 DST。特征也是 DST 类型，而特征对象在做的就是将 DST 类型转换为固定大小类型。**

#### 对象安全

只有对象安全的特征才能拥有特征对象。

当一个特征的所有方法都有如下属性时，它的对象才是安全的：

- 方法的返回类型不能是 `Self`
- 方法没有任何泛型参数

### 智能指针

> 堆栈性能：
>
> - 小型数据，在栈上的分配性能和读取性能都要比堆上高
> - 中型数据，栈上分配性能高，但是读取性能和堆上并无区别，因为无法利用寄存器或 CPU 高速缓存，最终还是要经过一次内存寻址
> - 大型数据，只建议在堆上分配和使用

#### Box

1. 显示的把变量存储到堆上。

   ```rust
   let arr = Box::new([0;1000])
   ```

##### Box::leak

你需要一个在运行期初始化的值，但是可以全局有效，也就是和整个程序活得一样久，那么就可以使用 `Box::leak`

#### Deref

智能指针是一个结构体，没有办法直接执行\*操作，所以需要实现Deref特征，返回自己包含的东西的引用。（这里有点绕，因为解引用返回的东西还是个引用），然后这个引用就可以使用\*操作了

在函数和方法中，Rust 提供了一个极其有用的隐式转换：`Deref `转换。简单来说，当一个实现了 `Deref` 特征的值被传给函数或方法时，会根据函数参数的要求，来决定使用该值原本的类型还是 `Deref` 后的类型。

#### Drop

order:

- **变量级别，按照逆序的方式**，`_x` 在 `_foo` 之前创建，因此 `_x` 在 `_foo` 之后被 `drop`
- **结构体内部，按照顺序的方式**，结构体 `_x` 中的字段按照定义中的顺序依次 `drop`

我们无法为一个类型同时实现 `Copy` 和 `Drop` 特征。因为实现了 `Copy` 的特征会被编译器隐式的复制，因此非常难以预测析构函数执行的时间和频率。因此这些实现了 `Copy` 的类型无法拥有析构函数。

#### Rc

```rust
let a = Rc::new(String::from("hello, world"));
let b = Rc::clone(&a);
```

`Rc/Arc` 是不可变引用，你无法修改它指向的值，只能进行读取。

Arc在`std::sync::Arc`中

Rc在`std::rc::Rc`中

### 错误处理

```rust
enum Result<T, E> {
    Ok(T),
    Err(E),
}
```

> Result同样是prelude的

使用match进行匹配

```rust
let f = File::open("hello.txt");

let f = match f {
  Ok(file) => file,
  Err(error) => match error.kind() {
    ErrorKind::NotFound => match File::create("hello.txt") {
      Ok(fc) => fc,
      Err(e) => panic!("Problem creating the file: {:?}", e)
    },
    other_error => panic!("Problem opening the file: {:?}", other_error),
  },
};
```

#### unwrap & expect

如果返回成功，就将 `Ok(T)` 中的值取出来，如果失败，就直接 `panic`。

```rust
let f = File::open("hello.txt").expect("Failed to open hello.txt");
```

expect可以带上错误提示。

#### 错误传播

```rust
fn read_username_from_file() -> Result<String, io::Error> {
    let mut f = File::open("hello.txt")?;
    let mut s = String::new();
    f.read_to_string(&mut s)?;
    Ok(s)
}
File::open("hello.txt")?.read_to_string(&mut s)?;
```

##### ?

1. 如果结果是 `Ok(T)`，则把 `T` 赋值给 `f`，如果结果是 `Err(E)`，则返回该错误。
2. 它还可以自动进行类型转换：一个错误类型通过 `?` 返回后，（可以）变成了另一个错误类型。
3. 还可以链式调用，遇到错误就返回，没遇到错误就将Ok中的值取出来用于下一个方法调用。
4. 它也可以用于Option的返回，Result用？返回Err，Option就用？返回None。

**attention**

```rust
fn first(arr: &[i32]) -> Option<&i32> {
   arr.get(0)?
}
```

`?` 操作符需要一个变量来承载正确的值，它会把Ok或者Some中的值取出来，因此上面这个函数会编译错误，因为返回类型不一致，如果错误，返回None，如果正确，返回&i32。

因此？只能用于以下形式：

- `let v = xxx()?;`
- `xxx()?.yyy()?;`

### 类型别名

type TypeName = 一个裹了好几层的类

### 宏

#### 选择器

- item：条目，例如函数、结构、模块等
- block：代码块
- stmt：语句
- pat：模式
- expr：表达式
- ty：类型
- ident：标识符
- path：路径，例如 foo、 ::std::mem::replace, transmute::<_, int>, …
- meta：元信息条目，例如 #[…]和 #![rust macro…] 属性
- tt：词条树

### 函数式

闭包

```rust
(move) |param1, param2,...| {
    语句1;
    语句2;
    返回表达式
}
```

1. 闭包并不会作为 API 对外提供，因此它可以享受编译器的类型推导能力，无需标注参数和返回值的类型。
2. 闭包还拥有一项函数所不具备的特性：捕获作用域中的值。
3. 如果你想强制闭包取得捕获变量的所有权，可以在参数列表前添加 `move` 关键字，这种用法通常用于闭包的生命周期大于捕获变量的生命周期时，例如将闭包返回或移入其他线程。