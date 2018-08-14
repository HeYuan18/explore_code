#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sds.h"

sds* sdsnew(const char *init)
{
    int initlen = (init == NULL) ? 0 : strlen(init);

    if(0 < initlen)
    {
       return sdsnewlen(init, initlen);
    }
    else
    {
        return sdsnewstdin();
    }
}

sds* sdsempty(void)
{
    return sdsnewlen("", 0);
}

sds* sdsdup(const sds *src)
{
    return sdsnewlen(src->buf, src->len);
}

void sdsinfo(const sds *src)
{
    printf("\nsdshdr info:\n");
    printf("free: %d, len: %d, size:%d\n", src->free, src->len, src->free + src->len);
    printf("buf: %s\n", src->buf);
}

void sdsclear(sds **src)
{
    (*src)->free += (*src)->len;
    (*src)->len = 0;
    (*src)->buf[0] = '\0';
}

sds* sdsfree(sds **src)
{
    if(NULL != (*src))
    {
        free((*src));
        (*src) = NULL;
    }
    
    return NULL;
}

static sds* sdsnewlen(const char *init, int initlen)
{
    sds *sh = NULL;
    sh = (sds*)malloc(sizeof(sds) + initlen + 1);
    if(NULL == sh)
    {
        printf("malloc sdsnewlen\n");
        exit(1);
    }
    memset(sh, 0, sizeof(sds) + initlen + 1);

    sh->free = 0;
    sh->len = initlen;
    memcpy(sh->buf, init, initlen);
    
    return sh;
}

static sds* sdsnewstdin(void)
{
    int rowflag = 0;
    char inbuf[eachlen];
    memset(inbuf, 0, eachlen);

    sds *sh = NULL;
    sh =  (sds*)malloc(sizeof(sds) + eachlen);
    if(NULL == sh)
    {
        printf("malloc sdsnewstdin\n");
        exit(1);
    }
    memset(sh, 0, sizeof(sds) + eachlen);

    sh->free = eachlen;
    sh->len = 0;

    while(fgets(inbuf, eachlen, stdin))  //每次从标准输入最多获取31个字符
    {
        if(sh->free <= (int)strlen(inbuf)) //空闲空间不够重新扩大空间
        {
            sh = (sds*)realloc(sh, sizeof(sds) + sh->free + sh->len + sizeof(char) * eachlen);
            if(NULL == sh)
            {
                printf("realloc sdsnewstdin\n");
                exit(1);
            }
            sh->free += eachlen;
        }

        if('\n' == inbuf[strlen(inbuf) - 1])
        {
            inbuf[strlen(inbuf) - 1] = '\0';
            rowflag = 1;
        }

        strncat(sh->buf, inbuf, (int)strlen(inbuf));
        sh->free -= strlen(inbuf);
        sh->len += strlen(inbuf);

        if(rowflag)
        {
            break;
        }
    }

    return sh;
}

int main()
{
    sds *x = sdsnew(NULL);

    sdsinfo(x);
    sdsfree(&x);

    return 0;
}

