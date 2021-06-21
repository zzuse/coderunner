#include <iostream>

#define ALIGN_UP(x, a) ((x + a - 1) & (~(a - 1)))

int main() {
	printf("%x\n", 31);
	printf("%x\n", ~31);
	printf("%x\n", 62);
	std::cout << ALIGN_UP(31, 32) << std::endl;
	std::cout << ALIGN_UP(1920, 96) << std::endl;
}