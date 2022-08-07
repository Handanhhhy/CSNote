# st_mode

## 该变量占 2byte 共 16位

## 掩码的使用：st_mode & 掩码

## 其他人权限
（0-2 bit）

### S_IROTH 00004 读权限

### S_IWOTH 00002 写权限

### S_IXOTH 00001 执行权限

## 所属组权限
（3-5 bit）

### S_IRGRP 00040 读权限

### S_IWGRP 00020 写权限

### S_IXGRP 00010 执行权限

## 文件所有者权限
（6-8 bit）

### S_IRUSR 00400 读权限

### S_IWUSR 00200 写权限

### S_IXUSR 00100 执行权限

## 特殊权限位
（9-11 bit）

### S_ISUID 0004000 设置用户ID

### S_ISGID 0002000 设置组ID

### S_ISVTX 0001000 黏住位

## 文件类型
（12-15 bit）

### S_IFSOCK 0140000 套接字

### S_IFLNK 0120000 符号链接（软链接）

### S_IFREG 0100000 普通文件

### S_IFBLK 0060000 块设备

### S_IFDIR 0040000 目录

### S_IFCHR 0020000 字符设备

### S_IFIFO 0010000 管道

*XMind - Trial Version*