# Anaconda安装

[参考](https://blog.csdn.net/wq_ocean_/article/details/103889237?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522164161387516780265459246%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=164161387516780265459246&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-103889237.pc_search_insert_es_download&utm_term=Anaconda&spm=1018.2226.3001.4187)

## 安装包

[清华大学开源软件镜像站](https://mirrors.tuna.tsinghua.edu.cn/anaconda/archive/)，一般下载最新版本前一个版本。

## 勾选注意

+ Add Path（添加到环境变量）
+ Register Anaconda as System python（安装Anaconda中的python优先级最高）

### 测试安装

cmd输入:

> conda --version

出现版本号则成功

## 更改镜像源

#### 方法一

>conda config --add channels https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/main/
>conda config --set show_channel_urls yes

打开`C:\UseC:UsersUser`，`.condarc`文件内容被更改为

>ssl_verify: true
> channels:
>  \- https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
>  \- defaults
> show_channel_urls: true

#### 方法二

打开`.condarc`，将上述内容复制进去

## 更新包

先更新conda

```sql
conda update conda
```

再更新第三方所有包

```r
conda upgrade --all
```

### python自带IDEL

> D:\softsapce\programming\Anaconda\anaconda3\Lib\idlelib