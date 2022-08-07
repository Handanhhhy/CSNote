### 创建项目

>```text
>django-admin startproject project_name
>eg:django-admin startproject mysite
>
>mysite/ #项目的容器
>    manage.py #各种方式管理 Django 项目的命令行工具
>    mysite/
>        __init__.py #一个空文件，告诉 Python 这个目录应该被认为是一个 Python 包
>        settings.py #Django 项目的配置文件
>        urls.py #Django 项目的 URL 声明，就像你网站的“目录”
>        asgi.py #作为你的项目的运行在 ASGI 兼容的 Web 服务器上的入口
>        wsgi.py #作为你的项目的运行在 WSGI 兼容的
>        Web服务器上的入口
>```



### 用于开发的简易服务器

> python manage.py runserver

### 创建应用

> python manage.py startapp dir_name

### 视图和URL配置

#### 视图

一个视图就是Python的一个函数。这个函数第一个参数的类型是HttpRequest；它返回一个HttpResponse实例。为了使一个Python的函数成为一个Django可识别的视图，它必须满足这两个条件。（也有例外）

#### URLconf

*URLconf* 就像是 Django 所支撑网站的目录。 它的本质是 URL 模式以及要为该 URL 模式调用的视图函数之间的映射表。 你就是以这种方式告诉 Django，对于这个 URL 调用这段代码，对于那个 URL 调用那段代码。

#### URL模式

URL模式要求尾部有一个斜杠(/)， 然而，默认地，任何不匹配或尾部没有斜杠(/)的申请URL，将被重定向至尾部包含斜杠的相同字眼的URL。 （这是受配置文件setting中APPEND_SLASH项控制的）

如果你是喜欢所有URL都以’/’结尾的人（Django开发者的偏爱），那么你只需要在每个URL后添加斜杠，并且设置”APPEND_SLASH”为”True”.  如果不喜欢URL以斜杠结尾或者根据每个URL来决定，那么需要设置”APPEND_SLASH”为”False”,并且根据你自己的意愿来添加结尾斜杠/在URL模式后.

#### Django时区

默认值是Django的诞生地：美国/芝加哥，如果你处在别的时区，你需要在settings.py文件中更改这个值。

