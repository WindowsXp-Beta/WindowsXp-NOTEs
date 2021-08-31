# Java Note

## Java Concept

### Java abbr.

> I hate abbr.
>
> Hey!But you just said an abbreviation!!
>
> Well,you know...too difficult to spell such a long word...

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
        ┌───────┐┌───────┐┌───────┐┌───────┐
        │Windows││ Linux ││ macOS ││others │
        └───────┘└───────┘└───────┘└───────┘
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

## Syntax

### 变量类型

final 仅可赋值一次，仅可在constructor中赋值。

### 控制

#### 循环

#### Pipeline

Stream

### 函数

#### lambda expression

> 1. 减少代码量
> 2. 实现@functional interface

`(argument-list) -> {body} `

当body只有一条语句时，不写return也是可以的。多条语句时，则必须要写return。

### interface VS abstract class

abstract class类中的方法不必是抽象的；abstract class类中定义抽象方法必须在具体子类中实现。

interface可以说成是抽象类的一种特例，由interface修饰。接口中的所有方法都必须是抽象的；接口中的方法定义默认为public abstract类型；接口中的成员变量类型默认为public static final。









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







