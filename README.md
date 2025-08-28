## C++ 现代语法特征训练营

![image-20250825222353105](assets/image-20250825222353105.png)

> 本训练营旨在为你提供现代 C++ 编程的基础入门知识。C++ 语言的特性极为丰富且涉猎广泛，无法在一次训练营中全部涵盖，而且坦白说，这门语言最好通过实践来学习。工作人员相信，15-445 这门课程会让你成为一名更自信的 C++ 程序员！不过，我们确实会涉及一些在完成编程作业时必须掌握的 C++ 知识点。本教程不涵盖基础的 C/C++ 语法，主要介绍 C++ 的编程特性，尤其是那些 C 语言中不存在的概念。

本仓库主要记录个人对该训练营内容的学习过程，并整理原项目代码文件的结构，使得更易于上手和使用；同时对英文注释进行翻译，对暂时具有语言障碍的新手更加友好；最后对部分概念补充了一些简要的笔记，可供有需要的人参考。



## 进度表

| 序号 |             章节              |                             代码                             |                     笔记                     |                           参考资料                           |
| :--: | :---------------------------: | :----------------------------------------------------------: | :------------------------------------------: | :----------------------------------------------------------: |
|  1   | References and Move Semantics | <a href="1 - References and Move Semantics/references.cpp">references.cpp</a> |                     N/A                      | [References](https://en.cppreference.com/w/cpp/language/reference) |
|      |                               | <a href="1 - References and Move Semantics/move_semantics.cpp">move_semantics.cpp</a> |   <a href="notes/移动语义.md">移动语义</a>   | [std::move](https://en.cppreference.com/w/cpp/utility/move)  |
|      |                               | <a href="1 - References and Move Semantics/move_constructors.cpp">move_constructors.cpp</a> | <a href="notes/移动构造器.md">移动构造器</a> | [Move Constructors](https://en.cppreference.com/w/cpp/language/move_constructor) & [Move Assignment Operators](https://en.cppreference.com/w/cpp/language/move_assignment) |
|  2   |         C++ Templates         | <a href="2 - C++ Templates/templated_functions.cpp">templated_functions.cpp</a> |   <a href="notes/模版函数.md">模版函数</a>   | [Templated Functions](https://en.cppreference.com/w/cpp/language/function_template) |



## 构建

该训练营包含若干 C++ 代码文件，位于各章节目录下，建议深入研读。每个代码文件均可编译为与其同名的可执行文件。请使用 CMake 构建这些可执行文件，以下一组命令应能完成所有可执行文件的构建：

```cmake
$ mkdir build
$ cd build
$ cmake ..
$ make -j8
```

执行这些命令后，生成的可执行文件将位于 `build` 目录中。例如， `1 - References and Move Semantics/references.cpp`  文件会编译为 `references` 可执行文件，位于 `./build` 目录下。其余代码文件亦是如此。



## 许可证

1. 本项目基于 <a href="https://github.com/cmu-db/15445-bootcamp">15445-bootcamp</a> 进行翻译和扩展，原项目版权（包括源代码文件）归属 <a href="https://github.com/cmu-db/15445-bootcamp/graphs/contributors">**原作者**</a> 所有，扩充的笔记内容归属本人所有，均遵循  <a href="LICENSE">Apache License 2.0</a> 协议。
2. 本仓库作为个人学习进度的记录，包括相关材料的整理备份、翻译和补充，并对有需要的人提供帮助。

