# 变量命名规范

小驼峰：smallCamelForm

大驼峰：BigCamelForm

下划线：underscore_form

## Dart

1. Classes（类名）、 enums（枚举类型）、 typedefs（类型定义）、以及 type parameters（类型参数）应该把每个单词的首字母都大写（包含第一个单词），即大驼峰命名法，不使用分隔符。
2. 在库，包，文件夹，源文件中使用 lowercase_with_underscores 方式命名。
3. 类成员、顶级定义、变量、参数以及命名参数等 *除了*第一个单词，每个单词首字母都应大写，并且不使用分隔符。
4. 使用 `lowerCamelCase` 来命名常量，包括枚举的值。

## Java

1. class name，interface name
   - 名词组成
   - 避免缩写，除非缩写更为人所熟知
   - 大驼峰命名
2. method name
   - 动词
   - 小驼峰命名
3. 变量名
   - 小驼峰
4. 常量名
   - 全大写字母，中间以下换线 `_` 分隔。

## SQL

sql文件名：单词均小写且用下划线连接。

列名：单词小写，用下划线连接。

## C++

### Compiler

class name and method name: UppelCamelCase

member and variable name: snake_case

## Qt

> from QLink

> 所有命名使⽤英⽂单词（不要使⽤拼⾳）或其缩写，以及⼀些常⽤的简写变量

- 类名：每个单词首字母大写。

- 变量和函数名：驼峰。

- 大括号位置：if、 else、 for、 while 等在同一行末尾。

  函数定义末尾在下一行。

## Javascript

变量名与函数名：驼峰法。
类名：大写驼峰式命名法，首字母大写。

私有属性和方法：前缀为下划线`_`。

全局变量为大写 (**UPPERCASE** )。

文件名：

 大多 Web 服务器 (Apache, Unix) 对大小写敏感： london.jpg 不能通过 London.jpg 访问。 

 其他 Web 服务器 (Microsoft, IIS) 对大小写不敏感： london.jpg 可以通过 London.jpg 或 london.jpg 访问。 

 你必须保持统一的风格，我们建议统一使用小写的文件名。

> 我采用的命名方式：文件名小驼峰。

对象定义的规则:

- 将左花括号与类名放在同一行。
- 冒号与属性值间有个空格。
- 字符串使用双引号，数字不需要。
- 最后一个属性-值对后面不要添加逗号。
- 将右花括号独立放在一行，并以分号作为结束符号。

## Linux kernel

https://www.kernel.org/doc/html/latest/process/coding-style.html

### indentation

行首空格用tab，且间距为8

### 大括号

- 多个statements用大括号，单个statement不用大括号

- if, switch, for, while, do all non-function blocks

  ```c
  if () {
  
  }
  ```

  function

  ```c
  int function()
  {
    
  }
  ```

### 空格

这些keywords后加一个空格 `if, switch, case, for, do, while`

大部分二元，三元运算符每一边都要空格

`=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  :`

一元运算符不用空格

`&  *  +  -  ~  !  sizeof  typeof  alignof  __attribute__  defined`

`. ->`等struct member operations也不用空格

### Naming

GLOBAL variables (to be used only if you **really** need them) need to have descriptive names, as do global functions.

LOCAL variable names should be short, and to the point. If you have some random integer loop counter, it should probably be called `i`. Calling it `loop_counter` is non-productive, if there is no chance of it being mis-understood. Similarly, `tmp` can be just about any type of variable that is used to hold a temporary value.

### comments

Instead, put the comments at the head of the function, telling people **what it does**, and possibly **WHY it does it**.

## python

function name should be lowelcase with word seperated by underscores

variable should follow the same convention

### google python style

`module_name`, `package_name`, `ClassName`, `method_name`, `ExceptionName`, `function_name`, `GLOBAL_CONSTANT_NAME`, `global_var_name`, `instance_var_name`, `function_parameter_name`, `local_var_name`

## rust

