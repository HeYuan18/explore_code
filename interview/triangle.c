/*************************************************************************
	> File Name: triangle.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月08日 星期日 22时03分27秒
 ************************************************************************/

#include<stdio.h>
#include<cstl/cvector.h>

#define max 1000000

vector_t* fibonacci(vector_t* v, int len)
{
    v = create_vector(int);
    if(NULL == v)
    {
        return NULL;
    }

    vector_init(v);
    vector_push_back(v, 1);
    vector_push_back(v, 2);
    int l = 0, f = 2;
    while(f < len)
    {
        l = vector_size(v);
        vector_push_back(v, (*(int*)vector_at(v, l - 1) + *(int*)vector_at(v, l - 2)));
        ++f;
    }

    return v;
}

int main()
{
    vector_t* arr = fibonacci(arr, max);
    if(NULL == arr)
    {
        return -1;
    }
    
    int n = 0, ans = 0, i = 1;
    scanf("%d", &n);

    if(n > max)
    {
        return -1;
    }
    
    for(; i <= n; ++i)
    {
        if(*(int*)vector_at(arr, i - 1)  <= n)
        {
            ++ans;
        }
        else
        {
            break;
        }
    }

    printf("%d\n", n - ans);

    return 0;
}
