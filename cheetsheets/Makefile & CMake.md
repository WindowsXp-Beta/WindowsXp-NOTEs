# Makefile

> ref: [跟我一起写Makefile](https://seisman.github.io/how-to-write-makefile)

`?=`: set a variable only if it's not set/doesn't have a value 

## 显示规则

```makefile
target ... : prerequisites ...
    command
```

target: 目标文件（重定位目标文件 or 可执行目标文件）

prerequisties: 该target依赖的文件或target

command: 改target要执行的命令（任意shell命令）

## 工作流程

1. 找到文件中第一个target，作为最终的目标文件。

2. if 如果该文件不存在 or 依赖的文件修改时间比改文件新: 执行command来生成这个文件

3. if 依赖的文件也不存在: 在当前Makefile中寻找这个target并执行（如果也找不到以此类推）

    > 我觉得这里不太准确，即使依赖的target存在，也会去看一下它的prerequisite是否有更新

## 变量

定义: `objects = main.o kbd.o`

使用: `$(objects)`

## 隐晦规则

看到一个这样的target `whatever.o`  make会自动把`whatever.c`加入prerequisite，并且推导出command为`cc -c whatever.c`

## 文件

### Makefile文件

--file, -f specify which makefile to use

`include <filename>`

> e.g. include foo.make *.mk $(bar)

### 搜寻依赖文件

大项目中源文件会被放到多个目录里，可以通过`VPATH`告诉makefile还有哪些路径去寻找文件。

`VPATH = src:../include` 多个目录间通过冒号分隔

# CMake

> ref: [CMake official tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html#guide:CMake%20Tutorial)  [Modern CMake by example by RC](https://github.com/richardchien/modern-cmake-by-example)

## Basic

```cmake
cmake_minimum_required(VERSION 3.9) # specify a minimum CMake version
project(answer) # project's name

add_executable(answer main.cpp answer.cpp)

add_subdirectory(MathFunctions) # MathFunctions中也可以使用根目录下的library，include之类的

set(CMAKE_CXX_STANDARD 11) # set CMAKE_CXX_STANDARD variable to state the correct flag
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(TutorialConfig.h.in TutorialConfig.h) # copy a file to another location and modify its contents
```

### attention

- configure_file会替换input中的`@VAR@` or `${VAR}`。如果cmake没有定义这个变量，就是empty string。

- add_subdirectory中的CMakeLists可以链接同一项目中其它子目录中定义的library
- 可以使用`target_compile_features(libanswer INTERFACE cxx_std_20)`提供更细粒度的编译控制，set C++11是全局的



### 变量

#### scope

- function scope

    函数中的set只在当前function call和nested call中存在

- directory scope

    每一个不在function中的set/unset都属于当前directory scope

- persistent scope

    set/unset using CACHE option

#### set

`set(WOLFRAM_APPID "" CACHE STRING "WolframAlpha APPID")`

变量名 初始值 cache变量 类型 描述

#### cache

私密的 App ID、API Key 等不应该直接放在代码里，应该做成可配置的项，从外部传入。除此之外还可通过可配置的变量来控制程序的特性、行为等。在 CMake 中，通过 cache 变量实现。

对于上面set中定义的WOLFRAM_APPID，可以在调用cmake时传入`cmake -B build -DWOLFRAM_APPID=xxx`

也可以使用ccmake在TUI中修改

bool类型也可以使用option`option(USE_MYMATH "Use tutorial provided math implementation" ON)`

然后使用`target_compile_definitions(libanswer PRIVATE WOLFRAM_APPID="${WOLFRAM_APPID}")`传递给源代码

#### 内置

[official doc](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html#variables-that-provide-information)

begin with `CMAKE_`, `_CMAKE_`, `_` followed by the name of any CMake Command

- PROJECT_SOURCE_DIR vs CMAKE_CURRENT_SOURCE_DIR
- PROJECT_BINARY_DIR vs CMAKE_CURRENT_BINARY_DIR

#### 使用

`"${var}/other_stuff"`

##### 打印

```cmake
message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}") # don't use white spaces since they would be emitted
```

## Library

```cmake
# object library
add_library(library_name [STATIC | SHARED | MODULE] [<source>])
target_link_libraries(<target>
					  <PRIVATE|PUBLIC|INTERFACE>
					  <item>...) # <item>: library
target_include_directories(<target>
						   <PRIVATE|PUBLIC|INTERFACE>
						   <item>...) # <item>: path, and you can include multiple paths
```

### scope

| Include Inheritance |                         Description                          |
| :-----------------: | :----------------------------------------------------------: |
|      `PUBLIC`       | All the directories following `PUBLIC` will be used for the current target and the other targets that have dependencies on the current target, i.e., appending the directories to `INCLUDE_DIRECTORIES` and `INTERFACE_INCLUDE_DIRECTORIES`. |
|      `PRIVATE`      | All the include directories following `PRIVATE` will be used for the current target only, i.e., appending the directories to `INCLUDE_DIRECTORIES`. |
|     `INTERFACE`     | All the include directories following `INTERFACE` will NOT be used for the current target but will be accessible for the other targets that have dependencies on the current target, i.e., appending the directories to `INTERFACE_INCLUDE_DIRECTORIES`. |

INTERFACE_INCLUDE_DIRECTORIES就是链接这个库的文件也可以`#include`其中的头文件

### interface lib

```cmake
# interface library
add_library(<name> INTERFACE)
```

可以用来指定一些编译要求(compile feature, compile option, etc.)，然后将此lib链接到其他库

## gen exp

[conditional expressions](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html?highlight=compile_lang_and_id#conditional-expressions)

- `$<condition:true_string>`
- `$<IF:condition,true_string,false_string>`

### example

```cmake
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
# equal to $<COMPILE_LANGUAGE:language> and $<LANG_COMPILER_ID:compiler_ids>
# you can check your COMPILER_ID in CMAKE_CXX_COMPILER_ID
target_compile_options(tutorial_compiler_flags INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
```

explain：先最里面那层，[$<BUILD_INTERFACE>](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html?highlight=compile_lang_and_id#genex:BUILD_INTERFACE) 只在当前target被同一个buildsystem中的另一个target使用时返回冒号后面的内容

然后`${gcc_like_cxx}:`，这里使用一个0 or 1的变量，变量的值由之前的set指定。如果1，返回后面的内容

## vscode

### config

[official doc](https://github.com/microsoft/vscode-cmake-tools/blob/main/docs/cmake-settings.md#cmake-settings)

#### sourceDirectory

如果CMakeList.txt不在workspaceFolder下，需要设置`cmake.sourceDirectory`，也可以顺便设置下`cmake.buildDirectory`。

命令中输入`CMake: Configure`即会弹出一个对话框可以选择root CMakeList。

📢：刚设置完之后有可能不生效（具体表现为CMake的输出卡在Configuring ...那），需要重启一下vscode，然后去settings.json按一下保存，CMake正常输出即可。

### variant

左下角第一栏可以指定优化等级，包括

1. Release: `-O3 -DNDEBUG`
2. Debug: `-O0 -g`
3. RelWithDebInfo: `-O2 -g -DNDEBUG`
4. MinSizeRel: `-Os -DNDEBUG`

### debug launch

1. 输入lldb然后载入一个模板

    ```
    {
        "name": "(lldb) 启动",
        "type": "cppdbg",
        "request": "launch",
        "program": "输入程序名称，例如 ${workspaceFolder}/a.out",
        "args": [],
        "stopAtEntry": false,
        "cwd": "${fileDirname}",
        "environment": [],
        "externalConsole": false,
        "MIMode": "lldb"
    }
    ```

2. 修改program，使用cmake的command: `${command:cmake.launchTargetPath}`

    这里的launchTarget在最下面的任务栏里选
