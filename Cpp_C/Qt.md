# Qt

## basic

`上下文相关帮助`链接到文档。

### Q&A

1. 碰到error: 1 duplicate symbol for architecture x86_64时去看**编译输出**

   > 编译问题都应该先去看编译输出

## signal&slot

1. https://www.jianshu.com/p/d6fc0bb0689a
2. https://blog.csdn.net/zkl99999/article/details/53787044

> **信号就是一个个的函数名，返回值是 void（因为无法获得信号的返回值，所以也就无需返回任何值），参数是该类需要让外界知道的数据。信号作为函数名，不需要在 cpp 函数中添加任何实现。**

关于信号的参数，这个参数可以被槽函数接受。

所以两者声明必须满足一定条件。

> 如果信号的参数有默认值，那么传递给`SIGNAL()`宏的参数个数不能少于`SLOT()`宏的参数个数。
>
> 信号槽要求信号和槽的参数一致，所谓一致，是参数类型一致。如果不一致，允许的情况是，槽函数的参数可以比信号的少，即便如此，槽函数存在的那些 ，参数的顺序也必须和信号的前面几个一致起来。这是因为，你可以在槽函数中选择忽略信号传来的数据（也就是槽函数的参数比信号的少），但是不能说信号根本没有这个数据，你就要在槽函数中使用（就是槽函数的参数比信号的多，这是不允许的）。

- **发送者和接收者都需要是QObject的子类（当然，槽函数是全局函数、Lambda 表达式等无需接收者的时候除外）；**

  > 这意味着你自己写的类必须继承QObject

- **使用 signals 标记信号函数，信号是一个函数声明，返回 void，不需要实现函数代码；**

- **槽函数是普通的成员函数，作为成员函数，会受到 public、private、protected 的影响；**

  > 如果信号是 private 的，这个信号就不能在类的外面连接，也就没有任何意义。

- **使用 emit 在恰当的位置发送信号；**

- **使用QObject::connect()函数连接信号和槽。**

- **任何成员函数、static 函数、全局函数和 Lambda 表达式都可以作为槽函数**

### bug and trick

