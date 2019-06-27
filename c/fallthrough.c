#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	char * a = "NUL";
	char * b = NULL;
	char * c = "NULLL";
	const int two =2;

	for (int i = 0; i < 100; i++) {
		switch (i) {
			case 1: printf("1\n");
			case two: printf("2\n");
			case 5+3: printf("8\n");
			default:;
		}
	}
	int line = 1;
	int y = 3;
	switch (line) {
		case 0:
			printf("0\n");
			break;
		case 1:
			if(two == 2) {
				printf("2\n");
				if (y == 3)
					break;
				printf("2 again\n");
			}
			printf("init\n");
			break;
		default:
			printf("done\n");
	}
	printf("deinit\n");
	
	printf("book \
is a cat, \
gun\n");
	printf("second book "
	"is naughty "
	"valve\n");
	char* available[] = {
		"color",
		"disk",
		"cray "
		"mouse",
	};
	printf("%s\n",available[2]);
	printf("%c\n",*available[2]);
	printf("sizeof *available[2] is %ld\n", sizeof(*available[2]));
	int p = 10 * sizeof * available[2];
	printf("p is %d\n", p);
	char* r = malloc(p);
	int apple = sizeof (int) * p;
	printf("apple i %d\n", apple);
	printf("%d %s\n", argc, argv[argc-1]);
	int m, n;
	m = 3;
	n = 2;
	int *q = &m;
	int *s = &n;
	int o = *q/ *s; // space matters
	o = m++ + ++n; // space matters
	printf("%d\n", o);
	o = m+++n;
	printf("%d, %d, %d\n", o,m,n);
}