/*************************************************************************
	> File Name: analyseSystem.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月17日 星期二 15时30分18秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

typedef struct system{
    int num;
    int times[0];
}Sys;

typedef struct rely{
    int num;
    int nexus[0];
}Rel;

void init(Sys **sys, Rel **rel, int a, int b)
{
    int i = 0, j = 0;
    
    *sys = (Sys*)malloc(sizeof(int) * (a + 1));
    *rel = (Rel*)malloc(sizeof(int) * (b * 2 + 1));
    assert((NULL != *sys) && (NULL != *rel));
   
    (*sys)->num = a;
    printf("输入%d个系统所耗时间：\n", a);
    for(; i < a; ++i)
    {
        scanf("%d", &(*sys)->times[i]);
    }

    (*rel)->num = b;
    printf("输入%d个系统依赖关系：\n", b);
    for(; j < b; ++j)
    {
        i = j * 2 + 1;
        scanf("%d %d", &(*rel)->nexus[i - 1], &(*rel)->nexus[i]);
    }
}

int analyse(const Sys *sys, const Rel *rel)
{
    printf("\n------------分析结果--------------\n");
    int time = 0, maxt = 0;
    int i = 0, j = 0, m = 0, n = 0, k = 0;
    int *relation = NULL;

    relation = (int*)malloc(sizeof(int) * rel->num);
    assert(NULL != relation);
    memset(relation, 0, sizeof(int) * rel->num);

    for(; m < rel->num; ++m)
    {
        if(relation[m])
        {
            continue;
        }

        i = m * 2 + 1;
        k = i;
        time = sys->times[rel->nexus[i - 1] - 1] + sys->times[rel->nexus[i] - 1];
        printf("依赖关系：%d -> %d", rel->nexus[i - 1], rel->nexus[i]);

        for(n = 0; n < rel->num; ++n)
        {
            j = n * 2 + 1;
            
            if(rel->nexus[k] == rel->nexus[j - 1])
            {
                k = j;
                relation[k / 2] = 1;
                time += sys->times[rel->nexus[j] - 1];
                printf(" -> %d", rel->nexus[j]);
            }
        }
        printf("\n");

        if(time > maxt)
        {
            maxt = time;
        }
        time = 0;
    }

    printf("最长耗时%d\n", maxt);

    return maxt;
}

void printInfo(const Sys *sys, const Rel *rel)
{
    printf("\n\n------------系统信息--------------\n");
    int i = 0, j = 0;

    printf("系统个数：%d, 依赖关系个数：%d\n", sys->num, rel->num);
    printf("系统耗时：\n");
    for(; i < sys->num; ++i)
    {
        printf("%d\n", sys->times[i]);
    }
    printf("系统依赖关系：\n");
    for(; j < rel->num; ++j)
    {
        i = j * 2 + 1;
        printf("%d -> %d\n", rel->nexus[i - 1], rel->nexus[i]);
    }
}

void delete(Sys **sys, Rel **rel)
{
    free(*sys);
    free(*rel);
    *sys = NULL;
    *rel = NULL;
}

int main(int argc, char *argv[])
{
    int a = 0, b = 0;
    Sys *S = NULL;
    Rel *R = NULL;

    printf("输入系统个数和依赖关系个数：");
    scanf("%d %d", &a, &b);

    init(&S, &R, a, b);

    printInfo(S, R);
    analyse(S, R);

    delete(&S, &R);

    return 0;
}
