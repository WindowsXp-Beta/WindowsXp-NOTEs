# docker

> tutorial: [container-learning-path](https://iximiuz.com/en/posts/container-learning-path/)

## docker image

[docker image ref](http://c.biancheng.net/view/3143.html)

1. 镜像内部是一个精简的操作系统（不包含内核——容器都是共享所在 Docker 主机的内核。所以有时会说容器仅包含必要的操作系统（通常只有操作系统文件和文件系统对象）），同时还包含应用运行所必须的文件和依赖包。

   > Ubuntu 官方的 Docker 镜像大约有 110MB

2. 从一个镜像可以启动多个容器，并且在镜像上启动的容器全部停止之前，镜像是无法被删除的。

3. Docker 镜像由一些松耦合的只读镜像层组成。

   <img src="http://c.biancheng.net/uploads/allimg/190416/4-1Z416163955K0.gif" style="zoom:50%;" />

   > 可以通过docker image inspect查看image具体分层

   所有的docker镜像都起始于一个基础镜像层，当进行修改或增加新的内容时，就会在当前镜像层之上，创建新的镜像层。

   e.g. 基于Ubuntu 16.04构建一个新镜像，并添加Python，然后添加一个安全补丁。

   <img src="http://c.biancheng.net/uploads/allimg/190416/4-1Z416164115364.gif" style="zoom:70%;" />

   **在添加额外的镜像层的同时，镜像始终保持是当前所有镜像的组合**

   | <img src="http://c.biancheng.net/uploads/allimg/190416/4-1Z41616413R94.gif" style="zoom:70%;" /> | <img src="http://c.biancheng.net/uploads/allimg/190416/4-1Z416164203H1.gif" style="zoom:50%;" /> |
   | ------------------------------------------------------------ | ------------------------------------------------------------ |
   | 每个镜像层包含 3 个文件，而镜像包含了来自两个镜像层的 6 个文件。 | 在外部看来整个镜像只有 6 个文件，这是因为最上层中的文件 7 是文件 5 的一个更新版本。 |

   多个镜像之间可以并且确实会共享镜像层。这样可以有效节省空间并提升性能。

   > of course, 如果某个镜像层被多个镜像共享，那只有当全部依赖该镜像层的镜像都被删除后，该镜像层才会被删除。

   其实**镜像本身就是一个配置对象**，其中包含了镜像层的列表以及一些元数据信息。**镜像层才是实际数据存储的地方**（比如文件等，镜像层之间是完全独立的，并没有从属于某个镜像集合的概念）。

## Dockerfile

FROM 指令用于指定要构建的镜像的基础镜像。它通常是 Dockerfile 中的第一条指令。

RUN 指令用于在镜像中执行命令，这会创建新的镜像层。每个 RUN 指令创建一个新的镜像层。

COPY 指令用于将文件作为一个新的层添加到镜像中。通常使用 COPY 指令将应用代码赋值到镜像中。

EXPOSE 指令用于记录应用所使用的网络端口。

ENTRYPOINT 指令用于指定镜像以容器方式启动后默认运行的程序。

CMD ["executable","param1","param2"]  执行命令

> Also：`CMD command param1 param2` (*shell* form)

**The main purpose of a `CMD` is to provide defaults for an executing container.**

## manipulate

> Many thanks to [Gun9niR's blog](https://gun9nir.me/posts/docker-bookstore-21-11-30/)

### basic

1. 换源：直接在docker desktop修改配置即可

   https://blog.csdn.net/luqiang81191293/article/details/107043249

#### docker Cli

[docker ps](https://docs.docker.com/engine/reference/commandline/ps/)	list all containers(container id, image, command, ...)

[docker exec](https://docs.docker.com/engine/reference/commandline/exec/)	Run a command in a running container   **you may refer to `tldr` for common usage**

From 1.13 docker has a Cli restructured which adds a command subcommand form.[official blog](https://www.docker.com/blog/whats-new-in-docker-1-13/#h.yuluxi90h1om)

- docker run => docker container run

### multiple-container app

> using docker-compose
>
> [ref-link](https://docs.docker.com/compose/networking/)

使用docker-compose时，在docker-compose.yaml文件中

> [compose file format](https://github.com/compose-spec/compose-spec/blob/master/spec.md)

compose会建立一个network，然后将每个container加入这个network

*discoverable* by them at a hostname identical to the container name.

```yaml
version: "3.9"
services:
  web:
    build: .
    ports:
      - "8000:8000"
  db:
    image: postgres
    container_name:
    ports:
      - "8001:5432"
```

container可以通过hostname `web` or `db` （也就是container name） 加 **container port**，访问web或db，比如`postgres://db:5432`，在host machine上可以通过 `postgres://{DOCKER_IP}:8001`访问，本地的docker ip就是localhost。

因此我们要将application.properties中的数据库localhost全部替换成container name。

> 但在docker desktop里查看container name并不是db或者web（比如bookhub_bookhub-1_1），使用这个也可以访问。
>
> 也可以通过yaml文件中的container_name项配置container name。

FINALLY: `docker compose up -d`

`up`: Create and start containers

`-d`: run containers in detach mode(run in the background)

### build image

#### Traditional Docker Builds

using dockerfile, remain to explore

#### using maven plugin

`spring-boot:build-image -Dmaven.test.skip=true -f pom.xml`

using -Dmaven.test.skip=true to skip tests

运行结束后就可以在docker dashboard的image中看到，一般它会带上tag，所以在yaml或者docker run命令中使用image:tag（backend:0.0.1-SNAPSHOT）。

### bug report

1. 后端container启动时报错：

   failed to launch: exec.d: failed to execute exec.d file at path '/layers/paketo-buildpacks_bellsoft-liberica/helper/exec.d/memory-calculator': exit status 1 unable to calculate memory configuration

   > [How to solve Memory issues with Paketo buildpack used to build a spring-boot app?](https://stackoverflow.com/questions/67593945/how-to-solve-memory-issues-with-paketo-buildpack-used-to-build-a-spring-boot-app) 这个帖子提供了一些相关信息，比如告诉你这个报错都是啥意思，比如什么什么需要多少内存。

   **Sol**：在docker设置中的resource中把内存从2G开到4G。。。

   这提示我们当有一个问题网上找不到什么solution时，很可能这个问题非常简单以至于只要根据报错信息用直觉干点事情就行了。。。