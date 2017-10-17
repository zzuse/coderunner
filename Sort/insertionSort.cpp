#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
    
    int array[6]={5,2,4,6,1,3};
    int first = 0;
    int last = 5;
    for(int i=first+1;i<=last;i++)//n-1此扫描，依次向前插入n-1个元素
    {
        int temp=array[i];//每趟将a[i]插入到前面的已排序子序列中 
        int j=i-1;
        while((j>=first)&&(array[j]>temp))
        {
            array[j+1]=array[j];//将前面较大的元素向后移动
            j--;//插入位置减一
        }
        array[j+1]=temp;//temp值到达插入位置
    }
    cout<<array[0]<<array[1]<<array[2]
        <<array[3]<<array[4]<<array[5];
}