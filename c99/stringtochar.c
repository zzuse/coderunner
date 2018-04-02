#include <stdio.h>
#include <string.h>
#define TS_PATH_DELIMITER "."

int main(int argc, char *argv[]) {
	char name[7]="123.3SSS";
	char* tmp;
	printf(tolower(name));
	printf(name);
	tmp = strstr(name,TS_PATH_DELIMITER);
	
	printf("%c",*tmp);
}