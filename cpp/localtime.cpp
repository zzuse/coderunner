
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <stdio.h>
using namespace std;

int main(int argc, char *argv[])

{
    time_t tNow =time(NULL);
    time_t tEnd = tNow + 2500;
    //在这里修改程序,不可重入
    struct tm* ptm = localtime(&tNow);
    struct tm* ptmEnd = localtime(&tEnd);
    //在这里修改程序,可重入
    /*struct tm* ptm = new struct tm[sizeof(struct tm)];
    struct tm* ptmEnd = new struct tm[sizeof(struct tm)];
    localtime_r(&tNow, ptm);
    localtime_r(&tEnd, ptmEnd);*/
    
    char szTmp[50] = {0};
    strftime(szTmp,50,"%H:%M:%S",ptm);
    char szEnd[50] = {0};
    strftime(szEnd,50,"%H:%M:%S",ptmEnd);
    printf("%s \n",szTmp);
    printf("%s \n",szEnd);
    
    int diff=difftime(tEnd,tNow);
    printf("%d \n",diff);

    time_t biggest=0x7FFFFFFFF;
    //ctime is localtime
    printf("%s \n",ctime(&biggest));
    printf("%s \n",asctime(gmtime(&biggest)));
    

    return 0;
}