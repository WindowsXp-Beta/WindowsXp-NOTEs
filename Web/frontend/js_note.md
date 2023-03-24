# JS Note

> including javascript, ECMAscript, typescript, React.js and other libraries

[如何最快速的找到页面某一元素所绑定的点击事件，并查看js代码](https://blog.csdn.net/jmd88888888/article/details/70919378)

## dirty work

### node version control

use nvm

`nvm ls-remote` To see what Node versions are available to install run

`nvm install $node_latest_version`

`nvm ls` you can verify what is installed with

`nvm use $version_you_want_to_use`  use specific version

## Syntax

[Javascript best practice](https://www.w3schools.com/js/js_best_practices.asp)

**弱类型**

注释：块 /* */
行 //

### import & export

`export`

- 默认情况下，JavaScript中在模块内的所有声明都是本地的，外部无法访问。如果需要公开模块中部分声明的内容，并让其它模块加以使用，这个时候就需要导出功能，最简单的方式是添加export关键字导出模块。

- 可以导出的内容包括类、函数以及var、let和const修饰的变量。export命令可以出现在模块的任何位置，只要处于模块顶层就可以。如果处于块级作用域内，就会报错，import命令也是如此。

> default : 一个模块仅仅只允许导出一个`default`对象，实际导出的是一个`default`命名的变量进行重命名，等价语句如下。
>
> ```javascript
> import any from './requireTest'
> /***The above and the latter are equal***/
> import {default as any } from './requireTest'
> ```
>
> 所以`import`后可以是任意变量名称，且不需要`{}`。

`import`

- import命令接受一对大括号，里面指定要从其他模块导入的变量名。大括号里面的变量名，必须与被导入模块（profile.js）对外接口的名称相同。如果想为输入的变量重新取一个名字，import命令要使用as关键字，将输入的变量重命名。

### 变量

变量名又称为`标识符`，必须以**字母，数字，下划线，美元符号开头；后续的字符也可以是数字**，不能用关键字，js是对大小写敏感的。
声明变量

- var x = 5 （全局变量）
- x = 5 (not recommended)
- let x = 5 （局部变量）
- const x = 5 (局部变量)
  可以定义为一个数组或对象。const不是不可变，而是变量标识符不可重定义，例如可以修改对象、数组内的值，但不能重新赋给一个新的对象或数组。

#### 初始化

It is a good coding practice to initialize variables when you declare them.

This will:

- Give cleaner code
- Provide a single place to initialize variables
- Avoid undefined values

```javascript
let arr = []
let obj = {}
```

不要使用new来初始化。

- Use `""` instead of `new String()`
- Use `0` instead of `new Number()`
- Use `false` instead of `new Boolean()`
- Use `{}` instead of `new Object()`
- Use `[]` instead of `new Array()`
- Use `/()/` instead of `new RegExp()`
- Use `function (){}` instead of `new Function()`

#### 变量类型

|  变量   |                             解释                             |                             示例                             |
| :-----: | :----------------------------------------------------------: | :----------------------------------------------------------: |
| String  | 字符串（一串文本）：字符串的值必须用引号（单双均可，必须成对）扩起来。 |                   let myVariable = '李雷';                   |
| Number  |                数字：无需引号。包含int和float                |                     let myVariable = 10;                     |
| Boolean | 布尔值（真 / 假）： true/false 是 JS 里的特殊关键字，无需引号。 |                    let myVariable = true;                    |
|  Array  |           数组：用于在单一引用中存储多个值的结构。           | let myVariable = [1, '李雷', '韩梅梅', 10]; 元素引用方法：myVariable[0], myVariable[1] …… |
| Object  | 对象：JavaScript 里一切皆对象（除了基础类型，数组也是Object），一切皆可储存在变量里。这一点要牢记于心。 | let myVariable = document.querySelector('h1'); 以及上面所有示例都是对象。 |

- 获取数组长度：`array_var.length`
- `typeof null = object`

##### 字符串

- 格式化字符串： \`${}\`  在{}中可以添加js表达式。

##### 数组

`forEach` vs `map`

两者都将传入的callback `function(value, index, array)`作用在每一个元素上，但是map会**返回一个新数组**（每个元素都是回调函数作用在每个元素上的返回值，因此如果不返回，那么新数组就是[undefined, ...]）而foreach**不会**。

### object

#### initializer

```javascript
const obj = {
  property_1:   value_1,   // property name may be an identifier...
  2:            value_2,   // or a number...
  // ...,
  'property n': value_n    // or a string
};
```

property name may be an **identifier**, **number** or a **string**

#### 属性访问器

> member operation

```javascript
object.property
object['property']
```

1. 访问没有定义的property返回undefined

2. 可以直接给没有在初识化中定义的property赋初值，比如 `object.undefined_property = initial_value`
3. object property names (keys) can only be strings or Symbols

> Symbol is **a primitive data type of JavaScript** introduced in ECMAscript 2015, along with string, number, boolean, null and undefined.
>
> You create a symbol by calling `Symbol()`

#### method

两种写法

```javascript
let person = {
    hello: function() {
        return 'hello'
    },
    world() {
        return 'world'
    }
}
```

同样，也可以不定义直接赋初值。

### 运算符

| 运算符 |  作用  |
| :----: | :----: |
|  ===   |  等于  |
|  !==   | 不等于 |
|   !    |  取非  |

#### question mark

`a?.property_or_method()`

if a is undefined, the above line will return a `undefined` instead of raising an error

如果a是一个方法，你可以通过`?.()`来调用它，如果a undefined，则会返回undefined

`rightexp ?? leftexp`

if the `rightexp` is null or undefined, then it will return the value of the `leftexp`

`x ??= y`

nullish assignment: only assign if x is null

### control flow

`if`,`if - else`,`if-else if-else`,`switch` same as c

switch 使用 `===` 比较，因此可以使用字符串等

### 函数

```javascript
function fun_name(p1, p2, p3) {
   return p1 + p2 + p3;
}
```

#### default parameter

```javascript
function fnName(param1 = defaultValue1, ..., paramN = defaultValueN) { ... }
```

#### 函数表达式

```javascript
var x = function (a, b) {return a * b};
```

在变量中保存函数表达式之后，此变量可用作函数。
`var z = x(3,4)`

`javascript`中函数也是对象，它们能被“存储”在变量中，能作为函数参数被传递，能在函数中被创建，能从函数中返回。

#### 箭头函数

lambda expression
`(param1, param2, ..., paramN) => {statements}`

#### this

this像是一个函数的参数，它随着执行环境的改变而改变。

### 类

#### 类声明

```javascript
class class_name {
   constructor(para1, para2) {
      this.a = para1;
      this.b = para2;
   }
   //构造函数只能有一个
}
```

#### 类表达式

```javascript
// 未命名/匿名类
let Rectangle = class {
  constructor(height, width) {
    this.height = height;
    this.width = width;
  }
};
console.log(Rectangle.name);
//可以通过类的（不是实例的）name属性访问它
// output: "Rectangle"

// 命名类
let Rectangle = class Rectangle2 {
  constructor(height, width) {
    this.height = height;
    this.width = width;
  }
};
console.log(Rectangle.name);
// 输出: "Rectangle2"
```

函数声明会提升，类声明不会提升，因此首先需要声明类，然后再访问它。

## 异步

### Promise

example

```javascript
function test() {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve('hello world')
            // reject('hello world')
        }, 1000)
        console.log(100)
    }
    ).then((res) => {
        console.log('right')
        console.log(res)
    }).catch((err) => {
        console.log('wrong')
        console.log(err)
    })
}
test()
console.log('after test')
```

The output is

```
100
after test
right
hello world
```

可见setTimeout这种异步函数不会立刻执行，而是先执行后面的js语句，通过resolve或者reject结束Promise从而调用通过then或者catch attach的callback函数。

1. Callbacks added with [`then()`](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Promise/then) will never be invoked before the [completion of the current run](https://developer.mozilla.org/en-US/docs/Web/JavaScript/EventLoop#run-to-completion) of the JavaScript event loop.

    ```javascript
    Promise.resolve().then(() => console.log(2));
    console.log(1);
    // Logs: 1, 2
    ```

2. catch is shorthand for `then(null, FailureCallback)`

3. then返回的也是一个Promise，所以可以链式调用

4. 也可以通过throw reject一个Promise，不过不能在async callback中使用，详见[link](https://stackoverflow.com/a/33446005/16598178)

### async/await

#### async的作用

async 函数（包含函数语句、函数表达式、Lambda表达式）会返回一个 Promise 对象，如果在函数中 `return` 一个直接量，async 会把这个直接量通过 `Promise.resolve()` 封装成 Promise 对象。

所以在没有await的情况下执行async function，它会立刻执行，并返回一个Promise对象。

#### await

await是个运算符，用于组成表达式，如果它等到的不是一个 Promise 对象，那 await 表达式的运算结果就是它等到的东西。

如果它等到的是一个 Promise 对象，await 就忙起来了，它会阻塞后面的代码，等着 Promise 对象 resolve，然后得到 resolve 的值，作为 await 表达式的运算结果。

## JS/ES new syntax

> ECMAScript6 reference:
>
> [《ES6标准入门》](https://es6.ruanyifeng.com)

### destructuring assignment

> [MDN doc](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Operators/Destructuring_assignment)

#### object

对象的解构赋值，可以很方便地将现有对象的方法，赋值到某个变量。

1. basic

    ```javascript
    // method
    let { log, sin, cos } = Math;
    const { log } = console;
    log('hello') // hello
    ```

    ```javascript
    // property
    const user = {
        id: 42,
        isVerified: true,
        school: { high: 'xj' },
    }
    const { id, isVerified } = user // id = user.id
    // id is 42 and isVerified is true
    // change name and provide a default value
    const { id: foo, isVerified: bar = false } = user // foo = user.id
    // nested
    let { school: { high: foo } } = user
    ```

    解构看起来规则挺多，其实很好理解：

    `let { property: alias  = default_value } = object`

    它等价于 `let alias = object.property`，其中alias的缺省值就是property。

    关于nested，说白了就是递归解构，比如上例中解析high school就是：

    1. `{high: foo} = user.school`
    2. `foo = user.school.high`

2. 函数参数

    e.g.

    ```javascript
    function drawChart({
      size = "big",
      coords = { x: 0, y: 0 },
      radius = 25,
    } = {}) {
      console.log(size, coords, radius);
    }
    ```

    初值为`{}`

### `() & [] & {}`

[JavaScript中圆括号`()` 和 方括号`[]` 的特殊用法疑问？](https://www.zhihu.com/question/20127472)

### three dots(...)

#### rest parameters

```javascript
function myFunc(a, b, ...args) {
 console.log(a); // 22
 console.log(b); // 98
 console.log(args); // [43, 3, 26]
};
myFunc(22, 98, 43, 3, 26);
```

args会将所有剩余的参数全部放到一个JavaScript的array中。

#### spread operators

```javascript
function myFunc(x, y, ...params) { // used rest operator here
  console.log(x);
  console.log(y);
  console.log(params);
}

var inputs = ["a", "b", "c", "d", "e", "f"];
myFunc(...inputs); // used spread operator here
// "a"
// "b"
// ["c", "d", "e", "f"]
```

将iterable（比如array）的元素展开。

```javascript
const featured = ['Deep Dish', 'Pepperoni', 'Hawaiian'];
const specialty = ['Meatzza', 'Spicy Mama', 'Margherita'];

const pizzas = [...featured, 'veg pizza', ...specialty];

console.log(pizzas); // 'Deep Dish', 'Pepperoni', 'Hawaiian', 'veg pizza', 'Meatzza', 'Spicy Mama', 'Margherita'
```
