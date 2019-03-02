#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
	struct tm tm;

	time_t seconds;
	unsigned long useconds;
	memset(&tm, 0, sizeof(struct tm));
//	strptime("1970-01-01 00:00:00", "%Y-%m-%d %H:%M:%S", &tm);
	strptime("2017-09-07 00:00:01", "%Y-%m-%d %H:%M:%S", &tm);

	//printf("time_t %ld\n",sizeof(time_t));
	//printf("float %ld\n",sizeof(float));
	seconds = mktime(&tm);
	printf("%ld\n", seconds);

	float tmp=0.428;
	float temp=tmp*1000;
	useconds = (unsigned long)temp + seconds*1000;
	
	printf("%ld", useconds);

}