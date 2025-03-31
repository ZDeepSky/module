#include <iostream>
#include <cstdio>
#include <unistd.h>


#include <string>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>


using namespace std;


int main(int argc, char * argv[])
{
    if(argc != 3)
    {
        cout<<"error: example ./client 192.168.101.139 5005\n"<<endl;
        return -1;
    }
    
    //第一步，创建客户端socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd == -1)
    {
        perror("socket fd crt error\r\n");
        return -1;
    }

    //第二步，服务器发起请求
    struct hostent *h;
    if((h = gethostbyname(argv[1])) == nullptr)//将字符串转为结构体
    {
        cout<<__FUNCTION__<<__LINE__<<" socket gethostbyname fail"<<endl; 
        close(socketfd);
        return -1;
    }

    struct sockaddr_in servAddr={0};

    memset(&servAddr, 0, sizeof(sockaddr_in));
    servAddr.sin_family = AF_INET;
    memcpy(&servAddr.sin_addr, h->h_addr, h->h_length);
    servAddr.sin_port = htons(atoi(argv[2]));

    if(connect(socketfd,(struct sockaddr *)&servAddr,sizeof(servAddr))!=0)
    {
        perror("connect fail");
        return -1;
    };
    

    //第三步通信
    char buffer[1024] = {0};
    for(int i = 0; i<3; i++)
    {
        int iret;
        // memset(buffer, 0, sizeof(buffer));
        sprintf(buffer, "这是第%d 个超级女生",i);

        if( (iret = send(socketfd, buffer, strlen(buffer),0)) <=0)
        {
            perror("send error");
            break;
        }

        cout<<"发送:"<<buffer<<endl;
        
        memset(buffer, 0, sizeof(buffer));
        sleep(1);

    }
    int iretRsv = recv(socketfd, buffer, sizeof(buffer), 0);
    if(iretRsv<=0)
    {
        perror("secv error");
    }

    cout << "rsv:" << buffer << endl;
    close(socketfd);
    return 0;
}