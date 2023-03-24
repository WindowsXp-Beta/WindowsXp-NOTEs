# Go

## cli

**go run**：go run 编译并直接运行程序，它会产生一个临时文件（但不会生成 .exe 文件），直接在命令行输出程序执行结果，方便用户调试。

**go build**：go build 用于测试编译包，主要检查是否会有编译错误，如果是一个可执行文件的源码（即是 main 包），就会直接生成一个可执行文件。

**go install**：go install 的作用有两步：第一步是编译导入的包文件，所有导入的包文件编译完才会编译主程序；第二步是将编译后生成的可执行文件放到 bin 目录下（`$GOPATH/bin`），编译后的包文件放到 pkg 目录下（`$GOPATH/pkg`）

[go get vs go install after go 1.16](https://zhuanlan.zhihu.com/p/338011682)

- 基本上 `go install <package>@<version>` 是用于命令的全局安装：
  - 例如：`go install sigs.k8s.io/kind@v0.9.0`;

- `go get` 安装二进制的功能，后续版本将会删除
- `go get` 主要被设计为修改 `go.mod` 追加依赖之类的，但还存在类似 `go mod tidy` 之类的命令，所以**使用频率可能不会很高**

## project structure

main包

在 Go 语言里，命名为 main 的包具有特殊的含义。 Go 语言的编译程序会试图把这种名字的包编译为二进制可执行文件。所有用 Go 语言编译的可执行程序都必须有一个名叫 main 的包。一个可执行程序有且仅有一个 main 包。

会发现名为 main()的函数，否则不会创建可执行文件。 main()函数是程序的入口，所以，如果没有这个函数，程序就没有办法开始执行。程序编译时，会使用声明 main 包的代码所在的目录的目录名作为二进制可执行文件的文件名

## package

### manipulate

go 1.11之后使用go modules来管理module，这使得go project可以不在`$GOPATH`路径中。详见[Go Modules: an Alternative to GOPATH for Package Distribution](https://insujang.github.io/2020-04-04/go-modules/)

`go mod init module_name`

`go mod tidy` install dependencies and update the go.mod

see also [Understanding go.sum and go.mod file in Go (Golang)](https://golangbyexample.com/go-mod-sum-module/)

### module

[call your code from another module](https://go.dev/doc/tutorial/call-module-code)

### main package

The Go language reserve two functions for special purpose and the functions are **main()** and **init()** function.

#### main

1. The *main()* function is a special type of function and it is the entry point of the executable programs.
2. It does not take any argument nor return anything.
3. Go automatically call *main()* function, so there is no need to call *main()* function explicitly and every executable program must contain single main package and *main()* function.

#### init

1. does not take any argument nor return anything
2. This function is present in every package and this function is called when the package is initialized.
3. This function is declared implicitly, so you cannot reference it from anywhere
4. you are allowed to create multiple **init()** function in the same program and they execute in the order they are created.

## Syntax

### types

#### type keyword

A type definition creates a new, distinct type with the same [underlying type](https://go.dev/ref/spec#Types) and operations as the given type and binds an identifier, the *type name*, to it.

A defined type may have [methods](https://go.dev/ref/spec#Method_declarations) associated with it. It does **not** inherit any methods bound to the given type.

```go
type Mutex struct         { /* Mutex fields */ }
func (m *Mutex) Lock()    { /* Lock implementation */ }
func (m *Mutex) Unlock()  { /* Unlock implementation */ }
// NewMutex has the same composition as Mutex but its method set is **empty**.
type NewMutex Mutex

// The method set of PtrMutex's underlying type *Mutex remains unchanged,
// but the method set of PtrMutex is **empty**.
type PtrMutex *Mutex
```

#### byte

alias for the uint8

#### string & rune

go string is a **read-only** slice of bytes, containers of text encoded in UTF-8()

遍历string中的rune要使用range

```go
for idx, runeValue := range s {}
```

##### format

> [ref: string-format](https://zetcode.com/golang/string-format/)
>
> - v: default format
>
> - \#v - Go-syntax representation of the value

#### conversion

```go
i := 42
f := float64(i)
u := uint(f)
```



### variable

zero values are the "default" value for defined variables in Go.

```go
var i int // 0
var t bool // false
type T struct {
    v string
}
var t T // {""}
```

### pointer

How can we get a pointer points to a Struct

```golang
new(Point)
&Point{}      // OK
&Point{2, 3}  // Combines allocation and initialization
// but built-in types are illegal
&int // x
```

from a post on medium, we can implement our own new like following

```go
func newInt() {
  var i int
  return &i
}
```

#### new vs make

`new` return a pointer to a type and `make` returns an allocated object of that type

**In the case of `make` we can only use it for `map`, `slice` and `chan`.**

`make(type(slice, map...), length, capacity)`

### function

#### variadic function

define

```go
func sum(nums ...int) {
    fmt.Print(nums, " ")
    total := 0
    for _, num := range nums {
        total += num
    }
    fmt.Println(total)
}
```

call

```go
sum(1, 2, 3)
nums := []int{1, 2, 3}
sum(nums)
```

### control flow

#### branch

##### switch



### struct

access struct fields with dot `.`

you can also use dots with struct pointers since it will be **dereferenced automatically**

#### Exported field

upperclass field means this field is exported which means it can be used outside the package, otherwise it can only be used inside the package.

#### tag

Go struct tags are annotations that appear after the type in a Go struct declaration. Each tag is composed of short strings associated with some corresponding value.

```go
type User struct {
	Name string `example:"name"`
}
```

#### method

We should use method on values or pointers?

> [go faq](https://go.dev/doc/faq#methods_on_values_or_pointers)

1. does the method need to modify the receiver? If it does, the receiver *must* be a pointer.
2. efficiency: If the receiver is large, a big `struct` for instance, it will be much cheaper to use a pointer receiver.

### interface

An interface is two things:

- it is a set of methods
- but it is also a type

The `interface{}` type (or `any` with Go 1.18+), the **empty interface** is the interface that has no methods. Since the empty interface has zero methods, all types implement the empty interface.

#### internal representation

An interface can be thought of as being represented internally by a tuple `(type, value)`. `type` is the underlying concrete type of the interface and `value` holds the value of the concrete type.

### generic

> introduced in go 1.18

#### function

```go
func MapKeys[K comparable, V any](m map[K]V) []K {
    r := make([]K, 0, len(m))
    for k := range m {
        r = append(r, k)
    }
    return r
}
```

- comparable is a interface meaning that we can compare values of this type with the `==` and `!=` operators
- any is an alias for `interface{}`

#### struct

```go
type List[T any] struct {
    head, tail *element[T]
}
	
type element[T any] struct {
    next *element[T]
    val  T
}

func (lst *List[T]) Push(v T) {
    if lst.tail == nil {
        lst.head = &element[T]{val: v}
        lst.tail = lst.head
    } else {
        lst.tail.next = &element[T]{val: v}
        lst.tail = lst.tail.next
    }
}
```

### collection

#### map

create: `make(map[key-type]val-type)`  `map[string](int){"foo": 1, "bar": 2}`

set value: `name[key] = val`

get value: `name[key]`

`len(map_var)` return number of key/value pairs in a map

remove a pair: `delete(m, "k2")`

What is a map variable?

> `var m map[string]int`
>
> Map types are **reference types**, like pointers or slices, and so the **value of `m` above is `nil`**; it doesn’t point to an initialized map. A nil map behaves like an empty map when reading, but **attempts to write to a nil map will cause a runtime panic**; don’t do that. To initialize a map, use the built in `make` function
>
> > 实际上map并不是reference，而是一个pointer to a `runtime.hmap` structure from [this post](https://dave.cheney.net/2017/04/30/if-a-map-isnt-a-reference-variable-what-is-it)

#### array

create: `var a [length]int`

initialize: `b := [5]int{1, 2, 3, 4, 5}`

set value: `array[index] = value`

get value: `array[index]`

> The type of elements and length are both part of the array’s type

#### slice

create: `make([]slice_type, initial_length)`

initialize: `t := []string{"g", "h", "i"}`

set and get are same as array

get a slice: we can get a slice using `s[low(included):high(excluded)]`

append: `s = append(s, "d")`

> we need to accept a return value from `append` as we may get a new slice value

copy: `copy(slice_to, slice_from)`

#### usage

在go中，将两个变量赋给同一个slice，map等，实际上这两个变量共享了这个数据结构的location，因此一个变量改变这个数据结构对另一个变量是可见的。

```go
m := make(map[int]int)
m[1] = 10
m[2] = 20
m2 := m
fmt.Println(m)
fmt.Println(m2)
m2[3] = 30
fmt.Println(m)
```

但go中又没有pass-by-reference [from post](https://dave.cheney.net/2017/04/29/there-is-no-pass-by-reference-in-go)

**所以将一个map传入一个函数，在函数内对它的操作函数外是不可见的。**

### print

- `func fmt.Println(a ...interface{})` 

  uses the default format of its arguments, and adds spaces between them.

- `func fmt.Printf(str string, ...interface{})`

  And you don't need to be particular about the type. `%v` will generally figure it out.

  ```golang
  fmt.Printf("Hello, playground %v\n",i)
  ```

  when printing structs, the plus flag (`%+v`) adds field names

## exception handling

error is a built-in interface

```go
type error interface {
    Error() string
}
```

defer

panic

recover

## goroutine

Goroutines run in the **same address space**, so access to shared memory must be synchronized.

```go
go f(s) // invoke a function in a goroutine
go func(msg string) { // an anonymous function call
    // do something
}("parameters")
```

### channel

pipes connecting concurrent goroutines, you can send values into channel from one gorountine and receive those values from another gorountine

create: `make(chan val-type)`

send value: `ch <- v`

receive value and assign it to v: `v := <-ch`

sends and receives block until the other side is ready. This allows goroutines to synchronize without explicit locks or condition variables.

#### buffered

buffered: `make(chan val-type, buffer_size)`

Sends to a buffered channel block only when the buffer is full. Receives block when the buffer is empty.

#### close

sender can close a channel (by calling `close(ch)`) and receivers can test whether a channel has been closes

`v, ok := <- ch`

`for i := range c` receives values from the channel repeatedly until it's closed

### context

Incoming requests to a server should create a Context, and outgoing calls to servers should accept a Context.

The WithCancel, WithDeadline, and WithTimeout functions take a Context (the parent) and return a derived Context (the child) and a CancelFunc.

Calling the CancelFunc cancels the child and its children, removes the parent's reference to the child, and stops any associated timers.

## dyn type

### type assertions

`x.(T)`

asserts that `x` is not `nil` and that the value stored in `x` is of type `T`. The notation `x.(T)` is called a *type assertion*.

### reflect

https://pkg.go.dev/reflect

Package reflect implements run-time reflection, allowing a program to manipulate objects with arbitrary types. The typical use is to take a value with static type interface{} and extract its dynamic type information by calling TypeOf, which returns a Type.

A call to ValueOf returns a Value representing the run-time data. Zero takes a Type and returns a Value representing a zero value for that type.

## go philosophy

### variable is allocated on heap or stack

[answer from go doc](https://go.dev/doc/faq#stack_or_heap)

- Each variable in Go exists as long as there are references to it.
- When possible, the Go compilers will allocate variables that are **local** to a function in that **function's stack frame**. However, if the compiler cannot prove that the variable is not referenced after the function returns, then the compiler must allocate the variable on the **garbage-collected heap** to avoid dangling pointer errors.
- if a local variable is very large, it might make more sense to store it on the heap rather than the stack.
- if a variable has its address taken, that variable is a candidate for allocation on the heap. However, a basic *escape analysis* recognizes some cases when such variables will not live past the return from the function and can reside on the stack.

### What makes go fast?

[ref](https://dave.cheney.net/2014/06/07/five-things-that-make-go-fast)

1. The size of value is small

    int is 4 bytes while for python, it's 24 bytes and Java Interger object is 16 ~ 24 bytes dependending on your JVM.

    And it makes Lx cache to cache more variables.

2. function inline and it enables other optimization like dead code elimination

    <img src="Go.assets/Gocon-2014-21.jpg" style="zoom:67%;" />

    <img src="Go.assets/Gocon-2014-22.jpg" style="zoom:67%;" />

3. escape analysis

    memory allocated on the heap comes at a cost. It is a debt that costs CPU time every time the GC runs until that memory is freed.

    <img src="Go.assets/Gocon-2014-25.jpg" style="zoom:67%;" />

    e.g.

    ```go
    func Sum() {
        numbers := make([]int, 100) // numbers will be allocated on stack which don't need to be garbage collected
        for i := range numbers {
            numbers[i] = i + 1
        }
        var sum int
        for _, i := range numbers {
            sum += i
        }
        return sum
    }
    ```

4. gorountine

    <img src="Go.assets/Gocon-2014-33.jpg" style="zoom:67%;" />

    Goroutines are cooperatively scheduled, rather than relying on the kernel to manage their time sharing.

    The switch between goroutines only happens at well defined points, when an explicit call is made to the Go runtime scheduler.

    <img src="Go.assets/Gocon-2014-34.jpg" style="zoom:67%;" />

    5. Segmented and copying stack

        motivation: Because it is hard to predict the stack requirements of a particular thread, a large amount of memory is reserved for each thread’s stack along with a guard page. The hope is that this is more than will ever be needed and the guard page will never be hit. The downside is that as the number of threads in your program increases, the amount of available address space is reduced.

        <img src="Go.assets/Gocon-2014-41.jpg" style="zoom:67%;" />

        <img src="Go.assets/Gocon-2014-42.jpg" style="zoom:67%;" />

        