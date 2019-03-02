#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

void banana() {
	printf("in banana()\n");
	longjmp(buf,1);
	/*not reached*/
	printf("you'll never see this\n");
}

int main(int argc, char const* argv[])
{
	if (setjmp(buf)) {
		printf("back in main\n");
	} else {
		printf("first time through\n");
		banana();
	}
	return 0;
}
