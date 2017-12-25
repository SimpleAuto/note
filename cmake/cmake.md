# __cmake 使用说明__

##  ***eg: ~/cmake_test/backup/ti***

### PROJECT 指令的语法是：

#### PROJECT(projectname [CXX] [C] [Java])
你可以用这个指令定义工程名称，并可指定工程支持的语言，支持的语言列表是可以忽略的，
默认情况表示支持所有语言。这个指令隐式的定义了两个 cmake 变量:

&lt;projectname&gt;_BINARY_DIR 以及&lt;projectname&gt;_SOURCE_DIR，这里就是HELLO_BINARY_DIR 和 HELLO_SOURCE_DIR(所以 CMakeLists.txt 中两个 MESSAGE指令可以直接使用了这两个变量)，因为采用的是内部编译，两个变量目前指的都是工程所在路径/backup/cmake/t1，后面我们会讲到外部编译，两者所指代的内容会有所不同。同时 cmake 系统也帮助我们预定义了 PROJECT_BINARY_DIR 和 PROJECT_SOURCE_DIR变量，他们的值分别跟 HELLO_BINARY_DIR 与 HELLO_SOURCE_DIR 一致。为了统一起见，建议以后直接使用 PROJECT_BINARY_DIR，PROJECT_SOURCE_DIR，即使修改了工程名称，也不会影响这两个变量。如果使用了&lt;projectname&gt;_SOURCE_DIR，修改工程名称后，需要同时修改这些变量。

#### SET 指令的语法是：
SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
现阶段，你只需要了解 SET 指令可以用来显式的定义变量即可。
比如我们用到的是 SET(SRC_LIST main.c)，如果有多个源文件，也可以定义成：
SET(SRC_LIST main.c t1.c t2.c)。

#### MESSAGE 指令的语法是：
MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR] "message to display"
...)
这个指令用于向终端输出用户定义的信息，包含了三种类型:
SEND_ERROR，产生错误，生成过程被跳过。
SATUS，输出前缀为—的信息。
FATAL_ERROR，立即终止所有 cmake 过程.

#### ADD_EXECUTABLE(hello ${SRC_LIST})
定义了这个工程会生成一个文件名为 hello 的可执行文件，相关的源文件是 SRC_LIST 中
定义的源文件列表

#### 基本语法规则
前面提到过，cmake 其实仍然要使用”cmake 语言和语法”去构建，上面的内容就是所谓的
”cmake 语言和语法”，最简单的语法规则是：
1，变量使用${}方式取值，但是在 IF 控制语句中是直接使用变量名
2，指令(参数 1 参数 2...)参数使用括弧括起，参数之间使用空格或分号分开。
以上面的 ADD_EXECUTABLE 指令为例，如果存在另外一个 func.c 源文件，就要写成：
ADD_EXECUTABLE(hello main.c func.c)或者
ADD_EXECUTABLE(hello main.c;func.c)
3，指令是大小写无关的，参数和变量是大小写相关的。但，推荐你全部使用大写指令。
