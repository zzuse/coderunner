#include <stdlib.h>
#include <string.h>
int main()
{
	char buf[1024];
	strcpy(buf,"ps -ef|grep taosd|grep test|awk '{print $2}'|xargs echo");
	system(buf);
	return 0;
}