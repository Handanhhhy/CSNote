# 基于对象设计

## 数据与函数



## 头文件

### 引用

```c++
C1. #include <xxx>
2. #include "xxx"
```

### 防卫式声明(guard)

第一次引入时，未定义过OOP则会引入，第二次引入已经引入过了，则防止再次引入。

```c++
#ifndef __OOP__
#define __OOp__

/*
 * code
 */

#endif
```

### Header布局

<img src="D:\wordspace\CSNotebook\C++\C++面向对象高级编程\image-20220514135701943.png" alt="image-20220514135701943" style="zoom:50%;" />

## 类声明



## 模板

### 类模板

```c++
template<typename T>
```

会照成代码膨胀，但是时必要的。因为需要使用对应的数据类型去生成代码。 

![image-20220515105024748](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515105024748.png)

### 函数模板

```c++
template<class T>
```

![image-20220515105038050](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515105038050.png)



## 命名空间namespace

![image-20220515105249448](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515105249448.png)



## inline函数(内联)



## 访问级别

所有的数据都应该在private中。

## 构造函数

特点：函数名称与类相同、无返回类型、初始化列表。

初始化列表比在代码块中赋值效率高。



## 常量成员函数

在函数后加上const。

特点：

1. 只能读取成员变量的值，而不能修改成员变量的值。
2. 不能调用该类中其他未使用const修饰的函数。
3. 可以被类中的其他函数调用。 
4. 常对象只能调用常成员函数。

## 引用

### 参数传递：值、引用

![image-20220514144304616](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514144304616.png)

可以的条件下，尽量传引用。不想改变值时，传递const引用。

### 返回值传递：值、引用

可以的条件下，尽量传引用。不想改变值时，传递const引用。

![image-20220514144812308](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514144812308.png)

不能传引用的情况：

返回的是局部变量，局部变量在返回时会被销毁。

## 友元

![image-20220514144835313](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514144835313.png)

![image-20220514144855980](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514144855980.png)





## 编码的关注点

1. 数据放在private里面
2. 参数尽量以reference传
3. 返回值尽量以reference传
4. 该加const的要加
5. 使用初始化列表



## 操作符重载

操作符重载可以写成成员函数，和非成员函数。

C++中的操作符都是作用于左值。因此输入输出操作符重载不能写为成员函数。

![image-20220514170433646](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514170433646.png)

重载的时候要考虑该操作符是否会被连续使用。

```
cout << "xxx" << "yyy";
a+=b+=c;
```

![image-20220514154636092](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514154636092.png)



## 临时对象

typename ();

![image-20220514152818867](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514152818867.png)



## 拷贝构造、拷贝赋值、析构

涉及到指针的函数，需要重写。

1. 拷贝构造：构造函数中传入参数为自己类。
2. 拷贝赋值：操作符传入参数为自己类。
3. 析构：销毁时释放内存。

![image-20220514171629442](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514171629442.png)

![image-20220514172754037](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514172754037.png)

![image-20220514172807411](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514172807411.png)

从来源端拷贝到目的端：

1. 检查是否自我复制
2. 检查目的端内容是否释放
3. 返回值，考虑操作符是否会被连续调用（ob1=ob2=ob3）



## 静态static

![image-20220515102421429](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515102421429.png)

静态数据在类外初始化。

![image-20220515102547740](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515102547740.png)

对象调用静态函数时，不会传入this。因为静态时独立于对象的，属于类。

![image-20220515103540269](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515103540269.png)

![image-20220515103640707](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515103640707.png)

static离开了函数也存在。



## 堆、栈、内存管理

![image-20220514173931276](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514173931276.png)

![image-20220514174103342](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220514174103342.png)

### 构造函数和析构函数

array new 要搭配array delete



# 面向对象设计

## 复合composition

![image-20220515105803735](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515105803735.png)

queue中有个deque。

![image-20220515110248061](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515110248061.png)

红色部分时编译器添加上的。

## 委托delegation

![image-20220515110720931](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515110720931.png)

使用指针指向。右边可以随便更改，但左边不用变。 



## 继承inheritance

![image-20220515171354371](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515171354371.png)

基类的析构函数必须是virtual。  

![image-20220515131957272](D:\wordspace\CSNotebook\C++\C++面向对象高级编程-image\image-20220515131957272.png)

纯虚函数子类一定要重写。

```c++
#include <iostream>

using namespace std;

class Base {
public:
    Base() {
        cout << "base()" << endl;
    }

};

class Component {
public:
    Component() {
        cout << "Component()" << endl;
    }
};

class Derived : public Base {
public:
    Derived() {
        cout << "Derived()" << endl;
    }

protected:
    Component cmp;
};

int main() {
    Derived der;
    return 0;
}
```

输出：说明先够着基类，再构造Component。

>base()
>Component()
>Derived()