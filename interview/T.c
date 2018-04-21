/*************************************************************************
	> File Name: T.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月15日 星期日 10时09分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int** matrix;

void print_matrix(matrix m, int row)
{
    printf("print_matrix:\n");
    int i = 0, j = 0, col = 0;
    for(; i < row; ++i)
    {
        col = m[i][0];
        for(j = 1; j <= col; ++j)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

matrix init_matrix(matrix m, int len)
{
    int i = 0, j = 0, col = 0;
    m = (matrix)malloc(sizeof(int*) * len);
    if(NULL == m)
    {
        return NULL;
    }
    for(; i < len; ++i)
    {
        scanf("%d", &col);

        if(col <= 0)
        {
            return 0;
        }
        m[i] = (int*)malloc(sizeof(int) * (col + 1));
        if(NULL == m[i])
        {
            return NULL;
        }
        m[i][0] = col;
        for(j = 1; j <= col; ++j)
        {
            scanf("%d", &m[i][j]);
        }
    }

    return m;
}

int isExist(int* x, int E)  //改进为二分搜索
{
    int i = 1;
    for(; i <= x[0]; ++i)
    {
        if(E == x[i])
        {
            return 1;
        }
    }

    return 0;
}

int isT(int* x, int T)
{
    int isTrue = 1, i = 1;
    int col = x[0];
    int A1 = x[1], A2 = x[x[0]];

    for(; i <= col; ++i)
    {
        if(x[i] - T >= A1)
        {
            if(!isExist(x, x[i] - T))
            {
                isTrue = 0;
            }
        }
        
        if(x[i] + T <= A2)
        {
            if(!isExist(x, x[i] + T))
            {
                isTrue = 0;
            }
        }

        if(!isTrue)
        {
            break;
        }
    }

    return isTrue;
}

void getT(matrix m, int row)
{
    int T = 0;
    int i = 0;
    for(; i < row; ++i)
    {
        while(T <= (m[i][1] - m[i][m[i][0]]))   //T∈[1, An - A1]
        {
            ++T;
            if(isT(m[i], T))
            {
                printf("%d\n", T);
                break;
            }
        }
        T = 0;
    }
}

matrix destroy_matrix(matrix m, int row)
{
    int i = 0;
    for(; i < row; ++i)
    {
        free(m[i]);
    }
    free(m);

    m = NULL;

    return m;
}

int main()
{
    int n =  0;
    scanf("%d", &n);
    if(n <= 0)
    {
        return 0;
    }

    matrix M = NULL;
    M = init_matrix(M, n);
    if(NULL == M)
    {
        return 0;
    }

    print_matrix(M, n);
    getT(M, n);
    destroy_matrix(M, n);

    return 0;
}
