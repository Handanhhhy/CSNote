### 通用头文件包含

网络编程常用头文件。下文中使用`#include "common.h"`来代表

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
```

### 服务器和客户端基础模板

#### 服务器

```c
#include "common.h"
int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_addresss port_number \n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);
    /*
    ** 处理客户端的连接和各类事件
    */
    close(listenfd);
    return 0;
}
```



#### 客户端

```c
#include "common.h"

#define BUFFSIZE 1024

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage : %s ip_adderss port\n", basename(argv[0]));
        return 1;
    }

    const char *serv_ip = argv[1];
    const int serv_port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, serv_ip, &servaddr.sin_addr.s_addr);
    servaddr.sin_port = htons(serv_port);

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect errorno : %d\n", errno);
        close(sockfd);
        return 1;
    }
    char buf[BUFFSIZE];
    while (1)
    {
        /*从标准输入获取数据*/
        fgets(buf, sizeof(buf), stdin);
        /*将数据写给服务器*/
        /*普通数据*/
        send(sockfd, buf, sizeof(buf), 0);
        /*外带数据*/
        //send(sockfd, buf, sizeof(buf), MSG_OOB);
        /*此次操作为非阻塞*/
        /*从服务器读数据*/
        int num = recv(sockfd, buf, sizeof(buf), MSG_DONTWAIT);
        if (num == 0)
        {
            printf("server disconnected\n");
            break;
        }
        else if (num > 0) /*写至标准输出*/
        {
            fputs(buf, stdout);
            memset(buf, '\0', sizeof(buf));
        }
        else
        {
            //printf("recv errno : %d\n", errno);
            // break;
        }

        //write(STDOUT_FILENO, buf, len);
    }
    close(sockfd);
    return 0;
}
```



### IO复用函数

#### select

select：处理正常数据处于正常状态，处理外带数据处于异常状态
select：在一段指定时间内，监听用户感兴趣的文件描述符上的可读，可写和异常等事件。
返回值：成功时返回就绪文件描述符的总数，若在超时时间内未有任何描述符就绪则返回0，
失败返回-1，并设置errno.若在等待期间收到信号，则返回-1，并设置errno为EINTR
nfds参数：被监听的文件描述符总数，通常设置为监听的所有文件描述符中的最大值加1
timeout参数：传NULL则一直阻塞到某个文件描述符就绪.

```C
int select(int nfds, fd_set* readfds, fd_set* writefds, fd_set* exceptfds, struct timeval* timeout);
```

##### select函数处理外带数据

```c
#include "common.h"
#include <sys/select.h>

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_addresss port_number \n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    address.sin_port = htons(port);
    //IP协议 服务类型 0
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_addr_len);

    if (connfd < 0)
    {
        printf("connect errorno: %d\n", errno);
        close(listenfd);
        return 1;
    }
    char buf[1024];
    //初始化文件描述符集合
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);
    while (1)
    {
        memset(buf, '\0', sizeof(buf));
        FD_SET(connfd, &read_fds);
        FD_SET(connfd, &exception_fds);
        ret = select(connfd + 1, &read_fds, NULL, &exception_fds, NULL);
        if (ret < 0)
        {
            printf("selection failure\n");
            break;
        }
        if (FD_ISSET(connfd, &read_fds))
        {
            ret = recv(connfd, buf, sizeof(buf) - 1, 0);
            if (ret < 0)
            {
                break;
            }
            printf("get %d bytes of normal data:%s \n", ret, buf);
            ret = send(connfd, "ok\n", sizeof("ok\n"), 0);
            if (ret < 0)
            {
                break;
            }
            printf("send ok \n");
        }
        else if (FD_ISSET(connfd, &exception_fds))
        {
            ret = recv(connfd, buf, sizeof(buf) - 1, MSG_OOB);
            if (ret < 0)
            {
                break;
            }
            printf("get %d bytes of obb data:%s \n", ret, buf);
        }
    }
    close(connfd);
    close(listenfd);

    return 0;
}
```

#### poll

poll与select类似，也是在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者。

```c
/*
**nfds:指定被监听事件集合fds的大小。
**timeout:-1调用将阻塞到某个事件发生,poll调用将立即返回
**return：成功时返回就绪文件描述符的总数，若在超时时间内未有任何描述符就绪则返回0，
**失败返回-1，并设置errno.若在等待期间收到信号，则返回-1，并设置errno为EINTR
*/
int pool(struct pollfd* fds, nfds_t nfds,int timeout);
struct pollfd{
    int fd;/*文件描述符*/
    short events;/*注册的事件*/
    short revents;/*实际发生的事件*/
}
typedef unsigned long int nfds_t;

