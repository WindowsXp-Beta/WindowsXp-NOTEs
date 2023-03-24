# Software Test

> Ref:
>
> [How to write good tests](https://github.com/mockito/mockito/wiki/How-to-write-good-tests)

## Unit Test

### Java

#### springboot test

> with Assert and Mockito

对于springboot应用这种多层架构来说，对于每一层的单元测试是假设它依赖的层是完全正确的情况下（比如Controller会调用一些service），那么就假设service都是对的。这就需要Mockito（不是周董的歌）这个库来模拟这些@MockBean，@Mock的行为。（一般来说，比如测试Controller，那么就需要mock service层的行为，service则要模拟reposiroty的行为）

[Mockito Doc](https://javadoc.io/doc/org.mockito/mockito-core/latest/org/mockito/Mockito.html)

Mockito主要提供了两个功能：打桩 stubbing 和 检测 verify

> Mockito focus on interactions between objects

打桩用来模拟函数的行为，比如规定throw的exception，返回值等等。

verify用来检测一个函数是否被调用过。

使用方法可以参考上面的Doc和下面的例子

[se128-spring-backend-test](https://github.com/sjtu-se128/spring-backend-test/tree/main/testdemo/src/test/java/com/example/testdemo)

Assert则用来检测函数的返回值是否符合预期。
