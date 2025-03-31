#include <iostream>
#include <cstdio>

#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
using namespace std;

int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        cout<<"example: ./service 5555"<<endl;
        return -1;
    }

    //建立服务端socket
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenFd == -1)
    {
        perror("listen");
        return -1;
    }

    //第2步
    sockaddr_in servAddr = {0};
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = htons(atoi(argv[1]));


    if(bind(listenFd,(sockaddr *)&servAddr, sizeof(servAddr)))
    {
        perror("bind");
        close(listenFd);
        return -1;
    };


    //socket设置为可连接状态 5是最大的监听数
    if(listen(listenFd, 5) != 0)
    {
        perror("listen");
        close(listenFd);
        return -1;
    }

    //第4步 受理连接请求
    int clientFd = accept(listenFd, 0, 0);
    if(clientFd == -1)
    {
        perror("accept");
        close(listenFd);
        return -1;
    }


    char buff[1024]={0};
    while(true)
    {
        int ret;
        memset(&buff, 0, sizeof(buff));

        if((ret = recv(clientFd, buff, sizeof(buff), 0)) <= 0)
        {
            cout<<"recv error"<<endl;
            break;
        }
        cout<<"recv buff: "<<buff<<endl;
        strcpy(buff,"ok");

        if((ret = send(clientFd, buff, strlen(buff), 0))<=0)
        {
            cout<<"send error"<<endl;
            break;
        }

        cout<<"send buff "<<buff<<endl;

    }


    close(listenFd);
    close(clientFd);
    return 0; 
}



