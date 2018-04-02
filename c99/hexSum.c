#include <stdio.h>

int calculateHexNumber(double input){
	int count=0;
	unsigned int number=(unsigned int)input;
	if(number&1) count++;
	while(number = number >> 1) {
		count = (number & 1) + count;
	}
	return count;
}

int main(int argc, char *argv[]) {
	double number=0xffffff;
	printf("%d\n",calculateHexNumber(number));
}