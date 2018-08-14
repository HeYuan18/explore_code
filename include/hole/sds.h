#ifndef _SDS_H_
#define _SDS_H_

#define SDS_LEN 9

/*简单动态字符串*/
typedef struct sds{
    int  len;   //字符串长度
    int  free;  //字符串空闲空间
    char *data; //字符串值
}SDS;

void initSDS(SDS *S);
void getSDS(SDS *S);
void printSDS(const SDS *S);
void clearSDS(SDS *S);
void freeSDS(SDS *S);

#endif
