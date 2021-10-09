# Ultra Multi-Thread

This project aims to facilitate and modularize multithreaded programming by naming shared objects. At the same time, it provides various common multi-thread synchronization functions, and re-packages the standard library. The code is header only, but it will rely on some third-party libraries as auxiliary functions.

本项目旨在通过命名共享对象的方式，便捷化和模块化多线程编程。同时提供各类常用多线程同步功能，对标准库进行二次封装。代码 header only ，但会依赖部分第三方库作为辅助功能。

------

Several pain points for multi-threaded programming:

-   Shared data directly uses global variables: the code does not have a good modular structure, and the file dependencies are complicated.
-   Shared data uses dynamic allocation of objects on the heap: shared_ptr is passed layer by layer in each function, and the code structure is easy to be confused.
-   The standard library has only lower-level thread synchronization libraries: commonly used high-level synchronization methods always have to make wheels.

针对多线程编程的几个痛点：

-   共享数据直接使用全局变量：代码不具有良好的模块化结构，文件依赖关系繁杂。
-   共享数据使用堆上动态分配对象： shared_ptr 在各个函数中层层传递，代码结构容易混乱。
-   标准库只有较底层的线程同步库：常用的高级同步方式总是要造轮子。

Using the method of naming shared objects eliminates the need for layer-by-layer transmission of shared_ptr, and at the same time, it does not rely on complicated code like directly using global objects. Name the shared object, uniquely identify a shared object through the object type and object name, and find the corresponding shared object through the string hash table.

使用命名共享对象的方式，省去 shared_ptr 的层层传递，同时不会像直接使用全局对象那样是的代码依赖繁杂。命名共享对象，通过对象类型和对象名称唯一确定一个共享对象，通过字符串哈希表来寻找对应的共享对象。

------

Commonly used multi-thread synchronization functions:

-   Publish and subscribe mode
-   Thread conditional sleep and wake up

常用多线程同步功能：

-   发布订阅模式
-   线程条件休眠与唤醒

------

The actual project folder is UltraMultiThread, and the rest of the files are sample files, which provide a way to build a project. The main functions and functions can be viewed in the sample project. Here is the file structure, which is also the project template structure:

实际项目文件夹是 UltraMultiThread ，其余文件都是示例文件，它们提供了一种搭建项目的思路。主要功能和函数的使用可以查看示例项目，这里给出文件结构，也是项目模版结构：

```shell
.
├── CMakeLists.txt  # Project CMake configuration/项目 CMake 配置
├── init.sh  # Empty the example, leaving the frame/清空示例，留下框架
├── main.cpp  # The main cpp file, only used to run the python terminal, do not write your code here/主 cpp 文件，仅用于运行 python 终端，不要放入任务
├── scripts  # Python script storage directory/python 脚本存放目录
│   ├── app.py  # The main python script, used to call other python scripts without modification/主 python 脚本，用于调用其他 python 脚本，无需修改
│   ├── background_run.py  # Start c++ thread task/启动 c++ 线程任务
│   └── workers.py  # python task programming/python 任务编程
├── startup.sh  # Sample run script/示例运行脚本
├── UltraMultiThread  # Project directory/项目目录
│   ├── CMakeLists.txt  # Project CMake/项目 CMake
│   └── include
│       └── umt
│           ├── Message.hpp  # P-S/通信类
│           ├── ObjManager.hpp  # Shared variable/共享变量类
│           └── umt.hpp
└── workers.cpp  # c++ task/c++ 任务
```

We recommend using python scripts to start threads in c++ in the way of task enablement, so that you can selectively open c++ tasks.

我们推荐使用 python 脚本以任务启用的方式开启 c++ 中的线程，这样可以选择性打开 c++ 任务。

For users who are not familiar with using it, we provide C++ and Python templates:

对于不熟悉使用的用户，我们提供 C++ 和 Python 模版：

C++：

```c++
#include <umt/umt.hpp>
#include <thread>

// define your class here

// end code

void function() {
    // define a publisher or subscriber

    while(true) {
        // push the data after calculation or receive the data which you needed
        // for subscriber, don't forget the try-catch block
    }
}


// background wrapper
// don't forget to start your thread in python task
void background_run*() {
    std::thread(function).detach();
}


UMT_EXPORT_MESSAGE_ALIAS(MSG, MSG, c){}  // export your class

UMT_EXPORT_MESSAGE_ALIAS_WITHOUT_TYPE_EXPORT(int, int, c);  // export basic type

UMT_EXPORT_OBJMANAGER_ALIAS(foo, foo, c) {}  // export shared variable

PYBIND11_EMBEDDED_MODULE(Workers, m) {}  // export the module
```

Python：

```python
import threading
import Message_<>  # import the wrapped class you defined in c++
from Message_MSG import MSG  # import your class


def function():
    # define a publisher or subscriber

    while True:
        # push the data after calculation or receive the data which you needed
        # for subscriber, don't forget the try-except block


threading.Thread(target=function, daemon=True).start()  # start your thread
```



## TODO

1.   自动注册类中成员变量和成员函数机制
2.   c++有线程自动不退出机制
3.   pop 返回成功与否，不会报错退出
4.   只导出P/S而不指定数据类型，解决途径：动态多态或std::any
5.   c++/python输出冲突，解决途径：多进程或统一LOGGER-syncstream



## Update log

2021-10-09: Solve the deadlock problem of python basic types, commit: 7b080b

2021-10-09：解决 python 基本类型死锁问题，commit：7b080b





If this project is useful to you, you can order a Star! Thank you~

如果本项目对你有用的话可以点个 Star ！谢谢～

----

作者：

-   Harry-hhj，GitHub主页：[传送门](https://github.com/Harry-hhj)
-   xinyang-go，GitHub主页：[传送门](https://github.com/xinyang-go)

