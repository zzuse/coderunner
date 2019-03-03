#include <stdio.h>

int array[] = { 23, 24, 12, 17, 204, 99, 16 };
#define TOTAL_ELEMENTS (sizeof(array) / sizeof(array[0]))

int main(int argc, char* argv[])
{
    if (-1 < (unsigned char)1)
        printf("-1 is less than (unsigned char) 1, ANSI\n");
    else
        printf("-1 Not less than (unsigned char) 1, K&R\n");

    int d = -1, x;
    // when compare with unsigned int, d is promoted
    if (d <= TOTAL_ELEMENTS - 2) {
        // if (d <= (int)TOTAL_ELEMENTS - 2) { //correct
        x = array[d + 1];
        printf("true\n");
    }
}