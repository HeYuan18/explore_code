/*************************************************************************
	> File Name: 数组循环左移k.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月23日 星期一 22时35分57秒
 ************************************************************************/

#include<stdio.h>

int* reverse(int* arr, int start, int end)
{
    for(; start < end; ++start, --end)
    {
        int s = arr[end];
        arr[end] = arr[start];
        arr[start] = s;
    }

    return arr;
}

int* rightShift(int* arr, int len, int k)
{
    k = k%len;

    arr = reverse(arr, 0, k - 1);
    arr = reverse(arr, k, len - 1);
    arr = reverse(arr, 0, len - 1);

    return arr;
}

void print_arr(int arr[], int len)
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

    rightShift(arr, len, 4);
    print_arr(arr, len);

    return 0;
}
