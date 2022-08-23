# Git

## 常用命令

| 常用命令                                    |                                                              |
| ------------------------------------------- | ------------------------------------------------------------ |
| 初始化仓库                                  | git init                                                     |
| 添加文件到仓库                              | 1. git add \<file>可反复多次使用，添加多个文件<br />2. git commit -m \<message> |
| 仓库当前的状态                              | git status                                                   |
| 查看修改了什么内容                          | git diff \<file>                                             |
| 查看历史记录                                | git log                                                      |
| 美化日志输出                                | git log --pretty=oneline                                     |
| 版本回退到上一个版本                        | git reset --hard HEAD^<br />HEAD表示当前版本，上一个版本就是`HEAD^`，上上一个版本就是`HEAD^^`，上100个版本写成HEAD~100 |
| 指定回到未来的某个版本                      | git reset --hard \<commit id>                                |
| 查看历史命令                                | git reflog                                                   |
| 回到最近一次`git commit`或`git add`时的状态 | git checkout -- readme.txt                                   |
| 生成ssh key                                 | ssh-keygen -t rsa -C "youremail@example.com"                 |
| 创建并切换到新分支                          | 1. git checkout -b branch_name<br />2. git switch -c dev     |
| 切换分支                                    | 1. git checkout branch_name<br />2. git switch branch_name   |
| 查看当前分支                                | git branch 命令会列出所有分支，当前分支前面会标一个`*`号。   |
| 合并到主分支                                | git merge branch_name                                        |
| 删除分支                                    | git branch -d branch_name                                    |
| 存储当前工作现场                            | git stash                                                    |
| 查看远程库信息                              | 使用git remote -v；                                          |
| 从本地推送分支                              | 使用git push origin branch-name，如果推送失败，先用git pull抓取远程的新提交； |
| 在本地创建和远程分支对应的分支              | 使用git checkout -b branch-name origin/branch-name，本地和远程分支的名称最好一致； |
| 建立本地分支和远程分支的关联                | 使用git branch --set-upstream branch-name origin/branch-name； |
| 创建新标签                                  | 1. git tag \<name><br />2.git tag -a \<name> -m " message" commit_id |
| 查看标签                                    | git tag                                                      |
| 查看标签信息                                | git show \<tagname>                                          |



```git
git clean -df
git reset --hard
git pull
```



### 分支

我想基于这个提交以及它所有的父提交进行新的工作

#### 创建分支

```git
git branch name
```

#### 切换分支

```git
git checkout name
```

#### 创建并切换分支

```git
git checkout -b name
```





## 连接配置

>1）git config --global user.name "your name"    设置账号
>2）git config --global user.email "your email"    设置邮箱
>3）ssh-keygen -t rsa -C "your email"      生成邮箱。如果此步骤什么也不输入会在~/.ssh目录下生成id_rsa.pub和id_rsa
>4）将id_rsa.pub的内容即公钥添加到gitee官网的ssh公钥中。
>5）eval "$(ssh-agent -s)"          确认ssh-agent处于开启中，打印Agent pid ...表示启用中
>6）ssh-add ~/.ssh/id_rsa_gitee        将ssh key添加到ssh agent中，添加成功提示：Identity added: /home/zsx/.ssh/id_rsa_gitee (/home/zsx/.ssh/id_rsa_gitee)
>7）ssh -T git@gitee.com            测试是否与gitee连接成功，连接成功提示：Hi zsx722! You've successfully authenticated, but GITEE.COM does not provide shell access.
>8）连接成功后即可执行git相关命令