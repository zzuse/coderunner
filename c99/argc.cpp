#include <stdio.h>

void call_arg(int,char**);

int main() {
	int argc=1;
	char *argv[1];
	char hello[6]="hello";
	argv[0]=hello;
	call_arg(argc, argv);
}

void call_arg(int argc,char** argv)
{
	printf("%d",argc);
	printf("%s",argv[0]);

}
