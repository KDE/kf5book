## Adding ThreadWeaver to a project - an introduction to the Frameworks 5 build system

Two standard questions come up when learning a new technology or toolkit as a programmer - how do I use it, and how do I add this module to and deploy it with my project. The answer to the second question requires at least rudimentary knowledge about the build system used, and will be covered in this chapter. While it will use ThreadWeaver to explain the details, the basic workflow presented is generic and could be similarly applied when adding other KDE frameworks. 

KDE frameworks use the CMake build system.[^c] In essence, CMake is a generator of native project build instructions (Makefiles, for example) based on a project build description, the `CMakeLists.txt` file. CMake is rather popular especially for C++ projects, and is used to build all of KDE. It's basic concepts are powerful, expressive and relatively easy to use. Many developers will agree that this is already much to ask of a build system. On top of that, CMake is rather portable and generates build instructions for all relevant target platforms including not just Linux, but also OSX and Windows. This portability supports the goal of KDE and it's frameworks to be available from a single source on as many platforms as possible. In the following steps, the essential bits of the complete CMakeLists.txt file for ThreadWeaver's HelloWorld example are going to be explained. The real world relevance of this  use case is to build an application that uses and links a KDE framework, in this case ThreadWeaver. 

@@snippet(threadweaver/examples/HelloWorld/CMakeLists.txt, adding_tw_1, cpp)

The first two lines define a minimum CMake version and make sure the extra CMake modules (ECM) used by KDE are detected by CMake. These two lines are not necessarily required, but it is a good idea to have them. Specifying a minimum CMake version at the beginning of the file prevents cryptic, hard to understand errors that may be caused by an older installed CMake version trying to parse the file any further. Similarly, ECM would be automatically detected if it is installed, but by explicitly looking for it, a clear error message is triggered if it cannot be found. However these two lines are just in preparation for the next bits that are more specific to the projects.

@@snippet(threadweaver/examples/HelloWorld/CMakeLists.txt, adding_tw_2, cpp)

The `find_package` statement detects the ThreadWeaver include files and libraries and provides them so that they can later be used to build and link concrete targets, like libraries or applications. Because the `find_package` statement marks the framework as required, the statement will fail if ThreadWeaver cannot be detected by CMake. In this case, make sure the framework is properly installed, including the development package that usually contains the header files. On failure to detect ThreadWeaver, CMake will abort and not generate any makefiles. 

@@snippet(threadweaver/examples/HelloWorld/CMakeLists.txt, adding_tw_3, cpp)

The last snippet defines the actual meat of the project. It specifies the project name to be `HelloWorld`, and adds an executable named `ThreadWeaver_HelloWorld` that is build from one source file, `HelloWorld.cpp`. The last line uses the `target_link_libraries` command to specify that to build the `ThreadWeaver_HelloWorld` executable, it should link the ThreadWeaver libraries. The libraries are specified using a scoped named variable, `KF5::ThreadWeaver`. This variable has been defined by the earlier `find_package` command. Every KDE framework defines a named variable like that that should be used to link the respective libraries. 

[^c]: http://www.cmake.org