| Item                    | Convention                                                   |
| ----------------------- | ------------------------------------------------------------ |
| Crates                  | [unclear](https://github.com/rust-lang/api-guidelines/issues/29) |
| Modules                 | `snake_case`                                                 |
| Types                   | `UpperCamelCase`                                             |
| Traits                  | `UpperCamelCase`                                             |
| Enum variants           | `UpperCamelCase`                                             |
| Functions               | `snake_case`                                                 |
| Methods                 | `snake_case`                                                 |
| General constructors    | `new` or `with_more_details`                                 |
| Conversion constructors | `from_some_other_type`                                       |
| Macros                  | `snake_case!`                                                |
| Local variables         | `snake_case`                                                 |
| Statics                 | `SCREAMING_SNAKE_CASE`                                       |
| Constants               | `SCREAMING_SNAKE_CASE`                                       |
| Type parameters         | concise `UpperCamelCase`, usually single uppercase letter: `T` |
| Lifetimes               | short `lowercase`, usually a single letter: `'a`, `'de`, `'src` |
| Features                | [unclear](https://github.com/rust-lang/api-guidelines/issues/101) but see [C-FEATURE](https://rust-lang.github.io/api-guidelines/naming.html#c-feature) |

# Comment注释

## c++

函数注释

```c++
/**
 * 函数的作用
 * @param 参数名 参数的作用
 * @return 返回值的作用
 */
```

# Google C++ Style

## 头文件

### 内联

只有当函数只有 10 行甚至更少时才将其定义为内联函数。

另一个实用的经验准则: 内联那些包含循环或 switch 语句的函数常常是得不偿失 (除非在大多数情况下, 这些循环或 switch 语句从不被执行)。

大多数编译器都不支持内联递归函数。

### include路径及顺序

相关头文件, C 库, C++ 库, 其他库的 .h, 本项目内的 .h。

example：

dir/foo.cc 的主要作用是实现或测试 dir2/foo2.h 的功能, foo.cc 中包含头文件的次序如下:
1. dir2/foo2.h (优先位置, 详情如下)
2. C 系统文件
3. C++ 系统文件
4. 其他库的 .h 文件
5. 本项目内 .h 文件

> 这种优先的顺序排序保证当 dir2/foo2.h 遗漏某些必要的库时， dir/foo.cc 或 dir/foo_test.cc 的构建会立刻中止。因此这一条规则保证维护这些文件的人们首先看到构建中止的消息而不是维护其他包的人们。

## naming convention

Tip: 函数命名，变量命名，文件命名要有描述性；少用缩写。

一般：`file_name.cc` `file_name.h`  `ClassName`  `class_member_`  `struct_member `  `normal_varible`

常量命名：`kDaysInAWeek` 除去开头k之外每个单词字母大写

函数命名：一般函数大驼峰，set和get函数要与变量名匹配，比如：

```c++
int num_entries() const { return num_entries_; }
void set_num_entries(int num_entries) { num_entries_ = num_entries; }
```

> 如果您的某函数出错时就要直接 crash, 那么就在函数名加上 OrDie。

宏：`MY_MACRO_THAT_SCARES_SMALL_CHILDREN`

枚举命名优先采用常量的命名方式，但宏的方式也可以接受。

## comment

代码前注释：巧妙或复杂的代码段前要加注释。

行注释：比较隐晦的地方要在行尾加入注释. 在行尾空两格进行注释。

## format

### indent

使用两格空格。

### 函数声明

```c++
ReturnType ClassName::ReallyLongFunctionName(Type par_name1, Type par_name2,
																						 Type par_name3) {
	DoSomething();
}
// 一个参数都放不下
ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
		Type par_name1, // 4 空格缩进
		Type par_name2,
		Type par_name3) {
	DoSomething(); // 2 空格缩进
}
```

- 如果返回类型和函数名在一行放不下，分行。
- 如果返回类型那个与函数声明或定义分行了，不要缩进。
- 左圆括号总是和函数名在同一行;
- 函数名和左圆括号间没有空格;
- 圆括号与参数间没有空格;
- 左大括号总在最后一个参数同一行的末尾处;
- 如果其它风格规则允许的话，右大括号总是单独位于函数最后一行，或者与左大括号同一行。
- 右大括号和左大括号间总是有一个空格;
- 函数声明和定义中的所有形参必须有命名且一致;
- 所有形参应尽可能对齐;
- 缺省缩进为 2 个空格;
- 换行后的参数保持 4 个空格的缩进;

- 如果有些参数没有用到, 在函数定义处将参数名注释起来。

### 条件语句

```c++
if (condition) {	// 圆括号里没空格紧邻。
	...	// 2 空格缩进。
} else {	// else 与 if 的右括号同一行。
	...
}
if (x == kFoo) return new Foo();	//只有当语句简单并且没有使用 else 子句时使用
// 单行语句不需要使用大括号, 如果你喜欢用也没问题; 复杂的条件或循环语句用大括号可读性会更好
if (condition)
	DoSomething(); // 2 空格缩进。
if (condition) {
	DoSomething(); // 2 空格缩进。
}
// 如果语句中某个 if-else 分支使用了大括号的话, 其它分支也必须使用
```

```c++
switch (var) {
	case 0: { // 2 空格缩进
		... // 4 空格缩进
		break;
	}
	case 1: {
		...
		break;
	}
	default: {
		assert(false);
	}
}
```

### 循环

```c++
// 空循环体应使用 {} 或 continue, 而不是一个简单的分号
while (condition) {
	// 反复循环直到条件失效。
}
for (int i = 0; i < kSomeNumber; ++i) {} // 可 - 空循环体。
while (condition) continue; // 可 - contunue 表明没有逻辑。
```

### 指针和引用

在声明指针变量或参数时, 星号与类型或变量名紧挨都可以。

```c++
// 好样的，空格前置。
char *c;
const string &str;
// 好样的，空格后置。
char* c; // 但别忘了 "char* c, *d, *e, ...;"!
const string& str;
```

### 布尔表达式

如果一个布尔表达式超过标准行宽, 断行方式要统一一下。

我采用：逻辑表达式都放在行尾。

### 类

```c++
// 当全放在一行合适时：
MyClass::MyClass(int var) : some_var_(var), some_other_var_(var + 1) {}
// 如果要断成多行，缩进四格，冒号放在第一行初始化句：
MyClass::MyClass(int var)
		: some_var_(var), // 4 空格缩进
			some_other_var_(var + 1) { // 对准
	...
	DoSomething();
	...
}
```

