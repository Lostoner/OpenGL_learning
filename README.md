# OpenGL_learning
 A little application for OpenGL learning.

本项目基于OpenGL开发，且已编译的可执行文件可在src文件夹中找到（release.exe）。
由于本项目仅仅是演示demo，并未编写对资源文件的查找，故相对路径的依赖是必须的，还请注意文件位置的相对不变是本程序正确运行的基础。
本项目需要以下动态链接库才可运行：
    vcruntime140d.dll
    opengl32.dll
    gdi32.dll
    imm32.dll
    kernel32.dll
    msvcp140d.dll
    shell32.dll
    ucrtbased.dll
    user32.dll
已经包含在项目文件Dependences\dll中，将其复制到C:\Windows\SysWOW64下即可。

本项目运行后，使用w、a、s、d、Shift、Ctrl进行摄像机移动，F2释放光标可在左上角UI处进行光照参数调整，ESC退出。
