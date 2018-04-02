#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
	int Mb=0;
	while (malloc(1<<20)) {
		++Mb;
	}
	printf("Allocated %d Mb total\n",Mb);
}