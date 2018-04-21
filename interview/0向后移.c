/*************************************************************************
	> File Name: 0向后移.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月29日 星期四 19时18分56秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int* init_arr(int* arr, int len)
{
    if(0 == len)
    {
        printf("err:please  check input\n");
        exit(1);
    }
    if(1 == len)
    {
        scanf("%d", &len);
        printf("%d\n", len);
        exit(1);
    }

    int i = 0;
    arr = (int*)malloc(len* sizeof(int));
    if(arr == NULL)
    {
        printf("err: malloc memory\n");
        exit(1);
    }

    for(; i < len; ++i)
    {
        scanf("%d", &arr[i]);
    }

    return arr;
}

void swap(int* a, int* b)
{
    int tmp = *b;
    *b = *a;
    *a = tmp;
}

int* trans_arr(int* const arr, int len)
{
    int* p = arr;
    int* q = arr;

    while(len--)
    {
        if(0 == *p && 0 != *q)
        {
            swap(p, q);
            ++p;
            ++q;

            continue;
        }
        if(0 != *p)
        {
            ++p;
            ++q;
        }
        if(0 == *q)
        {
            ++q;
        }
    }

    p = NULL;
    q = NULL;
}

void print_arr(const int* const arr, int len)
{
    int i = 0;
    for(; i < len; ++i)
    {
        printf("%d\n", arr[i]);
    }
}

int main()
{
    int len = 0, i = 0;
    int* arr = NULL;
    scanf("%d", &len);

    arr = init_arr(arr, len);

    
    trans_arr(arr, len);

    print_arr(arr, len);
    
    free(arr);
    arr = NULL;

    return 0;
}
