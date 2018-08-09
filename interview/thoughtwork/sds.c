#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sds.h"

void initSDS(SDS *S)
{
    S->free = SDS_LEN;
    S->len = 0;
    S->data = NULL;

    S->data = (char*)malloc(sizeof(char) * S->free);
    if(NULL == S->data)
    {
        perror("malloc_sds");
        exit(1);
    }
}

void getSDS(SDS *S)
{
    char buf[SDS_LEN];
    while(fgets(buf, SDS_LEN, stdin))
    {
        if(S->free <= (int)strlen(buf))
        {
            S->data = (char*)realloc(S->data, S->free + S->len + sizeof(char) * SDS_LEN);
            if(NULL == S->data)
            {
                perror("realloc_sds");
                exit(1);
            }
            S->free += SDS_LEN;
        }

        strncat(S->data, buf, (int)strlen(buf));
        S->free -= strlen(buf);
        S->len += strlen(buf);

        if('\n' == buf[strlen(buf) - 1])
        {
            break;
        }
    }
}

void printSDS(const SDS *S)
{
    printf("size: %d, len: %d\n", S->free + S->len, S->len);
    puts(S->data);
}

void freeSDS(SDS *S)
{
    S->len = 0;
    S->free = SDS_LEN;
    free(S->data);
    S->data = NULL;
}
