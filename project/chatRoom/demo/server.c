/*************************************************************************
	> File Name: Server.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月01日 星期五 15时06分56秒
 ************************************************************************/

#include"stdfx.h"
#include"server.h"

void start(int *sockfd)
{
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(serveraddr.sin_addr.s_addr), 8);
    
    if(((*sockfd) = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    int optval = 1;
    if(setsockopt(*sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    if(bind(*sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    if(listen(*sockfd, backlog) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("====================服务器运行成功====================\n");
    printf("允许链接人数: %d\n", (__FD_NUM__ - 1));
}

void io_select(int *sockfd)
{
    fd_set readset, allset;
    FD_ZERO(&allset);
    FD_SET(*sockfd, &allset);

    int maxfd = *sockfd;
    int nready = 0;

    while(1)
    {
        FD_ZERO(&readset);
        readset = allset;
    
        nready = select(1 + maxfd, &readset, NULL, NULL, NULL);

        if(nready <= 0)
        {
            perror("select");
            continue;
        }
        else
        {
            if(FD_ISSET(*sockfd, &readset))
            {
                int connfd = -1; 
                if((connfd = accept(*sockfd, (struct sockaddr*)&clientaddr, &clientaddr_len)) == -1)
                {
                    perror("accept");
                    continue;
                }
                maxfd = (maxfd > connfd) ? maxfd : connfd;

                if(member.count == (__FD_NUM__ - 1))
                {
                    memset(msg_buf, 0, __msg_len__);

                    Run.status = client_max_count;
                    memcpy(msg_buf, &Run, __run_len__);
                    send(connfd, msg_buf, __msg_len__, 0);
                    close(connfd);
                    Run.status = normal;

                    printf("超出最大链接数。\n");
                    printf("\t----->允许链接人数: %d\n", (__FD_NUM__ - 1));
                    fflush(stdout);
                    continue;
                }
                else
                {
                    memset(msg_buf, 0, __msg_len__);

                    memcpy(msg_buf, &Run, __run_len__);
                    send(connfd, msg_buf, __msg_len__, 0);
                }
                
                FD_SET(connfd, &allset);
                set_memberList(connfd);

                if(--nready == 0)
                {
                    continue;
                }
            }
            for(int i = 0; i <= __FD_NUM__; ++i)
            {
                if(member.client[i].fd == -1)
                {
                    continue;
                }
                if(FD_ISSET(member.client[i].fd, &readset))
                {
                    memset(msg_buf, 0, __msg_len__);
                    int recv_len = recv(member.client[i].fd, msg_buf, __msg_len__, 0);
                    recv_len -= 1;
                    if(recv_len <= 0)
                    {
                        close(member.client[i].fd);

                        FD_CLR(member.client[i].fd, &allset);
                        clr_memberList(i);

                        continue;
                    }
                    initMsg();
                    memcpy(&msg, msg_buf, __msg_len__);
                    msg.user = i;
                    memcpy(msg_buf, &msg, __msg_len__);
                    send_cast(member.client[i].fd, msg_buf, __msg_len__, 1, 0);
                }
                if(--nready == 0)
                {
                    continue;
                }
            }
        }   
    }
    FD_ZERO(&readset);
    FD_ZERO(&allset);
}

int main()
{
    int sockfd = 0;
    initMember();
    initMsg();
    
    start(&sockfd);
    io_select(&sockfd);
    close(sockfd);

    return 0;
}