```

常用`POLLIN`(数据可读) 、`POLLOUT`(数据可写)、`POLLRDHUP`(TCP连接被对方关闭，或者对方关闭了写操作)，注意使用时要在代码最开始出定义`_GUN_SOURCE`.

```c
#include "common.h"
#include <sys/poll.h>

#define OPENMAX 1024
#define BUFSIZE 1024

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_addresss port_number \n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    struct pollfd pollfds[OPENMAX];
    for (int i = 0; i < OPENMAX; i++)
        pollfds[i].fd = -1;
    //将listen监听事件放入
    pollfds[0].fd = listenfd;
    pollfds[0].events = POLLIN;
    //当前连接最大文件描述符下标
    int maxConn = 1;
    while (1)
    {
        int readyNum = poll(&pollfds, maxConn + 1, -1);
        if (readyNum < 0)
        {
            printf("poll errorno : %d\n", errno);
            break;
        }
        /*单独处理连接事件*/
        if (pollfds[0].revents & POLLIN)
        {
            struct sockaddr_in client_addr;
            socklen_t client_len = sizeof(client_addr);
            int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
            int i;
            for (i = 1; i < OPENMAX; i++)
            {
                /*插入到第一个未使用的pollfds中*/
                if (pollfds[i].fd == -1)
                {
                    pollfds[i].fd = connfd;
                    pollfds[i].events = POLLIN;
                    break;
                }
            }

            if (i >= FD_SETSIZE)
            {
                printf("too many client connect\n");
                break;
            }
            char client_ip[BUFSIZE];
            printf("[client %d: %s %d]:connected\n", i, inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip)), ntohs(client_addr.sin_port));
            send(connfd, "Welcome!\n", sizeof("Welcome!\n"), 0);
            maxConn = maxConn > i ? maxConn : i;
            /*减少遍历提高效率*/
            if (--readyNum == 0)
                continue;
        }
        /*对客户端事件进行处理*/
        for (int i = 1; i <= maxConn; i++)
        {
            int clienfd = pollfds[i].fd;

            if (clienfd < 0)
                continue;
            if (pollfds[i].revents & POLLIN)
            {
                char buf[BUFSIZE];
                ret = recv(clienfd, buf, sizeof(buf), 0);
                if (ret > 0)
                {
                    printf("[client %d]: %s", i, buf);
                }
                else if (ret == 0)
                {
                    close(clienfd);
                    pollfds[i].fd = -1;
                    printf("[client %d]: disconnected\n", i);
                }
                else
                {
                    /*收到RST标志 客户端因为某些原因需要重新连接*/
                    if (errno == ECONNRESET)
                    {
                        printf("clients[%d] aborted connection\n", i);
                        close(clienfd);
                        pollfds[i].fd = -1;
                    }
                    else
                    {
                        printf("read errorno : %d\n", errno);
                        break;
                    }
                }
            }
            if (--readyNum)
                break;
        }
    }
    close(listenfd);
    return 0;
}
```

#### epoll

epoll在实现上与select、poll有很大的差别，epoll使用一组函数来完成事件处理。epoll将文件描述符上的事件放在内核里的一个时间表中，从而无需像select、poll一样重复传入文件描述符集或事件集，因此epoll需要一个额外的文件描述符来标识内核中的这个事件表。

```c
/*
**size:并不起作用，只给内核一个提示，告诉内核事件表需要多大
**return:返回的文件描述符将作用于其他所有epoll系统调用的第一个参数
*/
int epoll_create(int size);
/*操作epoll的内核事件表函数*/
/*
**op:EPOLL_CTL_ADD(向事件表中注册fd上的事件),
**	 EPOLL_CTL_MOD(修改fd上的事件)
**	 EPOLL_CTL_DEL(删除fd上注册事件)
**events:指定事件
**return:成功返回0，失败返回-1并设置errno
*/
int epoll_ctl(int epfd,int op,int fd,struct epoll_event* events);
struct epoll_event{
    _uint32_t events;/*epoll事件*/
    epoll_data_t data;/*用户数据*/
}
/*联合体 其中fd较为常用 
*若要存入另外的数据,应使用ptr,并且在ptr指向的用户数据中包含fd
*/
typedef union epoll_data{
    void* ptr;
    int fd;
    uint32_t u32;
    uint64_t u64;
}epoll_data_t;
/*
**events:从内核事件表中复制出已经就绪的事件事件
**maxevents:指定最多监听多少个事件,必须大于0
**return:成功返回就绪描述符的个数，失败返回-1并设置errno
*/
int epoll_wait(int epfd,struct epoll_event* events,int maxevents,int timeout);

