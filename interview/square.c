/*************************************************************************
	> File Name: square.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月23日 星期五 21时26分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define eps 1e-8
#define MAX 100000
#define elem_type float

void print_arr(elem_type** const arr, int row)
{
    printf("Print:\n");
    int i = 0, j = 0;
    for(; i < row; ++i)
    {
        for(j = 0; j < 4; ++j)
        {
            printf("%0.2f\t", arr[i][j]);
        }
        printf("\n");
    }
}

int equals(elem_type l, elem_type r)
{
    elem_type c = fabs(l - r);

    return (c < eps);
}

/*计算斜率*/
int get_k(elem_type l, elem_type r)
{
    if(equals(0, l) && equals(0, r))
    {
        return MAX;
    }
    if(equals(0, l) || equals(0, r))
    {
        return 0;
    }

    return (l / r);
}

int is_square(elem_type** const arr, int row)
{
    int i = 0;
    elem_type a = 0, b = 0, c = 0, d = 0, k = 0, kk = 0;
    
    for(; i < 3; ++i)
    {
        a = (arr[1 + row][1 + i] - arr[1 + row][0]);
        b = (arr[row][1 + i] - arr[row][0]);
        switch(i)
        {
            case 0:
                c = (arr[1 + row][3] - arr[1 + row][2]);
                d = (arr[row][3] - arr[row][2]);
                break;
            case 1:
                c = (arr[1 + row][3] - arr[1 + row][1]);
                d = (arr[row][3] - arr[row][1]);
                break;
            case 2:
                c = (arr[1 + row][2] - arr[1 + row][1]);
                d = (arr[row][2] - arr[row][1]);
                break;
        }
        k = get_k(a, b);
        kk = get_k(c, d);
        if(equals(MAX, k) || equals(MAX, kk))
        {
            continue;
        }

        if(equals(-1, (k * kk)))       //垂直--->垂直先于平行判断
        {
            if(equals((pow(a, 2) + pow(b, 2)), (pow(c, 2) + pow(d, 2))))   //对角线相等
            {
                printf("YES\n");
                
                return 1;
            }
        }
        if(equals(k, kk) || equals(k, -kk))       //平行
        {
            continue;
        }
    }
    printf("NO\n");

    return 0;
}

void part_arr(elem_type** const arr, int count)
{
    int i = 0;

    printf("Result:\n");
    for(; i < count; ++i)
    {
        is_square(arr, 2 * i);
    }
}

elem_type** create_arr(elem_type** arr, int row)
{
    int i = 0, j = 0;

    arr = (elem_type**)malloc(sizeof(elem_type*) * row);
    if(NULL == arr)
    {
        printf("err:arr_malloc\n");

        return NULL;
    }

    for(; i < row; ++i)
    {
        arr[i] = (elem_type*)malloc(sizeof(elem_type) * 4);
        if(NULL == arr[i])
        {
            printf("err:arr_malloc\n");

            return NULL;
        }
    }
    
    for(i = 0; i < row; ++i)
    {
        for(j = 0; j < 4; ++j)
        {
            scanf("%f", &arr[i][j]);
        }
    }

    return arr;
}

elem_type** free_arr(elem_type **arr, int row)
{
    int i = 0;
    for(; i < row; ++i)
    {
        free(arr[i]);
        arr[i] = NULL;
    }

    free(arr);
    arr = NULL;

    return arr;
}

int main()
{
    int count = 0;
    scanf("%d", &count);
    if(1 > count || count > 5)
    {
        printf("err: count is 1~5\n");
        exit(-1);
    }

    elem_type** arr = create_arr(arr, 2 * count);
    if(NULL != arr)
    {
        part_arr(arr, count);
        free_arr(arr, 2 * count);
    }

    return 0;
}
