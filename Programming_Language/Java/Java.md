# Java Note

## Java Concept

### Java abbr.

> I hate abbr.
>
> Hey! But you just said an abbreviation!!
>
> Well, you know, it's so difficult to spell such a long word...

JDK: java development kit

JRE: java runtime environment

```ascii
  ┌─    ┌──────────────────────────────────┐
  │     │     Compiler, debugger, etc.     │
  │     └──────────────────────────────────┘
 JDK ┌─ ┌──────────────────────────────────┐
  │  │  │                                  │
  │ JRE │      JVM + Runtime Library       │
  │  │  │                                  │
  └─ └─ └──────────────────────────────────┘
        ┌───────┐┌───────┐┌───────┐ ┌──────┐
        │Windows││ Linux ││ macOS │ │others│
        └───────┘└───────┘└───────┘ └──────┘
```

JVM: Java Virtual Machine

Java SE: standard edition 标准版，包含标准的JVM和标准库。

> Java SE是一个标准，由JCP决定哪些东西要加到（或移除）到JDK中。每个人都可以实现这个标准，只要通过Tck(Test Compatibility Kit)就可以认为是一个可行的JDK。

Java EE: 是企业版，它只是在Java SE的基础上加上了大量的API和库，以便方便开发Web应用、数据库、消息服务等，Java EE的应用使用的虚拟机和Java SE完全相同。

### Different JDK

