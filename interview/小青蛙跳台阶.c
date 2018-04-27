/*************************************************************************
	> File Name: 小青蛙跳台阶.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月27日 星期五 21时03分03秒
 ************************************************************************/

#include<stdio.h>

/*小青蛙可以一次跳一个台阶也可以跳两个台阶，但小青蛙太年轻，不能连续跳两个台阶 F(n) = F(n - 1) + F(n - 3)*/
int jumpA(int num)
{
    int base[4] = {0, 1, 2, 3};
    if(3 >= num)
    {
        return base[num];
    }
    
    int p = 1;
    int t = 2;
    int q = 3;
    int r = 0;
    int i = 4;
    for(; i <= num; ++i)
    {
        r = p + q;
        p = t;
        t = q;
        q = r;
    }

    return r;
}

int jump(int num)   
{
    if(3 >= num)
    {
        return num;
    }

    return jump(num - 1) + jump(num - 3);
}

/*小青蛙可以一次跳一个台阶也可以跳两个台阶 F(n) = F(n - 1) + F(n - 2)*/
int jump1A(int num)
{
    int base[3] = {0, 1, 2};
    if(2 >= num)
    {
        return base[num];
    }

    int p = 1;
    int q = 2;
    int r = 0;
    int i = 3;
    for(; i <= num; ++i)
    {
        r = p + q;
        p = q;
        q = r;
    }
    
    return r;
}

int jump1(int num)   
{
    if(2 >= num)
    {
        return num;
    }

    return jump1(num - 1) + jump1(num - 2);
}

/*小青蛙可以一次跳一个台阶也可以跳两个台阶,还可以一次跳n个台阶 F(n) = 2 * F(n - 1)*/
int jump2A(int num)
{
    int base[2] = {0, 1};
    if(1 >= num)
    {
        return base[num];
    }

    int p = 1;
    int r = 0;
    int i = 2;
    for(; i < num; ++i)
    {
        r = 2 * p;
        p = r;
    }

    return r;
}

int jump2(int num)   
{
    if(2 >= num)
    {
        return num;
    }

    return 2 * jump2(num - 1);
}

int main()
{
    int n = 1;
    while(n)
    {
        printf("台阶数: ");
        scanf("%d", &n);

        printf("跳数: %d\n", jumpA(n));
    }

    return 0;
}
