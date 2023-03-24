# WeChat Miniprogram

## 语法

### Json

1. JSON的Key必须包裹在一个双引号中

2. JSON的值只能是以下几种数据格式：

   1. 数字，包含浮点数和整数

   2. 字符串，需要包裹在双引号中

   3. Bool值，true 或者 false

   4. 数组，需要包裹在方括号中 []

   5. 对象，需要包裹在大括号中 {}

   6. Null

      > JSON不支持undefined

### WXML

#### 列表渲染

`wx:for`

```html
<block wx:for="{{unloads}}" wx:key="objectId">
    <template is="noticeTpl" data="{{...item}}" />
</block>
```

> 数组当前项的变量名默认为item，下标变量名默认为index。
>
> ...item是expand operator，将该变量（iterator）展开后传入data

#### 模板

定义

##### 使用



## App

宿主环境提供了 App() 构造器用来注册一个程序App，需要留意的是App() 构造器必须写在项目根目录的app.js里，App实例是单例对象。

App构造器

```javascript
App({
  onLaunch: function(options) {},
  onShow: function(options) {},
  onHide: function() {},
  onError: function(msg) {},
  globalData: 'I am global data'
})
```

| 参数属性 | 类型     | 描述                                                         |
| :------- | :------- | :----------------------------------------------------------- |
| onLaunch | Function | 当小程序初始化完成时，会触发 onLaunch（全局只触发一次）      |
| onShow   | Function | 当小程序启动，或从后台进入前台显示，会触发 onShow（当再次回到微信或者再次打开小程序时，微信客户端会把“后台”的小程序唤醒，我们把这种情况称为“小程序进入前台状态”，App构造器参数所定义的onShow方法会被调用。） |
| onHide   | Function | 当小程序从前台进入后台，会触发 onHide                        |
| onError  | Function | 当小程序发生脚本错误，或者 API 调用失败时，会触发 onError 并带上错误信息 |

## lift cycle

微信客户端初始化宿主环境 =》网络下载or本地缓存中拿到小程序的代码包，注入宿主环境 =》微信客户端给App实例派发onLaunch事件

## Communicate

小程序的渲染层和逻辑层分别由2个线程管理：渲染层的界面使用了WebView 进行渲染；逻辑层采用JsCore线程运行JS脚本。一个小程序存在多个界面，所以渲染层存在多个WebView线程，这两个线程的通信会经由微信客户端（下文中也会采用Native来代指微信客户端）做中转，逻辑层发送网络请求也经由Native转发。

<img src="./note_img/wx_communicate.jpeg" style="zoom:80%;" />

### 事件

- 事件是视图层到逻辑层的通讯方式

#### 使用方式

- 在组件中绑定一个事件处理函数。

  ```html
  <view id="tapTest" data-hi="Weixin" bindtap="tapName"> Click me! </view>
  ```

- 在相应的Page定义中写上相应的事件处理函数，参数是event。

  ```javascript
  Page({
    tapName: function(event) {
      console.log(event)
    }
  })
  ```

#### 事件分类

事件分为冒泡事件和非冒泡事件：

1. 冒泡事件：当一个组件上的事件被触发后，该事件会向父节点传递。
2. 非冒泡事件：当一个组件上的事件被触发后，该事件不会向父节点传递。

冒泡事件

|    类型     |                           触发条件                           |
| :---------: | :----------------------------------------------------------: |
| touchstart  |                       手指触摸动作开始                       |
|  touchmove  |                        手指触摸后移动                        |
| touchcancel |             手指触摸动作被打断，如来电提醒，弹窗             |
|  touchend   |                       手指触摸动作结束                       |
|     tap     |                      手指触摸后马上离开                      |
|  longpress  | 手指触摸后，超过350ms再离开，如果指定了事件回调函数并触发了这个事件，tap事件将不被触发 |
|   longtap   |   手指触摸后，超过350ms再离开（推荐使用longpress事件代替）   |

#### 绑定

1. 事件绑定的写法类似于组件的属性，如：

   ```html
   <view bindtap="handleTap">
       Click here!
   </view>
   ```

2. 事件绑定函数可以是一个数据绑定，如：

   ```html
   <view bindtap="{{ handlerName }}">
       Click here!
   </view>
   ```

   此时，页面的 `this.data.handlerName` 必须是一个字符串，指定事件处理函数名；如果它是个空字符串，则这个绑定会失效（可以利用这个特性来暂时禁用一些事件）。

可以用catch来绑定事件，防止事件冒泡：

