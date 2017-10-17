#include <stdio.h>
#include <string.h>

#define TS_PATH_DELIMITER '.'
int main(int argc, char *argv[]) {
	char name[7]="123";
	char tmp[2]="";
	sprintf(tmp,"%c",TS_PATH_DELIMITER);
	strcat(name, tmp);
	printf("%s",name);
}