# fcntl

## 根据文件描述符来操作文件的状态 -- #include <fcntl.h>

## 函数原型

### int fcntl（int fd, int cmd）；

### int fcntl（int fd, int cmd, long arg）；

### int fcntl（int fd, int cmd, struct flock *lock）；

## 功能

### 复制一个现有的描述符 -- cmd

- F_DUPFD

### 获得／设置文件描述符标记 -- cmd

- F_GETFD
- F_SETFD

### 获得／设置文件状态标记 -- cmd

- F_GETFL

	- 只读打开

		- O_RDONLY

	- 只写打开

		- O_WRONLY

	- 读写打开

		- O_RDWR

	- 执行打开

		- O_EXEC

	- 搜索打开目录

		- O_SEARCH

	- 追加写

		- O_APPEND

	- 非阻塞模式

		- O_NONBLOCK

- F_SETFL

	- 可更改的几个标识

		- O_APPEND
		- O_NONBLOCK

### 获得／设置异步I/O所有权 -- cmd

- F_GETOWN
- F_SETOWN

### 获得／设置记录锁 -- cmd

- F_GETLK
- F_SETLK
- F_SETLKW

*XMind - Trial Version*