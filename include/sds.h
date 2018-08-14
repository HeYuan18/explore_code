#ifndef _SDS_H_
#define _SDS_H_

#define eachlen 8

typedef struct sdshdr{
    int free;
    int len;
    char buf[0];
}sds;

sds* sdsnew(const char *init);
sds* sdsempty(void);
sds* sdsdup(const sds *src);
void sdsinfo(const sds *src);
void sdsclear(sds **src);
sds* sdsfree(sds **src);
static sds* sdsnewlen(const char *init, int initlen);
static sds* sdsnewstdin(void);

#endif
