/*************************************************************************
	> File Name: 1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月29日 星期四 22时41分36秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int* init_arr(int* arr, int len)
{
    if(0 == len)
    {
        printf("err: check input\n");
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

int* trans_arr(int* const arr, int len)
{
    int i = 0, count = 0;
    int* p = arr;
    
    for(; i < len; ++i)
    {
        if(0 != *p)
        {
            arr[count++] = *p;
        }
        ++p;
    }
    for(i = count; i < len; ++i)
    {
        arr[i] = 0;
    }

    return arr;
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
    int* arr = NULL;
    int len = 0;
    scanf("%d", &len);

    arr = init_arr(arr, len);
    trans_arr(arr, len);
    print_arr(arr, len);

    free(arr);
    arr = NULL;
    
    return 0;
}
