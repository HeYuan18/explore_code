/*************************************************************************
	> File Name: redPacket.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月20日 星期三 20时01分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<time.h>

#define THREAD_MAX 32750
#define THREAD_NUM 200       //最多抢包人数
#define MONEY_MAX  500      //最大钱数
#define _RAND(min, max) (rand() % ((max) - (min)) + (min))

pthread_t thread[THREAD_NUM];
pthread_mutex_t mut;

typedef struct redpacket
{
    int num;        //红包个数
    int money;     //金额，单位是分
}red_Packet;

static red_Packet redPacket = {0};

/*消费者*/
void *woker(void *arg)
{
    int money = 0;

    pthread_mutex_lock(&mut);

    if(redPacket.num <= 0)
    {
        printf("Thread:#%lu 手慢了哦，红包被拿完了.\n", pthread_self());
        pthread_mutex_unlock(&mut);
        pthread_exit(NULL);
    }
    else if(redPacket.num == 1)
    {
        money = redPacket.money;
    }
    else
    {
        /* roll is 0.1 ~ 1.99*/
        money = redPacket.money * _RAND(10, 199) / 100 / redPacket.num;
    }

    redPacket.money -= money;
    -- redPacket.num;

    printf("Thread:#%lu get %d.%02d元, left[%d个红包, %d.%02d元]\n", pthread_self(), money / 100, money %100, redPacket.num, redPacket.money / 100, redPacket.money % 100);

    pthread_mutex_unlock(&mut);
    pthread_exit(NULL);

    return ((void*)0);
}

/*创建线程*/
void thread_create(void)
{
    memset(&thread, 0, sizeof(thread));
    for(int i = 0; i < THREAD_NUM; ++ i)
    {
        if((pthread_create(&thread[i], NULL, woker, NULL)) != 0)
        {
            printf("线程%d创建失败!\n", i);
        }
        else
        {
            //printf("i=%d\t线程%lu被创建.\n\n", i, thread[i]);
        }
    }
}

/*回收线程*/
void thread_wait(void)
{
    for(int i = 0; i < THREAD_NUM; ++i)
    {
        if(thread[i] != 0)  //?
        {
            pthread_join(thread[i], NULL);
            //printf("线程#%lu已经结束.\n", thread[i]);
        }
    }
}

int main(int argc, char *argv[])
{
    /*用默认属性初始化互斥锁*/
    pthread_mutex_init(&mut, NULL);
    
    srand((unsigned)time(NULL));  //产生随机种子

    float num = 0;
    float money = 0;

    while(1)
    {
        printf("Input: <number> <money>\n");

        if(fscanf(stdin, "%f %f", &num, &money) == EOF)
        {
            break;
        } 
        if(num <= 0 || num > THREAD_NUM)    //红包个数可以大于人数
        {
            printf("Package number out of range: [1, %d]\n", THREAD_NUM);
            continue;
        }
        if(money < 1 || money > MONEY_MAX)
        {
            printf("Total money out of range: [1, %d]\n", MONEY_MAX);
            continue;
        }

        redPacket.num = num;
        redPacket.money = 100 * money;

        printf("Init: [%d个红包, %d.%02d元]\n", redPacket.num, redPacket.money / 100, redPacket.money % 100);

        thread_create();    //创建线程
        thread_wait();      //回收线程
    }

    pthread_mutex_destroy(&mut);

    return 0;
}
