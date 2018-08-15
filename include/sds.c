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

sds* sdscat(sds **dst, const char *src)
{
    int catlen = strlen(src);
    if((*dst)->free <= catlen)
    {
        sdsmakeroomfor(dst, catlen);
    }
    return sdscatlen(dst, src, catlen);
}

sds* sdscatsds(sds **dst, const sds *src)
{
    int catlen = strlen(src->buf);
    if((*dst)->free <= catlen)
    {
        sdsmakeroomfor(dst, catlen);
    }
    return sdscatlen(dst, src->buf, catlen);
}

sds* sdscpy(sds **dst, const char *src)
{
    int cpylen = strlen(src);
    if(((*dst)->free + (*dst)->len) <= cpylen)
    {
        sdsmakeroomfor(dst, cpylen);
    }
    return sdscpylen(dst, src, cpylen);
}

sds* sdscpysds(sds **dst, const sds *src)
{
    int cpylen = strlen(src->buf);
    if(((*dst)->free + (*dst)->len) <= cpylen)
    {
        sdsmakeroomfor(dst, cpylen);
    }
    return sdscpylen(dst, src->buf, cpylen);
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
    int addlen = ((initlen / eachlen) + 1) * eachlen;

    sds *sh = NULL;
    sh = (sds*)malloc(sizeof(sds) + addlen);
    if(NULL == sh)
    {
        printf("malloc sdsnewlen\n");
        exit(1);
    }
    memset(sh, 0, sizeof(sds) + addlen);

    sh->free = addlen - initlen;
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
            sdsmakeroomfor(&sh, eachlen - 1);
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

static sds* sdscatlen(sds **dst, const char *t, int len)
{
    (*dst)->free -= len;
    (*dst)->len += len;
    strncat((*dst)->buf, t, len);

    return *dst;
}

static sds* sdscpylen(sds **dst, const char *t, int len)
{
    (*dst)->free += (*dst)->len;
    (*dst)->len = 0;

    strncpy((*dst)->buf, t, len);

    (*dst)->free -= len;
    (*dst)->len += len;

    return *dst;
}

static void sdsmakeroomfor(sds **src, int addlen)
{
    addlen = ((addlen / eachlen) + 1) * eachlen;

    (*src) = (sds*)realloc((*src), sizeof(sds) + (*src)->free + (*src)->len + sizeof(char) * addlen);
    if(NULL == (*src))
    {
        printf("realloc sdsmakeroomfor\n");
        exit(1);
    }

    memset((*src)->buf + (*src)->len, 0 , addlen);

    (*src)->free += addlen;
}

int main()
{
    sds *u = sdsempty();
    sds *x = sdsnew("I ");
    sds *y = sdsnew("live ");
    sds *z = sdsnew("in China.");


    sdscatsds(&x, sdscatsds(&y, z));
    sdscpysds(&u, x);

    sdsinfo(x);
    sdsinfo(u);

    sdsfree(&u);
    sdsfree(&x);
    sdsfree(&y);
    sdsfree(&z);

    return 0;
}

