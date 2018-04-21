/*************************************************************************
	> File Name: number.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月20日 星期五 20时22分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define T 100
#define n 1000000000
typedef int* Arr;

Arr init_arr(Arr l, int len)
{
    l = (Arr)malloc(sizeof(int) * len);
    if(NULL == l)
    {
        return NULL;
    }
    int i = 0;
    for(; i < len; ++i)
    {
        scanf("%d", &l[i]);
        /*1<= n <= 10^9*/
    }

    return l;
}

int getBit(int num)
{
    int bit = 1;
    while(num /= 10)
    {
        ++bit;
    }

    return bit;
}

int getBCount(int bit)
{
    int result = 0;
    
    result = 9 * pow(10, bit - 1);

    return result;
}

void getCount(int num)
{
    int bit = getBit(num);
    unsigned long int result = 0;

    int i = 1;
    for(; i < bit; ++i)
    {
        result += getBCount(i);
    }
    

    result += (num - pow(10, bit - 1) + 1) * bit;

    printf("%lu\n", result);
}


Arr destory_arr(Arr l)
{
    if(NULL != l)
    {
        free(l);
        l = NULL;
    }

    return l;
}

int main()
{
    int t = 0;
    scanf("%d", &t);
    if(0 >= t || 100 < t)
    {
        return 0;
    }
    
    int i = 0;
    Arr L = NULL;
    L = init_arr(L, t);
    
    for(; i < t; ++i)
    {
        getCount(L[i]);
    }

    L = destory_arr(L);
    
    return 0;
}
