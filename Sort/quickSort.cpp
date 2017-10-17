#include <iostream>

using namespace std;
void quickSort(int s[], int l, int r)  
{  
    if (l< r)  
    {        
        int i = l, j = r, x = s[l];  
        while (i < j)  
        {  
            while(i < j && s[j]>= x) // 从右向左找第一个小于x的数  
                j--;   
            if(i < j)  
                s[i++] = s[j];  
            while(i < j && s[i]< x) // 从左向右找第一个大于等于x的数  
                i++;   
            if(i < j)  
                s[j--] = s[i];  
        }  
        s[i] = x; //基准数放好
        quickSort(s, l, i - 1); //比基准数小
        quickSort(s, i + 1, r); //比基准数大
    }  
}
int main(int argc, char *argv[]) {
    int array[6]={5,2,4,6,1,3};
    int first = 0;
    int last = 5;
    quickSort(array,0,5);
    cout<<array[0]<<array[1]<<array[2]
        <<array[3]<<array[4]<<array[5];
}