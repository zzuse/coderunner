//g++ b.cpp -c -o b.o
//g++ a.o b.o -o run
//readelf -S run
//readelf --segments run
//objdump -d run |grep -A2 -B3 _Z|c++filt
#include <stdio.h>

int f(int, int);
int main()
{
	int a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n", f(a, b));
}