> ```html
> <view id="outer" bindtap="handleTap1">
>   outer view
>   <view id="middle" catchtap="handleTap2">
>     middle view
>     <view id="inner" bindtap="handleTap3">
>       inner view
>     </view>
>   </view>
> </view>
> ```
>
> 点击 inner view 会先后调用`handleTap3`和`handleTap2`(因为tap事件会冒泡到 middle view，而 middle view 阻止了 tap 事件冒泡，不再向父节点传递)，点击 middle view 会触发`handleTap2`，点击 outer view 会触发`handleTap1`。

#### 事件对象

**BaseEvent 基础事件对象属性列表：**

|                             属性                             |  类型   |              说明              |
| :----------------------------------------------------------: | :-----: | :----------------------------: |
| [type](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxml/event.html#type) | String  |            事件类型            |
| [timeStamp](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxml/event.html#timeStamp) | Integer |       事件生成时的时间戳       |
| [target](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxml/event.html#target) | Object  | 触发事件的组件的一些属性值集合 |
| [currentTarget](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxml/event.html#currenttarget) | Object  |    当前组件的一些属性值集合    |
| [mark](https://developers.weixin.qq.com/miniprogram/dev/framework/view/wxml/event.html#mark) | Object  |          事件标记数据          |

currentTarget VS target:

事件绑定的当前组件 VS 触发事件的源组件

这两者都有dataset属性，类型为object，表示组件上由`data-`开头的自定义属性组成的集合。

## page

一个页面是分三部分组成：界面、配置和逻辑。界面由WXML文件和WXSS文件来负责描述，配置由JSON文件进行描述，页面逻辑则是由JS脚本文件负责。

> 一个页面的文件需要放置在同一个目录下，其中WXML文件和JS文件是必须存在的，JSON和WXSS文件是可选的。

### 页面构造器Page()

```javascript
Page({
  data: { text: "This is page data." }, //Object	页面的初始数据
  onLoad: function(options) { },//监听页面加载，触发时机早于onShow和onReady
  onReady: function() { },//监听页面初次渲染完成
  onShow: function() { },//监听页面显示，触发事件早于onReady
  onHide: function() { },//监听页面隐藏
  onUnload: function() { },//监听页面卸载
  onPullDownRefresh: function() { },
  onReachBottom: function() { },
  onShareAppMessage: function () { },
  onPageScroll: function() { }
})
```

### data

WXML可以通过数据绑定的语法绑定从逻辑层传递过来的数据字段，这里所说的数据其实就是来自于页面Page构造器的data字段，data参数是页面第一次渲染时从逻辑层传递到渲染层的数据。

setData函数可以将数据传递给渲染层，从而更新界面，因为小程序渲染层和逻辑层在两个线程中，所以它是异步的，并提供了一个回调函数，调用格式一般为`setData(data, callback)`

> 不需要每次都将整个data字段重新设置一遍，你只需要把改变的值进行设置即可，宿主环境会自动把新改动的字段合并到渲染层对应的字段中。

### 路由

1. wx.navigateTo({ url: 'pageD' }) 可以往当前页面栈多推入一个 pageD，此时页面栈变成 [ pageA, pageB, pageC, pageD ]。
2. wx.navigateBack() 可以退出当前页面栈的最顶上页面，此时页面栈变成 [ pageA, pageB, pageC ]。
3. wx.redirectTo({ url: 'pageE' }) 是替换当前页变成pageE，此时页面栈变成 [ pageA, pageB, pageE ]，当页面栈到达10层没法再新增的时候，往往就是使用redirectTo这个API进行页面跳转。

#### tab

app.json中可以定义小程序底部的tab

```json
{
  "tabBar": {
    "list": [
      { "text": "Tab1", "pagePath": "pageA" },
      { "text": "Tab1", "pagePath": "pageF" },
      { "text": "Tab1", "pagePath": "pageG" }
    ]
  }
}
```

使用wx.switchTab({ url: 'pageF' })，此时原来的页面栈会被清空（除了已经声明为Tabbar页pageA外其他页面会被销毁），然后会切到pageF所在的tab页面，页面栈变成 [ pageF ]，此时点击Tab1切回到pageA时，pageA不会再触发onLoad，因为pageA没有被销毁。

wx.navigateTo和wx.redirectTo只能打开非TabBar页面，wx.switchTab只能打开Tabbar页面。

## 组件

> 就是html中的`<div>`之类的东西，官方提供了一些[基础组件](https://developers.weixin.qq.com/miniprogram/dev/component/)

组件属性

| 属性名 | 类型    | 描述           | 其他说明                                 |
| :----- | :------ | :------------- | :--------------------------------------- |
| id     | String  | 组件的唯一标示 | 保持整个页面唯一                         |
| class  | String  | 组件的样式类   | 在对应的WXSS中定义的样式类               |
| style  | String  | 组件的内联样式 | 可以通过数据绑定进行动态设置的内联样式   |
| hidden | Boolean | 组件是否显示   | 所有组件默认显示                         |
| data-* | Any     | 自定义属性     | 组件上触发的事件时，会发送给事件处理函数 |

### 自定义组件

类似于页面：一个自定义组件由json，wxml，wxss，js四个文件组成

e.g.

```js
Component({
  properties: {
    // 这里定义了innerText属性，属性值可以在组件使用时指定
    innerText: {
      type: String,
      value: 'default value',
    }
  },
  data: {
    // 这里是一些组件内部数据
    someData: {}
  },
  methods: {
    // 这里是一个自定义方法
    customMethod: function(){}
  }
})
```

**attention**

1. WXML 节点标签名只能是小写字母、中划线和下划线的组合，所以自定义组件的标签名也只能包含这些字符。

#### 生命周期

1. 组件实例刚刚被创建好时， `created` 生命周期被触发。此时，组件数据 `this.data` 就是在 `Component` 构造器中定义的数据 `data` 。 **此时还不能调用 `setData` 。**
2. 在组件完全初始化完毕、进入页面节点树后， `attached` 生命周期被触发。此时， `this.data` 已被初始化为组件的当前值。这个生命周期很有用，绝大多数初始化工作可以在这个时机进行。
3. 在组件离开页面节点树后， `detached` 生命周期被触发。退出一个页面时，如果组件还在页面节点树中，则 `detached` 会被触发。

##### 定义

从2.2.3开始，在lifetimes字段中声明。

```javascript
Component({
  lifetimes: {
    attached: function() {
      // 在组件实例进入页面节点树时执行
    },
    detached: function() {
      // 在组件实例被从页面节点树移除时执行
    },
  }
```

#### 使用自定义组件

首先在json文件中引用声明

```json
{
  "usingComponents": {
    "component-tag-name": "path/to/the/custom/component"
  }
}
```

可以在组件使用时指定定义的properties

```js
Component({
  properties: {
    // 这里定义了 innerText 属性，属性值可以在组件使用时指定
    innerText: {
      type: String,
      value: 'default value',
    }
  },
})
```

使用时指定

```xml
<component-tag-name inner-text="Some text"></component-tag-name>
```

#### 组件所在页面的生命周期

| 生命周期 |     参数      |             描述             |
| :------: | :-----------: | :--------------------------: |
|   show   |      无       |  组件所在的页面被展示时执行  |
|   hide   |      无       |  组件所在的页面被隐藏时执行  |
|  resize  | `Object Size` | 组件所在的页面尺寸变化时执行 |

## 云函数

云函数即在云端（服务器端）运行的函数。在物理设计上，一个云函数可由多个文件组成，占用一定量的 CPU 内存等计算资源；各云函数完全独立；可分别部署在不同的地区。开发者无需购买、搭建服务器，只需编写函数代码并部署到云端即可在小程序端调用，同时云函数之间也可互相调用。

> 云开发的云函数的独特优势在于与微信登录鉴权的无缝整合。当小程序端调用云函数时，云函数的传入参数中会被注入小程序端用户的 openid，开发者无需校验 openid 的正确性因为微信已经完成了这部分鉴权，开发者可以直接使用该 openid。

### Bmob

#### 数据查询

```javascript
find({
  "table":"XXX",          //表名
  "keys":"a,b,c",         //返回字段列表，多个字段用,分隔
  "where":{"a":"XXXX","b":"XXXX"},       //查询条件是一个JSON object
  //"where":{"c":{"$ne":1}},       //条件查询 查询c字段值不为1的记录
  "order":"-a,b",         //排序列表，[-]字段名称,-表示降序，默认为升序
  "limit":10,            //limit大小，一页返回多少条记录，默认为0
  "skip":2,             //skip,分页offset，(page-1)*limit
  "count":1,            //count,只返回符合条件的记录总数
  "include":"key1,key2,key3" //返回关联类型，其中include的Key必须是Pointer类型
 },function(err,data){    //回调函数
 });
```



#### js sdk