```

```c
#include "common.h"
#include <sys/epoll.h>

#define OPENMAX 1024
#define BUFSIZE 1024
#define IPLENGTH 20

struct client_data
{
    char ip[IPLENGTH];
    uint16_t port;
    int fd;
};

int main(int argc, char *argv[])
{
    if (argc <= 2)
    {
        printf("usage: %s ip_addresss port_number \n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    const int port = atoi(argv[2]);

    int ret = 0;
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr.s_addr);
    address.sin_port = htons(port);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listen >= 0);

    ret = bind(listenfd, (struct sockaddr *)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(listenfd, 5);
    assert(ret != -1);

    int epfd = epoll_create(OPENMAX);

    struct epoll_event event, readyEvents[OPENMAX];
    event.data.fd = listenfd;
    event.events = EPOLLIN;
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &event);
    assert(ret != -1);
    struct client_data clients[OPENMAX];
    for (int i = 0; i < OPENMAX; i++)
        clients[i].fd = -1;
    int maxConn = 0;
    while (1)
    {
        int readyNum = epoll_wait(epfd, readyEvents, OPENMAX, -1);
        for (int i = 0; i < readyNum; i++)
        {
            struct epoll_event *ptr = readyEvents + i;
            if (!(ptr->events & EPOLLIN))
                continue;
            if (ptr->data.fd == listenfd && ptr->events & EPOLLIN)
            {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);
                int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);
                int j;
                for (j = 0; j < OPENMAX; j++)
                {
                    if (clients[j].fd == -1)
                    {
                        clients[j].fd = connfd;
                        break;
                    }
                }
                if (j >= OPENMAX)
                {
                    printf("too many client connect\n");
                    continue;
                }
                maxConn = maxConn > j ? maxConn : j;
                inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, clients[j].ip, sizeof(clients[j].ip));
                clients[j].port = ntohs(client_addr.sin_port);
                printf("[client %s : %d]:connected\n", clients[j].ip, clients[j].port);
                send(clients[j].fd, "Welcome!\n", sizeof("Welcome!\n"), 0);
                event.data.ptr = (void *)(clients + j);
                event.events = EPOLLIN;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, clients[j].fd, &event);
                assert(ret != -1);
            }
            else
            {
                char buf[BUFSIZE];
                struct client_data *data = (struct client_data *)ptr->data.ptr;
                ret = recv(data->fd, buf, sizeof(buf), 0);
                if (ret <= 0)
                {
                    //先删除因为 ptr中data为指针 指向的文件描述符和clients中为同一个
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, data->fd, NULL);
                    //assert(ret != -1);
                    if (ret == -1)
                    {
                        printf("epoll ctl del errno %d fd %d\n", errno, data->fd);
                        exit(1);
                    }
                    close(data->fd);
                    for (int j = 0; j <= maxConn; j++)
                    {
                        if (clients[j].fd == data->fd)
                        {
                            clients[j].fd = -1;
                            break;
                        }
                    }
                    if (ret < 0)
                        printf("[client %s : %d]: read erron", data->ip, data->port, errno);
                    else
                        printf("[client %s : %d]: disconnected\n", data->ip, data->port);
                }
                else
                {
                    printf("[client %s : %d]: %s", data->ip, data->port, buf);
                    send(data->fd, "Received!\n", sizeof("Received!\n"), 0);
                }
            }
        }
    }

    close(listenfd);
    close(epfd);
    return 0;
}
```



##### epoll_LT



##### epoll_ET