[Which Java SDK Should You Use?](https://developer.okta.com/blog/2019/01/16/which-java-sdk)

[Differences between Oracle JDK and OpenJDK](https://www.baeldung.com/oracle-jdk-vs-openjdk)

> OpenJDK is an official reference implementation of a Java Standard Edition since version SE 7.
>
> But, since Java 10, the open-source reference implementation of the Java SE platform is the responsibility of the [JDK Project](https://openjdk.java.net/projects/jdk/).
>
> Oracle JDK is free for development and testing, but you have to pay for it if you use it in production
>
> Oracle OpenJDK is free for any environment

- Azul Zulu is an OpenJDK build that’s passed the TCK and is fully compliant with the Java SE standard.
- Red Hat
- AdoptOpenJDK
- Amazon Corretto
- ...

#### switch between different jdk

> [ref](https://cloud.tencent.com/developer/article/1782923)
>
> jdk往往存在的地方：
>
> 1. `/Users/weixinpeng/Library/Java/JavaVirtualMachines`
> 2. `/Library/Java/JavaVirtualMachines`

use jenv

- jenv add path_to_jdk_home
- jenv remove jdk_name
- use specific jdk version —— `jenv local jdk_name`

### version history

[Java Versions and Features](https://www.marcobehler.com/guides/a-guide-to-java-versions-and-features)

|  Year  |         version          |
| :----: | :----------------------: |
|  2004  |        1.5 / 5.0         |
|  2005  |        1.6 / 6.0         |
|  2011  |        1.7 / 7.0         |
|  2014  | 1.8 / 8.0 Java SE8(LTS)  |
| 2017/9 |        1.9 / 9.0         |
| 2018/3 |            10            |
| 2018/9 | 11 Java SE 11 (18.9 LTS) |
| 2019/3 |            12            |
| 2019/9 |            13            |
| 2020/3 |            14            |
| 2020/9 |            15            |
| 2021/3 |            16            |

命令行运行

1. 一个Java源码只能定义一个`public`类型的class，并且class名称和文件名要完全一致；
2. 使用`javac`可以将`.java`源码编译成`.class`字节码；
3. 使用`java`可以运行一个已编译的Java程序，参数是类名。

### java & javax & sun & org

**java.\***
   java SE的标准库，是java标准的一部分，是对外承诺的java开发接口，通常要保持向后兼容，一般不会轻易修改。包括其他厂家的在内，所有jdk的实现，在java.*上都是一样的。

**javax.\***
   也是java标准的一部分，但是没有包含在标准库中，一般属于标准库的扩展。通常属于某个特定领域，不是一般性的api。
    所以以扩展的方式提供api，以避免jdk的标准库过大。当然某些早期的javax，后来被并入到标准库中，所以也应该属于新版本JDK的标准库。比如jmx，java 5以前是以扩展方式提供，但是jdk5以后就做为标准库的一部分了，所有javax.management也是jdk5的标准库的一部分。

**com.sun.\***
   是sun的hotspot虚拟机中java.*  和javax.*的实现类。因为包含在rt中，所以我们也可以调用。但是因为不是sun对外公开承诺的接口，所以根据实现的需要随时增减，因此在不同版本的hotspot中可能是不同的，而且在其他的jdk实现中是没有的，调用这些类，可能不会向后兼容，所以一般不推荐使用。*

**org.omg.\***
是由企业或者组织提供的java类库，大部分不是sun公司提供的，同com.sun.*，不具备向后兼容性，会根据需要随时增减。其中比较常用的是w3c提供的对XML、网页、服务器的类和接口。

### jar vs war

- **.jar files:** The .jar files **contain libraries, resources and accessories files** like property files.
- **.war files:** The war file **contains the web application** that can be deployed on any servlet/jsp container. The .war file **contains jsp, html, javascript** and other files necessary for the development of web applications.

## Syntax

### 变量

final: 仅可赋值一次，仅可在constructor中赋值。

const: java中没有const，可以用static final达到类似的效果。

### 控制

#### 循环

##### for

1. 与C++类似

2. for-each

    ```java
    int[] numbers = {1, 2, 3, 4, 5};
    for (int number : numbers) {
        System.out.println(number);
    }
    ```

#### Pipeline

Stream

### 函数

#### lambda expression

> 1. 减少代码量
> 2. 实现@functional interface

`(argument-list) -> {body} `

当body只有一条语句时，不写return也是可以的。多条语句时，则必须要写return。

##### exception

all `@FunctionalInterface`s used in lambdas do not allow exceptions to be thrown。比如Consumer和Runnable都没有throw，所以如果是拿lambda初始化这些interface（比如Optional.ifPresent and Optional.ifPresentOrElse），不能throw exception。

有一些lambda one-line exception handling的库可以看看[JARiS](https://github.com/oliviercailloux/JARiS), [durian](https://github.com/diffplug/durian) and [this stackOverflow](https://stackoverflow.com/a/30246026/16598178).

## OOP

如果一个class, method, field, etc. 没显示声明scope，那它就是package-private。

### interface VS abstract class

abstract class类中的方法不必是抽象的；abstract class类中定义抽象方法必须在具体子类中实现。

interface可以说成是抽象类的一种特例，由interface修饰。接口中的所有方法都必须是抽象的；接口中的方法定义默认为public abstract类型；接口中的成员变量类型默认为public static final。

## JDK insight

### pass by value VS pass by reference

In Java, we can only pass parameters *by value*.

Java object variables are simply references that point to real objects in the memory heap.

### java memory layout

[Can Java allocate a list on stack?](https://stackoverflow.com/questions/23273569/can-java-allocate-a-list-on-stack)

1. All objects, including their individual attributes, are stored on the heap.

    > in special cases, the java virtual machine may perform escape analysis and decide to allocate objects (including your `LinkedList`) on a stack, but this normally doesn't happen and isn't a major concern.

2. the value on the stack is the pointer pointing to the value in heap

    ![](/Users/weixinpeng/git-repos/NOTE_github/Java/Java.assets/diff_ between_object _and _reference.jpg)

#### Comparing with rust

```java
var a = new Student();
var b = a; // b will copy the value of A
```

```rust
let a = Student();
let b = a; // a would no longer have the access to Student
```

## Java philosophy

### 面向对象原则

SOLID

#### SRP

> Single responsibility principle 

单一职责原则

A class should have only one reason to change.

使用组合，解耦

#### LSP

> Liskov substitution principle 

subclass != subtype

子类要能当成父类使用。

#### DIP

> Dependence inversion principle 

#### ISP

> The interface Segregation principle 

#### OCP

> Open-closed principle 

对增加open，对修改close

可以增加功能，不能修改已有的功能。

方法 => 面向接口编程。定义好interface，然后可以有多个实现。







