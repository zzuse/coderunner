#include <stdio.h>

int compare(s1, s2) char *s1, *s2;
{
    while (*s1++ == *s2)
    {
        if (*s2++ == 0)
            return (0);
    }
    return (*--s1 - *s2);
}

int main()
{
    char a[] = "abc";
    char b[] = "abd";
    printf("a - b = %d", compare(a, b));
    return 0;
}