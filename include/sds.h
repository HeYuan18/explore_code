#ifndef _SDS_H_
#define _SDS_H_

#define eachlen 32

typedef struct sdshdr{
    int free;
    int len;
    char buf[0];
}sds;

sds* sdsnew(const char *init);
sds* sdsempty(void);
sds* sdsdup(const sds *src);
sds* sdscat(sds **dst, const char *src);
sds* sdscatsds(sds **dst, const sds *src);
sds* sdscpy(sds **src, const char *t);
sds* sdscpysds(sds **dst, const sds *src);
void sdsinfo(const sds *src);
void sdsclear(sds **src);
sds* sdsfree(sds **src);
static sds* sdsnewlen(const char *init, int initlen);
static sds* sdsnewstdin(void);
static sds* sdscatlen(sds **dst, const char *t, int len);
static sds* sdscpylen(sds **dst, const char *t, int len);
static void sdsmakeroomfor(sds **src, int addlen);

#endif
