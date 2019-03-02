#include <stdio.h>
#include <string.h>

char ga[] = "abcdef";
void char_array(char ca[])
{
	printf("%d %#x %#x %#x %#x \n", sizeof(ca), &ca, &(ca[0]), &(ca[1]), ++ca);
}

void pointer_of_char(char *pa)
{
	printf("%d %#x %#x %#x %#x \n", sizeof(pa), &pa, &(pa[0]), &(pa[1]), ++pa);
}

int main(int argc, char *argv[])
{
	char my_array[10] = "b";
	char *my_ptr = "aaa";
	int i = strlen(my_array);
	int j = strlen(my_ptr);
	printf("%s %s\n", my_array, my_ptr);
	printf("array location %x holds string %s\n", my_ptr, my_ptr);
	char_array(ga);
	pointer_of_char(ga);
	printf("%d %#x %#x %#x\n", sizeof(ga), &ga, &(ga[0]), &(ga[1]));
	int app[2][3][5] = {
		{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}},
		{{16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}, {26, 27, 28, 29, 30}}};
	int(*p)[3][5] = app;
	int(*r)[5] = app[0];
	int *t = app[0][0];
	printf("sizeof app array %d\n", sizeof(app));
	while ((***p) > 0)
		printf("p %#x %#x %#x %d\n", app, p, ++p, ***p);
	while ((**r) > 0)
		printf("r %#x %#x %#x %d\n", app, r, ++r, **r);
	while ((*t) > 0)
		printf("t %#x %#x %#x %d\n", app, t, ++t, *t);
}