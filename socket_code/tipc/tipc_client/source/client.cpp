#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <linux/tipc.h>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "用法: ./client <服务类型号> <实例号>" << endl;
        cout << "示例: ./client 5555 1" << endl;
        return -1;
    }

    // 1. 创建TIPC套接字
    int sockFd = socket(AF_TIPC, SOCK_SEQPACKET, 0);
    if(sockFd == -1)
    {
        perror("socket创建失败");
        return -1;
    }

    // 2. 配置目标服务地址
    struct sockaddr_tipc servAddr = {0};
    servAddr.family = AF_TIPC;
    servAddr.addrtype = TIPC_ADDR_NAME;       // 与服务端保持一致
    servAddr.scope = TIPC_CLUSTER_SCOPE;      // 集群范围
    servAddr.addr.name.name.type = atoi(argv[1]);  // 服务类型
    servAddr.addr.name.name.instance = atoi(argv[2]); // 实例号
    servAddr.addr.name.domain = 0;            // 域号

    // 3. 连接服务端
    if(connect(sockFd, (struct sockaddr*)&servAddr, sizeof(servAddr)) != 0)
    {
        perror("连接失败");
        close(sockFd);
        return -1;
    }

    cout << "成功连接到TIPC服务！" << endl;

    // 4. 通信循环
    char buff[1024];
    while(true)
    {
        cout << "输入要发送的消息（输入exit退出）: ";
        cin.getline(buff, sizeof(buff));
        
        if(strcmp(buff, "exit") == 0) break;

        // 发送数据
        int sendRet = send(sockFd, buff, strlen(buff), 0);
        if(sendRet <= 0)
        {
            perror("发送失败");
            break;
        }

        // 接收响应
        memset(buff, 0, sizeof(buff));
     
    }
    while(true)
    {
        int recvRet = recv(sockFd, buff, sizeof(buff), 0);
        if(recvRet <= 0)
        {
            perror("接收失败");
            break;
        }
        
         cout << "收到响应: " << buff << endl;
    }
    close(sockFd);
    return 0;
}