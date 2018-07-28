/*************************************************************************
	> File Name: sysAnalyse.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月20日 星期五 17时04分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef struct listNode{
    struct listNode *prev;
    int data;
    struct listNode *next;
}listNode;

typedef struct relationship{
    int nums;
    listNode pair[0];
}Rel;

typedef struct system{
    int nums;
    int time[0];
}Sys;

int *flag = NULL;

void init(Sys **sys, Rel **rel, int m, int n)
{ 
    int i = 0;
    assert((NULL == *sys) && (NULL == *rel));

    flag = (int*)malloc(sizeof(int) * m);
    if(NULL == flag)
    {
        perror("malloc_flag_falure");
        return;
    }

    *sys = (Sys*)malloc(sizeof(int) * (m + 1));
    if(NULL == *sys)
    {
        perror("malloc_sys_falure");
        return;
    }
    *rel = (Rel*)malloc(sizeof(int) + sizeof(listNode) * m);
    if(NULL == *rel)
    {
        perror("malloc_rel_falure");
        return;
    }

    for(; i < m; ++i)
    {
        flag[i] = 1;
    }
    (*sys)->nums = m;
    for(i = 0; i < m; ++i)
    {
        (*sys)->time[i] = 0;
    }
    (*rel)->nums = n;
    for(i = 0; i < m; ++i)
    {
        (*rel)->pair[i].prev = NULL;
        (*rel)->pair[i].data = 0;
        (*rel)->pair[i].next = NULL;
    }
}

static void hashTable(Rel **rel, int key, int value)
{
    listNode *p = NULL, *q = NULL;
    q = (listNode*)malloc(sizeof(listNode));
    if(NULL == q)
    {
        perror("malloc_hashTable");
        return;
    }
    q->next = NULL;
    q->data = value;

    /*头插法---降低时间复杂度*/
    p = &(*rel)->pair[key];
    p = p->next;
    (*rel)->pair[key].next = q;
    q->prev = &(*rel)->pair[key];
    q->next = p;
    ++(*rel)->pair[key].data;

    p = NULL;
    q = NULL;
}

void inputData(Sys **sys, Rel **rel)
{
    assert((NULL != *sys) && (NULL != *rel));
    int i = 0, key = 0, value = 0;

    printf("请输入%d个系统的耗时：\n", (*sys)->nums);
    for(; i < (*sys)->nums; ++i)
    {
        scanf("%d", &(*sys)->time[i]);
    }
    printf("请输入%d个依赖关系：\n", (*rel)->nums);
    for(i = 0; i < (*rel)->nums; ++i)
    {
        scanf("%d %d", &key, &value);
        hashTable(rel, key - 1, value - 1);
    }
}

int analyse(const Sys *sys, const Rel *rel)
{
    assert((NULL != sys) && (NULL != rel));
    int time = 0, maxt = 0, num = 0, i = 0;
    listNode *p = NULL, *q = NULL;

    for(; i < sys->nums; ++i)
    {
        if(rel->pair[i].next)
        {
            p = rel->pair[i].next;
            while(p)
            {
                p = rel->pair[p->data].next;
            }
        }
    }
    p = NULL;

    return maxt;
}

void printInfo(const Sys *sys, const Rel *rel)
{
    assert((NULL != sys) && (NULL != rel));
    int i = 0;
    listNode *p = NULL;

    printf("\n-----系统详情-----\n");
    printf("系统个数: %d, 依赖个数：%d\n耗时情况：\n", sys->nums, rel->nums);
    for(; i < sys->nums; ++i)
    {
        printf("\t\t%d ms\n", sys->time[i]);
    }
    printf("\n依赖关系：\n");
    for(i = 0; i < sys->nums; ++i)
    {
        if(rel->pair[i].next)
        {
            p = rel->pair[i].next;  
            while(p)
            {
                printf("\t\t%d -> %d\n", i + 1, (p->data) + 1);
                p = p->next;
            }
        }
    }
    p = NULL;
}

void reclaim(Sys **sys, Rel **rel)
{
    if(NULL != *sys)
    {
        free(*sys);
        *sys = NULL;
    }
    if(NULL != *rel)
    {
        free(*rel);
        *rel = NULL;
    }
}

int main(int argc, char *argv[])
{
    Sys *s = NULL;
    Rel *r = NULL;
    int m = 0, n = 0;

    printf("请输入系统个数和依赖关系个数：");
    scanf("%d %d", &m, &n);

    init(&s, &r, m, n);
    inputData(&s, &r);
    printInfo(s, r);
    reclaim(&s, &r);

    return 0;
}
