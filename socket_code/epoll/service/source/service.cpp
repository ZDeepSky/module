#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <linux/tipc.h>  // TIPC相关头文件
#include "service.h"

using namespace std;

// 初始化服务端用于监听的socket。

bool initTipcSocket(int &listenFd, int serviceName)
{
    listenFd = 0;
    listenFd = socket(AF_TIPC, SOCK_SEQPACKET, 0);
    if(listenFd == -1)
    {
        perror("socket");
        return false;
    }

    sockaddr_tipc servAddr = {0};
    servAddr.family = AF_TIPC;
    servAddr.addrtype = TIPC_ADDR_NAME;
    servAddr.scope = TIPC_CLUSTER_SCOPE;// 集群可见
    servAddr.addr.name.domain = 0;
    servAddr.addr.name.name.type = SERVICE_TEST1;
    servAddr.addr.name.name.instance = 1; //实例号

    if(bind(listenFd,(sockaddr*)&servAddr, sizeof(servAddr)) != 0)
    {
        perror("bind() failed");
        close(listenFd);
        return false;
    }

    if(listen(listenFd, 5)!=0)
    {
        perror("listen");
        close(listenFd);
        return false;
    }
    return true;
}


int main(int argc, char *argv[])
{
    if (argc != 2) { printf("usage: ./tcpselect port\n"); return -1; }

    int listenFd = 0;
    if(!initTipcSocket(listenFd, atoi(argv[1])))
    {
        return -1;
    }

    cout << "TIPC服务端已启动，等待连接..." << endl;


    //epoll 的处理
    // 创建epoll
    int epollFd = epoll_create(1);
    epoll_event ev={0};//声明事件数据结构

    ev.data.fd = listenFd;
    ev.events=EPOLLIN;

    epoll_ctl(epollFd, EPOLL_CTL_ADD, listenFd,&ev);
    epoll_event evs[10];

    while(true)
    {
        int envNum = epoll_wait(epollFd, evs, 10, -1);

        if(envNum < 0)
        {
            perror("epoll wait");
            break;            
        }

        if(envNum == 0)
        {
            perror("epoll timeout");
            continue;
        }

        //infds 表示的是事件发生的socket
        for(int envIndex = 0; envIndex < envNum; envIndex++)
        {
            printf("evs[envIndex].data.fd  %d\r\n", evs[envIndex].data.fd );
            if(evs[envIndex].data.fd == listenFd)
            {
                sockaddr_tipc servAddrClient = {0};
                socklen_t len = sizeof(servAddrClient);
                // int clientFd = accept(listenFd, (sockaddr*)&servAddrClient, &len);
                int clientFd  = accept(listenFd,NULL,NULL);
                printf("servAddrClient.addrtype =%d\r\n", servAddrClient.addrtype);
                printf("clientFd =%d\r\n", clientFd);

                ev.data.fd = clientFd;
                ev.events=EPOLLIN;
                
                epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd,&ev);
            }
            else
            {

                char buff[1024];
                memset(buff, 0, sizeof(buff));
                if(recv(evs[envIndex].data.fd, buff, sizeof(buff), 0)<=0)
                {
                    printf("close client fd");
                    close(evs[envIndex].data.fd);
                    //如果socket被关闭，会自动删除epollfd，不需要单独删除
                }
                else{
                    printf("%d\r\n",);
                    send(evs[envIndex].data.fd, buff, strlen(buff), 0);
                }

            }
        }

    }

    close(listenFd);
    return 0;
}