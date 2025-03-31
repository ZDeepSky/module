#include <iostream>
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/tipc.h>  // TIPC相关头文件

using namespace std;



int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        cout << "example: ./service <服务类型号>" << endl;
        return -1;
    }

    // 1. 创建TIPC套接字
    int listenFd = socket(AF_TIPC, SOCK_SEQPACKET, 0);
    if(listenFd == -1)
    {
        perror("socket");
        return -1;
    }

    // 2. 配置TIPC地址结构
    struct sockaddr_tipc servAddr = {0};
    servAddr.family = AF_TIPC;
    servAddr.addrtype = TIPC_ADDR_NAME;       // 使用命名地址
    servAddr.scope = TIPC_CLUSTER_SCOPE;      // 集群范围内可见
    servAddr.addr.name.name.type = atoi(argv[1]);  // 服务类型号由参数传入
    servAddr.addr.name.name.instance = 1;     // 实例号固定为1
    servAddr.addr.name.domain = 0;            // 域号设为0

    // 3. 绑定地址
    if(bind(listenFd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0)
    {
        perror("bind");
        close(listenFd);
        return -1;
    }

    // 4. 监听连接
    if(listen(listenFd, 5) != 0)
    {
        perror("listen");
        close(listenFd);
        return -1;
    }

    cout << "TIPC服务端已启动，等待连接..." << endl;

    // 5. 接受连接
    int clientFd = accept(listenFd, NULL, NULL);
    if(clientFd == -1)
    {
        perror("accept");
        close(listenFd);
        return -1;
    }

    // 6. 通信逻辑（保持不变）
    char buff[1024] = {0};
    while(true)
    {
        int ret;
        memset(buff, 0, sizeof(buff));

        if((ret = recv(clientFd, buff, sizeof(buff), 0)) <= 0)
        {
            cout << "连接已关闭" << endl;
            break;
        }
        cout << "收到消息: " << buff << endl;

        strcpy(buff, "ok");
        if((ret = send(clientFd, buff, strlen(buff), 0)) <= 0)
        {
            perror("send");
            break;
        }
        cout << "发送响应: " << buff << endl;
    }

    close(listenFd);
    close(clientFd);
    return 0;
}