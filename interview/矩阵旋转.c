/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2018年03月29日 星期四 20时01分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int** init_matrix(int** matrix, int n)
{
    int i = 0, j = 0;
    matrix = (int**)malloc(n * sizeof(int*));
    for(; i < n; ++i)
    {
        matrix[i] = (int*)malloc(n * sizeof(int));
    }

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    return matrix;
}

int** rotate_matrix(int** matrix, int n)
{
    int i = 0, j = 0;
    int** tmp = (int**)malloc(n * sizeof(int*));
    for(; i < n; ++i)
    {
        tmp[i] = (int*)malloc(n * sizeof(int));
    }

    for(i = 0; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            tmp[n - 1 - j][n - 1 - i] = matrix[i][n - 1 - j];
        }
    }

    return tmp;
}

void print_matrix(int** matrix, int n)
{
    int i = 0, j = 0;
    for(; i < n; ++i)
    {
        for(j = 0; j < n; ++j)
        {
            printf("%d   ", matrix[i][j]);
        }
        printf("\n");
    }
}

int** destory_matrix(int** matrix, int n)
{
    int i = 0;
    for(; i < n; ++i)
    {
        free(matrix[i]);
        matrix[i] = NULL;
    }

    free(matrix);
    matrix = NULL;
}

int main()
{
    int **Matrix = NULL;
    int N = 0;
    scanf("%d\n", &N);

    Matrix = init_matrix(Matrix, N);
    Matrix = rotate_matrix(Matrix, N);
    print_matrix(Matrix, N);

    Matrix = destory_matrix(Matrix, N);
    
    return 0;
}
