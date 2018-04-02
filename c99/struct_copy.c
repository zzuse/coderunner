#include <stdio.h>

struct s_tag {int a[100];};
struct s_tag orange, lime, lemon;
struct s_tag deepcopyOrNot(struct s_tag s) {
	int j;
	for (j=0;j<100;j++) s.a[j] *= 2;
	return s;
}

int show_struct(struct s_tag s) {
	int j;
	printf("-----------------\n");
	printf("%p\n",&s);
	for (j=0;j<100;j++) printf("%d ",s.a[j]);
	printf("\n");

	return 0;
}

int main(int argc, char *argv[]) {
	int i;
	for (i=0;i<100;i++) lime.a[i]=1;
	
	lemon = deepcopyOrNot(lime);
	orange = lemon;
	printf("%p\n",&lime);
	printf("%p\n",&lemon);
	printf("%p\n",&orange);

	show_struct(lime);
	show_struct(lemon);
	show_struct(orange);
}

