/*************************************************************************
	> File Name: test.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年04月09日 星期一 20时34分09秒
 ************************************************************************/

#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN=1024;
int temp[MAXN][MAXN];

//先求s的反串reverse，然后求他们的最长的公共子序列，要删除的字符个数就能知道
//时间复杂度O(N^2)

int getRemoveNumber(string &s1)
{
    string s2(s1);
    reverse(s2.begin(),s2.end());
    int len=s1.length();
    memset(temp,0,sizeof temp);
    for(int i=0;i<len;++i)
    {
        for(int j=0;j<len;++j)
        {
            if(s1[i]==s2[j])
                temp[i+1][j+1]=temp[i][j]+1;
            else temp[i+1][j+1]=max(temp[i][j+1],temp[i+1][j]);
        }
    }
    return len-temp[len][len];
}

int main()
{
   string s;
   while(cin>>s)
   {
       cout<<getRemoveNumber(s)<<endl;
   }
   return 0;
}
