#include <stdio.h>

int main(int argc, char *argv[]) {
	char *src="\"sql\":\"show databases;\"";
	
	char *var = strchr(src, ':');
		printf("%s\n",src);
		printf("%s\n",var+1);
}