/*************************************************************************
	> File Name: 数组循环移k位.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月23日 星期一 22时35分57秒
 ************************************************************************/

#include<stdio.h>

typedef int* Arr;

Arr reverse(Arr arr, int start, int end)
{
    for(; start < end; ++start, --end)
    {
        int s = arr[end];
        arr[end] = arr[start];
        arr[start] = s;
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

Arr rightShift0(Arr arr, int len, int k)
{
    if(1 >= len || 0 >= k)
    {
        return arr;
    }

    k = k % len;
    int i = len;
    int m = 0, p = 0;
    int q = arr[0], r = arr[k - 1];
    while(i--)
    {
        p = m;
        m = m + len - k;
        m %= len;
        
        if(0 == m)
        {
            arr[p] = q;
            m = k - 1;
            continue;
        }
        if((k - 1) == m)
        {
            arr[p] = r;
            continue;
        }

        arr[p] = arr[m];
    }

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
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int len = sizeof(arr) / sizeof(int);
    print_arr(arr, len);

    rightShift0(arr, len, 1);
    print_arr(arr, len);

    return 0;
}