1. 不能删除信号传递过来的指针，因为你不知道有多少槽函数connect同一个信号 [ref link](https://stackoverflow.com/questions/19364172/qt-deletion-pointer-method)

   解决方案：QSharedPointer

2. QTimer::singleShot 如果SLOT要参数，使用lambda表达。

## 事件循环

类：`QEventLoop`

方法：`exec()`来启动一个事件循环，在这个循环期间，可以调用`exit()`来强制使`exct()`返回。

**子层事件循环具有父层事件循环的所有功能，所以当在主线程中启动各种exec()（比如QEventLoop::exec()）时，虽然会打断main函数中的QApplication::exec()，但是Gui界面还是可以正常响应，不会出现卡住的现象。这与用while来循环是不一样的。**

使用信号槽机制

## 继承 QObject

Golden Rules

1. Make sure the `Q_OBJECT` macro is present in the definition of all `QObject`-derived classes.

2. Make sure you declare your `QObject`-derived classes in your header files **only**.

3. Make sure all of your header files are listed in your .pro file in the `HEADERS=` list.

4. Run `qmake` every time you add `Q_OBJECT` to one of your classes or modify your `.pro` file.

   > In Qt creator, run qmake by `right click` the project then select `run qmake`

## qt memory management system

> invoke: why does QTimer need a parent in its constructor?

[Memory management in Qt?](https://stackoverflow.com/questions/2491707/memory-management-in-qt)

main idea:

- initialise all newly created `QObject`s with a parent, and the `parent` destructor will take care of destroying `child`
- It does this by issuing signals, so it is safe even when you delete `child` manually before the parent.

## QGraphics三件套

> Qgraphics view, scene, item
>
> [When to use QGraphicsScene or QWidget?](https://www.qtcentre.org/threads/5592-When-to-use-QGraphicsScene-or-QWidget)
>
> A: If I were to make a rule of a thumb, I'd say that you should use QGraphicsView whenever you want to create a large amount of objects that either change their state very often (animate) or require interaction with the user (selecting, moving, zooming). In other situations use QWidget. 
>
> QWidget支持更丰富的style。

### coordinate system

坐标系x向右，y向下。

Graphics View's scene coordinates correspond to QPainter's logical coordinates, and view coordinates are the same as device coordinates.

Items live in their own local coordinate system.

For example, if you receive a mouse press or a drag enter event, the event position is given in item coordinates. The QGraphicsItem::contains() virtual function, which returns true if a certain point is inside your item, and false otherwise, takes a point argument in item coordinates. Similarly, an item's bounding rect and shape are in item coordinates.

paint() also works in local coordinates as doc saying `All painting is done in local coordinates`.

**QGraphicsScene and QGraphicsView will perform all transformations for you.**

> 这是为什么Snake中`Snake::shape()`和`Snake::boundingRect()`要对tail这个QList中的每一个点调用mapFromScene()；新增food时检查食物是否在蛇所在坐标上时要将食物的坐标snake->mapFromScene(food_coordinate)。

### 理解setSceneRect

[ref: PyQt5: I can't understand QGraphicsScene's setSceneRect(x, y, w, h)](https://stackoverflow.com/questions/55780918/pyqt5-i-cant-understand-qgraphicsscenes-setscenerectx-y-w-h)

main idea:

- If the whole scene is visible in the view, (i.e., there are no visible scroll bars,) the view's alignment will decide where the scene will be rendered in the view.**And the default value is Qt::AlignCenter**

- the alignment is not about QRectF(0, 0, w, h) but the center of QRectF(x, y, w, h) which in this case is (100,100). So keep centered on sceneRect in the QGraphicsView.

- 将view比作camera，用来拍摄scene。一些观察：setRect后绘画的坐标仍然可以超过这个rect，只影响坐标系。

  > 只要别调用view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding)，这玩意儿的作用待研究，大概是会调整scene到view的合适区域，还会涉及的坐标系的scale等等。

[QGraphicsItem setPos is not moving item's position](https://stackoverflow.com/questions/7761442/qgraphicsitem-setpos-is-not-moving-items-position)

That means when the view is first shown, it uses the combined item bounds as its bounds. So when you first added the item, whatever the item's position is, it will be used as the top-left of the displayed scene. So your item is actually moved, but the scene is shown with an offset. So it looks like it's at (0, 0). And when you move it the second time, it's actually moved twice already.

The solution is to set the [`sceneRect`](http://doc.trolltech.com/latest/qgraphicsview.html#sceneRect-prop) to a known rect before showing it. That will fix the displayed area.

### 一些具体的绘图函数

- advance()

This function is intended for animations. 通常将scene的advance和timer connect然后当scene更新时更新它的所有子组件。

- update()

Schedules a redraw of the area covered by rect in this item. You can call this function whenever your item needs to be redrawn, such as if it changes appearance or size.（not change position, so don't call setPos in paint）

- setPos

将item放置到scene上的指定位置。当改变很多个item的位置时，可能会卡住。因此对于一些不用改变位置的item，应该把setPos放到构造函数里。

何时会调用paint()函数？

1. addItem时会调用。
1. setPos并<del>不会调用paint</del>（会调，所以不能在paint里调setPos，不然就循环了），它只是改变item的位置。

### other tips

- removeItem不会delete，scene->clear()会removeItem并且delete
- 将QGraphicsView放到QMainWindow里时，在设计中加入的组件（比如QLabel）都会看不见，需要将这些组件setParent(view)

### Inherits of QGraphicsItem

比如有可以使用信号的QGraphicsObject，方便向QWidget port的QGraphicsWidget，将QWidget嵌入QGraphicsItem的QGraphicsProxyItem等。具体见文档。

ref：[How can set a Qwidget inside a QGraphicsWidget?](https://stackoverflow.com/questions/19343238/how-can-set-a-qwidget-inside-a-qgraphicswidget)

## bugs log

### QTimer

- QTimer::start() 会反复计时，并触发Timeout signal。可以通过设置singleSlot来使其只运行一次。

- QTimer::start(int seconds) 会改变QTimer的Interval。

### keyevent

QGraphicsView会拦截方向键（作为屏幕的scroll），因此需要keyeventfilter。

### QMessageBox

QMessageBox的static函数，比如information，warning，需要返回后才会继续执行之后的东西，so order matters。

## code review

### snake

更新蛇

用Timer::time.start()定时调用`void QGraphicsScene::advance()`，这会调用scene中的每一个`QGraphicsItem::advance()`。

### qlink

- 布局

pushbutton放在maplayout下面，maplayout通过addWidget加入一个Vboxlayout

pushbutton调用setGeometory加入parent widget

- 移动

每20ms handle一次keypress，在handlekeypress时将pressedkeys（`QSet<int>`）中的key取出，进行检查。并调用moveplayer，使用QSet，这样可以避免重复的按键被加入。

> 我实现的一点问题，通过contains决定player的移动方向，所以W的优先级低于A，D。比如set中既有W也有A，先判断了W，把player设置为向上，再判断A又把player设置为想左，因此不支持斜着移动。
