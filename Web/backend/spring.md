# spring Note

## annotation

> 每个框架自己定义

annotation不影响字节码，框架（比如spring）在加载字节码的时候处理这些annotation，加入一些字节码。

### annotation & explanation

- Controller

  `@RestController` VS `@Controller`，`@RestController`会将java对象转化成JSON然后返回client。

- Mapping

  其实每种HTTP method都有一种，但`@RequestMapping("/{id}")`即可匹配所有的请求（为了体现RestFul API一般不用这个通配的）而使用HTTP verb对应的@Get/Put/Post/DeleteMapping

  配合上面这些Mapping的annotation
  
  - @RequestParam & @RequestBody
  
    [Spring @RequestParam Annotation](https://www.baeldung.com/spring-request-param) 

    [Spring’s RequestBody and ResponseBody Annotations](https://www.baeldung.com/spring-request-response-body)

    @RequestParam会接收来自 URL中的param，和responsebody中的form data（比如form-data和x-www-form-urlencoded数据 两种的不同见[四种常见的 POST 提交数据方式](https://imququ.com/post/four-ways-to-post-data-in-http.html)）其中有两种接收方式，直接接收，比如`@RequestParam String username`就是直接找URL中的 username=var 或者form中的`key:username, value:usernameValue`，如果前后端变量名一样，可以不在@后写(name="username")。还有一种就是用Map接受form数据，经试验，不能接受URL中的数据。

    > 网上资料有说RequestParam处理参数的方式就是将URL中的参数和form中的参数搞成一个Map。

    @RequestBody会接受HTTP request body中的参数，可以拿Map或者Entity接受application/json。或者直接拿个String把整个body以String的形式读入（比如json读进来就是裸的 {...} ）。但是其他 application/form-data，application/x-www-form-urlencoded，application/plain都会报错。（似乎可以通过设置produces属性来选择接受的application类型，但没试过）

    你也可以在函数里同时使用@RequestParam和@RequestBody两种东西，比较好的方法是Param取URL中的数据，Body取json中的数据。两种一起使用可以会出现的问题[Spring MVC - Why not able to use @RequestBody and @RequestParam together](https://stackoverflow.com/questions/19468572/spring-mvc-why-not-able-to-use-requestbody-and-requestparam-together) 经过检验前面的使用方法不会出现这样的问题。

  - @PathVariable

    [Spring @PathVariable Annotation](https://www.baeldung.com/spring-pathvariable)

- Lombok

  @Data  提供了 `@ToString`, `@EqualsAndHashCode`, `@Getter` on all fields, `@Setter` on all non-final fields, and `@RequiredArgsConstructor` 方法。


CORS（Cross-origin resource sharing） filter

`@CrossOrigin` 解决跨域问题。

## 序列化

### 概念

序列化：把对象转化为可传输的字节序列过程称为序列化。

反序列化：把字节序列还原为对象的过程称为反序列化。

为什么需要序列化

- 序列化最终的目的是为了对象可以跨平台存储，和进行网络传输。而我们进行跨平台存储和网络传输的方式就是IO，而我们的IO支持的数据格式就是字节数组。
- 因为我们单方面的只把对象转成字节数组还不行，因为没有规则的字节数组我们是没办法把对象的本来面目还原回来的，所以我们必须在把对象转成字节数组的时候就制定一种规则（序列化），那么我们从IO流里面读出数据的时候再以这种规则把对象还原回来（反序列化）。

- 如果我们要把一栋房子从一个地方运输到另一个地方去，序列化就是我把房子拆成一个个的砖块放到车子里，然后留下一张房子原来结构的图纸，反序列化就是我们把房子运输到了目的地以后，根据图纸把一块块砖头还原成房子原来面目的过程

什么时候使用序列化

- 凡是需要进行“跨平台存储”和”网络传输”的数据，都需要进行序列化。
- 本质上存储和网络传输都需要经过把一个对象状态保存成一种跨平台识别的字节格式，然后其他的平台才可以通过字节信息解析还原对象信息。

## spring MVC

### MVC

>  MVC stands for Model View Controller

前端视图View（maybe React.js or Vue.js），后端业务逻辑Model（maybe java or Django），各自发出的请求，由中间的Controller进行传递（将哪个Model显示在哪个View上，servelet就充当了一个这样的角色），接受前端HTTP请求，选择调哪个服务（service），从而实现前端与后端解耦。

MVC也可以全部在后端：比如Servlet返回html（`return "<html>"`）页面，或者通过JSP。把View放在后端。

### spring MVC

 <img src="./note_img/springMVC.png" style="zoom:40%;" />

1. dispatcher拦截所有的http请求并进行分发。（分发逻辑写在xml文件里）
2. 查找annotation或者xml文件。
3. 来了一个请求后，通过2，我们知道该将这个请求交由哪个Controller处理。
4. Controller返回一个ModelAndView，通过ViewResolver解析这个东西。
5. 最后返回前端View。

### Layered Architecture

> 分层依据

<img src="./note_img/SpingArchitecture.png" style="zoom:40%;" />

### RESTful API

[RESTful API 设计指南（from Ruan YiFeng）](https://www.ruanyifeng.com/blog/2014/05/restful_api.html)

HTTP方法使用

RESTful API中将HTTP作为应用层协议。

- GET（SELECT）：从服务器取出资源（一项或多项）。
- POST（CREATE）：在服务器新建一个资源。
- PUT（UPDATE）：在服务器更新资源（客户端提供改变后的完整资源）。
- PATCH（UPDATE）：在服务器更新资源（客户端提供改变的属性）。
- DELETE（DELETE）：从服务器删除资源。

> POST与PUT的区别：
>
> POST方法不具备幂等性，即多次提交会产生多个记录。

状态码：

- 200 OK - [GET]：服务器成功返回用户请求的数据，该操作是幂等的（Idempotent）。
- 201 CREATED - [POST/PUT/PATCH]：用户新建或修改数据成功。
- 202 Accepted - [*]：表示一个请求已经进入后台排队（异步任务）
- 204 NO CONTENT - [DELETE]：用户删除数据成功。
- 400 INVALID REQUEST - [POST/PUT/PATCH]：用户发出的请求有错误，服务器没有进行新建或修改数据的操作，该操作是幂等的。
- 401 Unauthorized - [*]：表示用户没有权限（令牌、用户名、密码错误）。
- 403 Forbidden - [*] 表示用户得到授权（与401错误相对），但是访问是被禁止的。
- 404 NOT FOUND - [*]：用户发出的请求针对的是不存在的记录，服务器没有进行操作，该操作是幂等的。
- 406 Not Acceptable - [GET]：用户请求的格式不可得（比如用户请求JSON格式，但是只有XML格式）。
- 410 Gone -[GET]：用户请求的资源被永久删除，且不会再得到的。
- 422 Unprocesable entity - [POST/PUT/PATCH] 当创建一个对象时，发生一个验证错误。
- 500 INTERNAL SERVER ERROR - [*]：服务器发生错误，用户将无法判断发出的请求是否成功。

## 零零碎碎

### application.properties VS application.yaml

两个都可以写，spring会帮你intergrate到一起。

spring boot用yml，它可以省去很多重复内容。

## 一次重构（multimodule）

2021.10.24

目的：构建multi-module的spring boot application。这样就可以复用entity。参考[官方文档](https://spring.io/guides/gs/multi-module/)

1. 用maven建parent文件夹，然后在里面的`pom.xml`中写`<module>`的tag就行。

2. idea里找到这个项目的project structure中import existing module（导入iml文件即可）或者new module（可以直接spring initializal）。

3. 我就new了一个book entity，然后导入了backend。并修改了它们的pom文件，修改方法参考官方文档即可。使用entity的backend的@SpringBootApplication加了scanbasedir。

   > new和import在idea中的操作参考这了篇[Jetbrain的官方教程](https://www.jetbrains.com/help/idea/creating-and-managing-modules.html)。根据这篇教程，module与是否处于parent目录下没关系。但你可以把外面的项目拖进来。然后我就作死拖了进来，然后一切祥和。甚至不加`@entityScan`都能跑。

4. 然后我又觉得文件夹放在里面有点不太好，又用refacotr把它move了出去，然后诡异的事情就发生了，文件夹里出现两个.iml文件。然后我再试图import module的时候，一个iml文件导入但是不在project（cmd+1）栏里显示，一个导入但是找不到book entity（pom中不报错）。

5. 解决不了，甚至直接run application都会出现找不到类的情况，一怒之下我决定remake。全部重来，反正代码都有，建项目就行了。

6. 踩得到第一个坑：新建项目的时候改了包名——之前import package等等全部不能用了。。。血的教训。。。

7. 然后顺着上面的路又走了一遍。

   > 下面这两个注解也都加上了：
   >
   > @SpringBootApplication(scanBasePackages = "com.windowsxp.bookhub,entity")
   >
   > @EntityScan("com.windowsxp.bookhub.book.entity")

8. 第一个bug——所有@configuration注解都没用了。

   solution：https://blog.csdn.net/a772304419/article/details/79680833

9. 第二个bug——所有Jparepository<1,2>中的1都找不到了。

   solution：把本项目里的entity文件夹也加到@EntityScan里。

10. 第三个bug——所有请求发过来全部返回404 not found。

    [Spring Boot: Cannot access REST Controller on localhost (404)](https://stackoverflow.com/questions/31318107/spring-boot-cannot-access-rest-controller-on-localhost-404)  找不到controller class把scanBasePackage去掉。

    > 9 和 10 的原因：[Spring @EntityScan vs. @ComponentScan](https://www.baeldung.com/spring-entityscan-vs-componentscan)
    >
    > > When writing our Spring application we will usually have entity classes – those annotated with *@Entity* annotation. We can consider two approaches to placing our entity classes:
    > >
    > > - Under the application main package or its sub-packages
    > > - Use a completely different root package
    > >
    > > In the first scenario, we could use *@EnableAutoConfiguration* to enable Spring to auto-configure the application context.
    > >
    > > In the second scenario, we would provide our application with the information where these packages could be found. For this purpose, we would use *@EntityScan.*
    > >
    > > *@EntityScan* annotation is used when entity classes are not placed in the main application package or its sub-packages. In this situation, we would declare the package or list of packages in the main configuration class within *@EntityScan* annotation. This will tell Spring where to find entities used in our application.
    > >
    > > in Chinese: 在自己的文件夹里@EnableAutoConfiguration帮你做了（@SpringBootApplication有这个注解的效果），外面的要EntityScan，结果加了Scan似乎都不行了。。。
    > >
    > > scanBasePackages类似，直接去掉就行了。官方文档里其实也说了
    > >
    > > > If your application also uses JPA or Spring Data, the `@EntityScan` and `@EnableJpaRepositories` (and related) annotations inherit only their base package from `@SpringBootApplication` when not explicitly specified. That is, once you specify `scanBasePackageClasses` or `scanBasePackages`, you might also have to also explicitly use `@EntityScan` and `@EnableJpaRepositories` with their package scans explicitly configured.

11. 重新打开backend_parent后，有可能又找不到外部module的entity了，这时可以点击右侧栏中maven的`reload all maven projects` 再run就可以了。
