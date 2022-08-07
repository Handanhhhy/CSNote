# Vscode配置C++环境

## 安装IED及编译器

1. 安装VSCode
2. 下载[MinGW](https://sourceforge.net/projects/mingw-w64/files/),最新版：x86_64-8.1.0-release-posix-seh-rt_v6-rev0

  POSIX线程（POSIX threads），简称Pthreads，是线程的POSIX标准。该标准定义了创建和操纵线程的一整套API。在类Unix操作系统（Unix、Linux、Mac OS X等）中，都使用Pthreads作为操作系统的线程。Windows操作系统也有其移植版pthreads-win32。

3. 将MinGW/bin添加到环境变量,重启Vscode

   > D:\CodeSoft\VSCode\vsc++\x86_64-8.1.0\mingw64\bin

## 配置环境

### 方法1

1. 安装Code Runner。(相应语言的编译器或者解释器还是需要自行安装的，并且把路径添加到PATH里,上面已经安装过，这里只是解释一下不可以不安装编译器)

   >Code Runner快捷键：
   >
   >运行：Ctrl+Alt+N
   >
   >停止：Ctrl+Alt+M
   >
   >F1：命令面板
   >
   >Run in Terminal：Run Code configuration -> √ Run In Terminal
   >
   > Save File Before Run：Run Code configuration -> √  Save File Before Run

   注：目前没找到调试方法

### 方法2

修改配置文件

1. C++ Edit Configuration(UI):编译器路径:D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin/gcc

   IntelliSense:gcc-x64或default

2. launch.josn

   ```json
   "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",//配置程序名称
   "preLaunchTask": "task g++" ,//配置任务
   "miDebuggerPath": ":D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin/gdb",//配置debug使用的gdb路径
   ```

   ```json
   {
       // 使用 IntelliSense 了解相关属性。 
       // 悬停以查看现有属性的描述。
       "version": "0.2.0",
       "configurations": [
           {
               "name": "(gdb) 启动",
               "type": "cppdbg",
               "request": "launch",
               "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
               "args": [],
               "stopAtEntry": false,
               "cwd": "${fileDirname}",
               "environment": [],
               "externalConsole": false,
               "MIMode": "gdb",
               "miDebuggerPath": ":D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0-release-posix-seh-rt_v6-rev0/mingw64/bin/gdb.exe",
               "setupCommands": [
                   {
                       "description": "为 gdb 启用整齐打印",
                       "text": "-enable-pretty-printing",
                       "ignoreFailures": true
                   }
               ],
               "preLaunchTask": "task g++"
           }
       ]
   }
   ```

   

3. F5调试源文件，选择创建任务，在选择使用模板创建tasks.json

   ```json
   {
       // See https://go.microsoft.com/fwlink/?LinkId=733558
       // for the documentation about the tasks.json format
       "version": "2.0.0",
       "tasks": [
           {
               "label": "task g++",//与json中preLaunchTask一致
               "type": "shell",
               "command": "D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0/mingw64/bin/g++.exe",
               "args": ["-g", "${file}", "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe"],
               "group": {
                 "kind": "build",
                 "isDefault": true
               }
             }
       ]
   }
   ```

   注：Vscode不支持路径中有中文，Code Runner可以解决这个问题



## 文件

### c_cpp_properties.json

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:\\CodeSoft\\VSCode\\vsc++\\x86_64-8.1.0\\mingw64\\bin\\gcc.exe",
            "cStandard": "gnu17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```

如果c++编译其未加入系统变量,就需要添加include

```json
{
    "configurations": [
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "D:/softsapce/programming/Vscode/x86_64-8.1.0/mingw64/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "compilerPath": "D:\\softsapce\\programming\\Vscode\\x86_64-8.1.0\\mingw64\\bin\\gcc.exe",
            "cStandard": "gnu17",
            "cppStandard": "gnu++14",
            "intelliSenseMode": "windows-gcc-x64"
        }
    ],
    "version": 4
}
```





### launch.json

```json
{
    // 使用 IntelliSense 了解相关属性。 
    // 悬停以查看现有属性的描述。
    // 欲了解更多信息，请访问: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "(gdb) 启动",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}\\${fileBasenameNoExtension}.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": true,
            "MIMode": "gdb",
            "miDebuggerPath": "D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0/mingw64/bin/gdb.exe",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "task g++"
        }
    ]
}
```

### task.json

```json
{
    // See https://go.microsoft.com/fwlink/?LinkId=733558
    // for the documentation about the tasks.json format
    "version": "2.0.0",
    "tasks": [
        {
            "label": "task g++",
            "type": "shell",
            "command": "D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0/mingw64/bin/g++.exe",
            "args": ["-g", "${file}", "-o", "${fileDirname}\\${fileBasenameNoExtension}.exe"],
            "group": {
              "kind": "build",
              "isDefault": true
            },
            "options": {
              "cwd": "D:/CodeSoft/VSCode/vsc++/x86_64-8.1.0/mingw64/bin"
            },
            "problemMatcher":"$gcc"
          }
    ]
}
```

