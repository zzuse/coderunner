#include <stdio.h>

int Add(int x, int y) {
	int sum;
	sum = x + y;
	return sum;
}

void main() {
	int z;
	z = Add(1, 2);
	printf("z=%d\n", z);
}
