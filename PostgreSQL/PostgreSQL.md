# PostgreSQL

安装

## 教程

### 事务

事务将多个步骤捆绑成了一个单一 的、要么**全完成**要么**全不完成**的操作。步骤之间的中间状态对于其他并发事务是不可见的， 并且**如果有某些错误发生导致事务不能完成，则其中任何一个步骤都不会对数据库造成影响**。

保存点允许我们有选择性地放 弃事务的一部分而提交剩下的部分。在使用SAVEPOINT定义一个保存点后，我们可以在必要 时利用ROLLBACK TO回滚到该保存点。该事务中位于保存点和回滚点之间的数据库修改都会 被放弃，但是早于该保存点的修改则会被保存。

### 窗口函数

一个窗口函数执行一种计算，在一系列与当前行有关的表行上执行。

```sql
<窗口函数> over (partition by <用于分组的列名>
                order by <用于排序的列名>)
```

<窗口函数>的位置，可以放以下两种函数：

1） 专用窗口函数，包括后面要讲到的rank, dense_rank, row_number等专用窗口函数。

2） 聚合函数，如sum,avg, count, max, min等。

**窗口函数有以下功能：**

1）同时具有分组和排序的功能

2）不减少原表的行数

### 继承

```sql
CREATE TABLE cities (
 name text,
 population real,
 altitude int -- (in ft)
);

CREATE TABLE capitals (
 state char(2)
) INHERITS (cities);
```

```sql
SELECT name, altitude
 FROM ONLY cities
 WHERE altitude > 500;
```

> name | altitude
>-----------+----------
> Las Vegas | 2174
> Mariposa | 1953

其中cities之前的ONLY用于指示查询只在cities表上进行而不会涉及到继承层次中位 于cities之下的其他表。

## SQL语法

### 词法结构

 关键词和不被引号修饰的标识符是大小写不敏感的。

问题：

```
SELECT 5 ! (- 6);
```

报错：HINT:  No operator matches the given name and argument types. You might need to add explicit type casts.

## 数据定义

### 生成列

### 依赖跟踪



## 查询

**PostgreSQL递归查询**

语法结构

```
with recursive 名字 as (
    A.初始条件语句(非递归部分)
    
    union [all] 
    
    B.递归部分语句
) [SELECT | INSERT | UPDATE | DELETE]
```

1. 前半部分A为初始条件语句，后半部分B为要进行的递归语句
2. 先执行A语句，然后将A语句的结果作为B语句的条件，如果需要对查询结果去重则使用union进行连接，否则使用union all进行连接



