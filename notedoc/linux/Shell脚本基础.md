# Shell脚本基础

## Linux环境变量

### 全局变量

命令：

```shell
$ printenv | head -n 8
XDG_SESSION_ID=7600
HOSTNAME=iZbp1ajqzkbhcpygosxze8Z
TERM=xterm
SHELL=/bin/bash
HISTSIZE=1000
SSH_CLIENT=182.148.70.155 62386 22
SSH_TTY=/dev/pts/0
USER=vin

$ env | head -n 8
XDG_SESSION_ID=7600
HOSTNAME=iZbp1ajqzkbhcpygosxze8Z
TERM=xterm
SHELL=/bin/bash
HISTSIZE=1000
SSH_CLIENT=182.148.70.155 62386 22
SSH_TTY=/dev/pts/0
USER=vin

```



### 局部变量

命令：

```shell
$ set | head -n 8
BASH=/bin/bash
BASHOPTS=checkwinsize:cmdhist:expand_aliases:extquote:force_fignore:histappend:hostcomplete:interactive_comments:login_shell:progcomp:promptvars:sourcepath
BASH_ALIASES=()
BASH_ARGC=()
BASH_ARGV=()
BASH_CMDS=()
BASH_LINENO=()
BASH_SOURCE=()
```



### 设置全局变量

命令：

```shell
$ export my_variable
```



### 删除环境变量

命令：

```shell
$ unset my_variable
```



### 设置PATH环境变量

PATH环境变量以`:`分隔



## 基础语法

### 命令替换

1. 反引号字符：**`**
2. **$()**格式

```shell
$ echo `pwd`
/home/vin

$ echo $(pwd)
/home/vin

```



### 数学运算

#### 整数运算

1. `expr`

   

2. `$[ operation ]`



#### 浮点数