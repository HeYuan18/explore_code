/*************************************************************************
	> File Name: 连续子数组的最大和.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月11日 星期三 20时01分56秒
 ************************************************************************/

#include<stdio.h>

#define bool int
#define false 0
#define true  1

bool g_invalidInput = false;

int findGreatstSumOfsubArray(int const* pArr, int len)
{
    if(NULL == pArr || 0 == len)
    {
        g_invalidInput = true;

        return 0;
    }

    int curSum = 0, maxSum = 0;
    int i = 0;
    for(; i < len; ++i)
    {
        if(curSum <= 0)
        {
            curSum = pArr[i];
        }
        else
        {
            curSum += pArr[i];
        }

        if(curSum > maxSum)
        {
            maxSum = curSum;
        }
    }

    return maxSum;
}

void Test(int* const pArr, int len)
{
    int result = findGreatstSumOfsubArray(pArr, len);
    if(true != g_invalidInput)
    {
        printf("连续子数组的最大和是: %d\n", result);
    }
    else
    {
        printf("InvalidInpunt\n");
    }
}

int main()
{
    int arr[] = {1, -2, 3, 10, -4, 7, 2, -5};
    int len = sizeof(arr) / sizeof(int);

    Test(arr, len);

    return 0;
}
