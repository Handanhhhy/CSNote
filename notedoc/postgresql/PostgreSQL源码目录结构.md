### PostgreSQL源码结构

#### 安装

执行配置

```shell
$ sudo ./configure --prefix='/home/postgres/postgresql/pgsql' --enable-debug --enable-cassert CPPFLAGS='-O0'
```

编译安装

```shell
$ make clean //清除之前编译的文件
$ make //编译
$ make install //安装
```

> make是轻量化安装编译 make all是全部安装编译



#### 日志配置

在`data`目录中，编辑`postgresql.conf`

```
logging_collector = on #开启日志
log_directory = 'log' 
log_filename = 'postgresql-%Y-%m-%d_%H%M%S.log'
log_file_mode = 0600    # creation mode for log files
log_truncate_on_rotation = off 
log_rotation_age = 1d
log_rotation_size = 10MB

log_min_messages = info 
#log_min_duration_statement = -1        # -1 is disabled, 0 logs all statements
log_min_duration_statement = 60 # -1 is disabled, 0 logs all statements

debug_pretty_print = on

log_statement = 'all'

log_timezone = 'Asia/Shanghai'

```

更改配置后若报错(如下)，应该是需要启动了数据库然后才能重新启动

>pg_ctl: PID file "../data/postmaster.pid" does not exist
>Is server running?
>trying to start server anyway
>waiting for server to start.... stopped waiting
>pg_ctl: could not start server
>Examine the log output.

> pg_ctl: PID file "../data/postmaster.pid" does not exist
> Is server running?
> trying to start server anyway
> pg_ctl: could not read file "../data/postmaster.opts"

使用方法

```c
#include "nodes/print.h"

elog(WARNING, "leaked override search path");
elog_node_display(15, "parse tree", qry,Debug_pretty_print)
```

