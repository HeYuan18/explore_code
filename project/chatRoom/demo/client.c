/*************************************************************************
	> File Name: Client.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月01日 星期五 22时51分31秒
 ************************************************************************/

#include"stdfx.h"
#include"client.h"

int connect_server(int *sockfd)
{
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(serveraddr.sin_zero), 8);

    if((*sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    if(connect(*sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    
    return handle_connect(*sockfd);
}

void io_select(int sockfd)
{
    fd_set readset;
    FD_ZERO(&readset);

    int nready = 0;
    int std = fileno(stdin);
    int maxfd = sockfd;

    while(1)
    {
        FD_ZERO(&readset);
        FD_SET(sockfd, &readset);
        FD_SET(std, &readset);
        
        printf("%s~.~:  ", name);
        fflush(stdout);
        nready = select(1 + maxfd, &readset, NULL, NULL, NULL);
        if(nready <= 0)
        {
            perror("select");
            continue;
        }
        else
        {
            if(FD_ISSET(sockfd, &readset))
            {
                memset(msg_buf, 0, __msg_len__);
                int recv_len = recv(sockfd, msg_buf, __msg_len__, 0);
                recv_len -= 1;
                if(recv_len <= 0)
                {
                    printf("\nserver_abnormal.\n");
                    fflush(stdout);
                    break;
                }
                handle_output();
            }
            if(FD_ISSET(std, &readset))
            {
                memset(msg.buffer, 0, sizeof(msg.buffer));
                if(fgets(msg.buffer, sizeof(msg.buffer), stdin) == NULL)
                {
                    perror("fgets");
                    continue;
                }
                if(handle_input(sockfd))
                {
                    break;
                }
            }
        }
    }
    FD_ZERO(&readset);
    close(sockfd);
}

int main(int argc, char *argv[])
{
    int sockfd = -1;
    initMember();
    initMsg();
    initRun();
    mkdir_msgRecord();

    if(connect_server(&sockfd) == normal)
    {
        io_select(sockfd);
    }

    return 0;
}
