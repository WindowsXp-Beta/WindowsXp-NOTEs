# React

> 抽象与封装 => 复用 => 代码易维护

启动：
`npx create-react-app project_name`
`npm start` or `yarn start`

## JSX

- 使用`{}`插入js代码

  > 注释 `{/*    */}`

- 可以在`if`和循环中使用JSX，将JSX赋给变量，把JSX当做参数传入，以及函数返回JSX。

- 属性值可以插入js表达式。`<img src={user.avatar} />`

## 元素

>元素是构成 React 应用的最小砖块。
>react元素是不可变对象，更新 UI 唯一的方式是创建一个全新的元素，并将其传入 `ReactDOM.render()`。

元素描述了你在屏幕上想看到的内容。
`const element = <h1>Hello, world</h1>;`

### component

组件让你可以将UI分成独立，可重用的部分。
**所有 React 组件都必须像纯函数一样保护它们的 props 不被更改。**

#### 定义组件

有两种方式

1. 使用函数

   ```javascript
   function Welcome(props) {
      return <h1>Hello, {props.name}</h1>
   }
   ```

2. 使用类

   ```javascript
   class Welcome extends React.Component {
      render() {//注意，我们需要在类中实现render方法
         return <h1>Hello, {this.props.name}</h1>;
      }
   }
   ```

   上面两种定义效果是一样的。

组件可以引用其他组件。

#### 渲染组件

使用元素
`const element = <Welcome name="sara"/>`
JSX将自定义元素的属性当做一个对象，称为`props`

>注意： 组件名称必须以大写字母开头。
>React 会将以小写字母开头的组件视为原生 DOM 标签。例如，`<div />` 代表 HTML 的 div 标签，而 `<Welcome />` 则代表一个组件，并且需在作用域内使用 Welcome。

#### state

要使用state，首先应将 _函数_ 转换为 _class_ ，再定义类的构造函数，将state初始化。

```javascript
constructor(props){
   super(props);
   this.state = ...
}
```

- 不要直接修改 State。 e.g.`this.state.comment = 'Hello';`。
- 而是应该使用 `setState()`。
- 使用箭头函数来解决`this.props`和`this.state`异步更新的问题。
- 数据是向下流动的。

##### setState

- `setState(updater, [callback])`
  updater为带有形式参数的`updater`函数`(state, props) => stateChange`，除了接受函数外，第一个参数也可以接受对象类型`{attribute: value}`。
- `setState()` 并不总是立即更新组件。它会批量推迟更新。这使得在调用 `setState()` 后立即读取 `this.state` 成为了隐患。

##### `React.useState()`

函数组件也可以具有状态，通过`React.useState()`函数。

```typescript
const [state, setState] = useState(initialState);
//initialState为状态初始值
//返回一个数组
//第一项为状态值
//第二项为一个函数，用于修改状态值
```

### 绘制

`ReactDOM.render(element, document.getElementById('root'));`在root上绘制。

## 事件处理

- React 事件的命名采用小驼峰式（camelCase），而不是纯小写。
- 使用 JSX 语法时你需要传入一个函数作为事件处理函数，而不是一个字符串。

事件处理函数通常被声明为类的方法，但由于Js中class不会默认绑定this，所以我们需要在构造函数中手动绑定。
`this.handleClick = this.handleClick.bind(this)`

> `bind()` 方法创建一个新的函数，在 `bind()` 被调用时，这个新函数的 `this` 被指定为 `bind()` 的第一个参数，而其余参数将作为新函数的参数，供调用时使用。

我们还可以使用箭头函数来避免`bind()`，`<button onClick={() => this.handleClick()}>`，但这又有一定问题:

> 如果该回调函数作为 prop 传入子组件时，这些组件可能会进行额外的重新渲染。我们通常建议在构造器中绑定或使用 class fields 语法来避免这类性能问题。

### 向事件处理函数传递参数

```javascript
<button onClick={(e) => this.deleteRow(id, e)}>Delete Row</button>
<button onClick={this.deleteRow.bind(this, id)}>Delete Row</button>
```

通过箭头函数传递参数时，需将 _事件对象`e`_ 显示的传递。

## lifecycle

### ComponentDidMount

1. componentWillMount  将要装载，在render之前调用；（已经deprecated了，使用constructor&didmount instead）

   componentDidMount，（装载完成），在render之后调用。

2. componentWillMount  每一个组件render之前立即调用；

   componentDidMount  render之后并不会立即调用，而是所有的子组件都render完之后才可以调用。

**将Ajax请求放在ComponentDidMount中**

<img src="/Users/weixinpeng/Desktop/NOTE_github/frontend/note_img/react_lifecycle.png" style="zoom:90%;" />

## 插入图片

1. `import`
2. 使用webpack的require函数

## [路由](https://reactrouter.com/web/guides/quick-start)

> we use `react-router-dom`

### Route matchers

1. switch

   当一个`<switch>`被render，它搜索它的`<Route>`孩子节点，找到一个与当前URL相符合的孩子节点的path，渲染这个孩子节点。

   path只检查URL的开头，因此`/`永远会被匹配。所以应该将**那些较为specific的Route**放在前面。

2. link

   类似于`<a>`的链接，提供了以下属性

   - `pathname`: A string representing the path to link to.

   - `search`: A string representation of query parameters.
   - `hash`: A hash to put in the URL, e.g. `#a-hash`.
   - `state`: State to persist to the `location`.