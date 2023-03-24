# Maven

## Basic

一个Maven工程就是由`groupId`，`artifactId`和`version`作为唯一标识，依赖项也通过这三个tag**唯一确定**。在[这里](https://search.maven.org/)搜索第三方组件的这三个值。

在Maven中声明一个依赖项（dependency）可以自动下载并导入classpath。

> - 某个jar包被Maven下载过会缓存在本地。
>
> - 以`-SNAPSHOT`结尾的版本号会被认为是开发版本，每次都会重复下载。
>
> - Maven通过对jar包进行PGP签名确保任何一个jar包一经发布就无法修改。修改已发布jar包的唯一方法是发布一个新版本。
> - 有时候`version`会缺省，很可能是因为`<parent>`中已经指定。

### 依赖管理

我们的项目依赖`abc`这个jar包，而`abc`又依赖`xyz`这个jar包：

```
┌──────────────┐
│ Sample Project│
└──────────────┘
        │
        ▼
┌──────────────┐
│      abc      │
└──────────────┘
        │
        ▼
┌──────────────┐
│      xyz      │
└──────────────┘
```

当我们声明了`abc`的依赖时，Maven自动把`abc`和`xyz`都加入了我们的项目依赖，不需要我们自己去研究`abc`是否需要依赖`xyz`。

#### 关系

> 通过`<scope>`这个tag指定。

|  scope   |                     说明                      |      示例       |
| :------: | :-------------------------------------------: | :-------------: |
| compile  |         编译时需要用到该jar包（默认）         | commons-logging |
|   test   |           编译Test时需要用到该jar包           |      junit      |
| runtime  |        编译时不需要，但运行时需要用到         |      mysql      |
| provided | 编译时需要用到，但运行时由JDK或某个服务器提供 |   servlet-api   |

## 构建流程

### phase

maven的生命周期由一系列phase构成。

e.g. default生命周期包含这些phase：

```
validate
initialize
generate-sources
process-sources
generate-resources
process-resources
compile
process-classes
generate-test-sources
process-test-sources
generate-test-resources
process-test-resources
test-compile
process-test-classes
test
prepare-package
package
pre-integration-test
integration-test
post-integration-test
verify
install
deploy
```

还有`clean`生命周期，包含三个phase：

```
pre-clean
clean
post-clean
```

### goal

一个phase里面又分了一些goal。

#### 插件

执行每个phase，都是通过某个插件（plugin）来执行的，Maven本身其实并不知道如何执行`compile`，它只是负责找到对应的`compiler`插件，然后执行默认的`compiler:compile`这个goal来完成编译。

### CLI

使用mvn命令行命令时，后面的参数是phase。比如：

`mvn package/compile/...` 会执行`default`生命周期到package/compile/... phase

还可以指定多个phase：`mvn clean package`，Maven先执行`clean`生命周期并运行到`clean`这个phase，然后执行`default`生命周期并运行到`package`这个phase。



`mvn release` command will tag your current code in configured SCM (Source Control Management) like SVN, and change the version number in your project's pom.xml.

`mvn deploy` command will put the JAR or WAR file of your project into a remote repository e.g. maven central or your company's nexus repository for sharing with other projects.

`mvn install` command runs the install plugin used in the install phase to add artifact(s) to the local repository. The Install Plugin uses the information in the POM (groupId, artifactId, version) to determine the proper location of the artifact within the local repository.

`mvn clean install`

1. You are using the `clean` command, which will delete all previously compiled Java .class files and resources (like .properties) in your project. Your build will start from a clean slate.

2. `Install` will then compile, test & package your Java project and even *install*/copy your built .jar/.war file into your local Maven repository.

By default, it is located in the user's home directory (~/.m2/repository) but the location can be configured in ~/.m2/settings.xml using the `<localRepository>` element.
