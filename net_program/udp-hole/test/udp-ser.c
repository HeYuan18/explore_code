/*************************************************************************
	> File Name: udp-ser.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年06月27日 星期三 19时11分28秒
 ************************************************************************/

#include<error.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define max_buf 1024

char buf[max_buf];

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef struct session
{
    int port;
    struct in_addr ip;
}Session;                           //ip+port->session

int main(int argc, char* argv[])
{
    Session cli[2];
    int sockfd;

    SA_IN server, client;
    bzero(&server, sizeof(SA_IN));
    bzero(&client, sizeof(SA_IN));
    socklen_t addrlen = sizeof(SA_IN);
    server.sin_port = htons(4399);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    
    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    { 
       perror("socket");

       return -1;
    }
    if(bind(sockfd, (SA*)&server, sizeof(SA_IN)) == -1)
    {
        perror("bind");

        return -1;
    }

    while(1)
    {
        memset(cli, 0, 2 * sizeof(Session));

        /*接收两个心跳包，并记录与此服务器连接的客户端的网关ip+port*/
        recvfrom(sockfd, &buf, sizeof(buf) - 1, 0, (SA*)&client, &addrlen);
        memcpy(&cli[0].ip, &client.sin_addr, sizeof(struct in_addr));
        cli[0].port = client.sin_port;
        printf("ip: %s\tport: %d OK\n", inet_ntoa(cli[0].ip), ntohs(cli[0].port));
        bzero(&client, sizeof(SA_IN));
        recvfrom(sockfd, &buf, sizeof(buf) - 1, 0, (SA*)&client, &addrlen);
        memcpy(&cli[1].ip, &client.sin_addr, sizeof(struct in_addr));
        cli[1].port = client.sin_port;
        printf("ip: %s\tport: %d OK\n", inet_ntoa(cli[1].ip), ntohs(cli[1].port));


        /*服务器向两台客户端互通对方的网关ip+port*/
        memset(buf, 0, sizeof(buf));
        memcpy(buf, &cli[0], sizeof(Session));
        sendto(sockfd, buf, sizeof(Session), 0, (SA*)&client, addrlen);

        memset(buf, 0, sizeof(buf));
        memcpy(buf, &cli[1], sizeof(Session));
        client.sin_addr = cli[0].ip;
        client.sin_port = cli[0].port;
        sendto(sockfd, buf, sizeof(Session), 0, (SA*)&client, addrlen);
    }

       return 0;
}
