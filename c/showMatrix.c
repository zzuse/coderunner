#include <stdio.h>

/*m row,n columns*/
int a[4][5] = {
	{1,2,3,4,5},
	{6,7,8,9,10},
	{11,12,13,14,15},
	{16,17,18,19,20},
	//{21,22,23,24,25}
};
int showMatrix(int m,int n);
int main(int argc, char *argv[]) {
	showMatrix(4,5);
}

int showMatrix(int m,int n) {
	int i=0,j=0,p=0,q=0;
	p=m-1;
	q=n-1;
	for(;p&&q;p--,q--,i++,j++) {
		while (j<q) {
			printf(" %d_[%d %d]",a[i][j],i,j);
			j++;
		}
		while (i<p) {
			printf(" %d_[%d %d]",a[i][j],i,j);
			i++;
		}
		while (j>m-p-1) {
			printf(" %d_[%d %d]",a[i][j],i,j);
			j--;
		}
		while (i>n-q-1) {
			printf(" %d_[%d %d]",a[i][j],i,j);
			i--;
		}
		if(i==p||j==q)printf(" %d_[%d %d]",a[i][j],i,j);
		printf("\n------p=%d q=%d i=%d j=%d------\n",p,q,i,j);
	}
}