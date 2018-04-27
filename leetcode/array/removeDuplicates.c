/*************************************************************************
	> File Name: removeDuplicates.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月15日 星期日 20时29分05秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int* Array;

Array init_array(Array arr, int len)
{
    arr = (Array)malloc(sizeof(int) * len);
    if(NULL == arr)
    {
        return NULL;
    }

    memset(arr, 0, len);

    return arr;
}

Array input_array(Array arr, int len)
{
    printf("input: ");
    int i = 0;
    for(; i < len; ++i)
    {
        scanf("%d", &arr[i]);
    }

    return arr;
}

int removeDuplicates(Array arr, int len)
{
    if(NULL == arr)
    {
        return 0;
    }
    if(1 >= len)
    {
        return len;
    }
    
    int r = 0, q = 1, p = 1;

    while(q < len)
    {
        if(arr[r] < arr[q])
        {
            if(arr[p] < arr[q])
            {
                arr[p] = arr[q];
            }
            ++p;
            ++q;
            ++r;
        }
        else
        {
            ++q;
            if(arr[r] < arr[q] && q < len)
            {
                arr[p] = arr[q];
                ++p;
                ++q;
                ++r;
            }
        }
    }
    
    return r + 1;
}

void print_array(Array arr, int len)
{
    printf("printA: ");
    int i = 0;
    for(; i < len; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

Array destory_array(Array arr)
{
    if(NULL != arr)
    {
        free(arr);
        arr = NULL;
    }

    return arr;
}

int main()
{
    int len = 0;
    printf("input len: ");
    scanf("%d", &len);
    if(0 == len)
    {
        printf("InvaildInput\n");

        return 0;
    }

    Array Arr = NULL;
    Arr = init_array(Arr, len);
    Arr = input_array(Arr, len);
    
    int num = removeDuplicates(Arr, len);
    print_array(Arr, num);

    Arr = destory_array(Arr);

    return 0;
}
