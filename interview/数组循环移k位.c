/*************************************************************************
	> File Name: 数组循环移k位.c
	> Author: karma1996
	> Mail:   karma1996@foxmail.com
	> Created Time: 2018年04月23日 星期一 22时35分57秒
 ************************************************************************/

#include<stdio.h>

typedef int* Arr;

Arr reverse(Arr arr, int start, int end)
{
    int tmp = 0;
    for(; start < end; ++start, --end)
    {
        tmp = arr[end];
        arr[end] = arr[start];
        arr[start] = tmp;
    }

    return arr;
}

Arr leftShift(Arr arr, int len, int k)
{
    k %= len;

    arr = reverse(arr, 0, k - 1);
    arr = reverse(arr, k, len - 1);
    arr = reverse(arr, 0, len - 1);

    return arr;
}

Arr rightShift(Arr arr, int len, int k)
{
    k = k%len;
    k = len - k;

    arr = reverse(arr, 0, k - 1);
    arr = reverse(arr, k, len - 1);
    arr = reverse(arr, 0, len - 1);

    return arr;
}

Arr leftShift0(Arr arr, int len, int k)
{
    if(1 >= len || 0 >= k)
    {
        return arr;
    }

    int n = len;
    int i = 1;
    int p = 0, q = 0, r = 0;
    int d = arr[r];
    
    k %= len;
    while(n--)
    {
        q = p;
        p = p + k;
        p %= len;

        if(r == p)
        {
            arr[q] = d;
            r = k - i;
            p = r;
            d = arr[r];
            ++i;

            continue;
        }

        arr[q] = arr[p];
    }
    
    return arr;
}

Arr rightShift0(Arr arr, int len, int k)
{
    if(1 >= len || 0 >= k)
    {
        return arr;
    }

    int n = len;
    int i = 1;
    int p = 0, q = 0, r = 0;
    int d = arr[r];
    
    k %= len;
    while(n--)
    {
        q = p;
        p = p + len - k;
        p %= len;

        if(r == p)
        {
            arr[q] = d;
            r = k - i;
            p = r;
            d = arr[r];
            ++i;

            continue;
        }

        arr[q] = arr[p];
    }

    printf("i = %d\n", i);
    
    return arr;
}

void print_arr(Arr arr, int len)
{
    printf("arrP: \n");

    if(0 == len)
    {
        return;
    }

    int i = 0;
    for(; i < len; ++i)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6};
    int len = sizeof(arr) / sizeof(int);
    print_arr(arr, len);

    rightShift0(arr, len, 3);
    print_arr(arr, len);

    leftShift0(arr, len, 4);
    print_arr(arr, len);

    return 0;
}
