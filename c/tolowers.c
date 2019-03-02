#include <stdio.h>

char *tolowers(char *src, char *dest)
{
    /*ignore case */
    char *str = dest;
    int len = 0;
    while (*src)
    {
        if (*src >= 'A' && *src <= 'Z')
        {
            *dest = *src | 0x20;
        }
        else
        {
            *dest = *src;
        }
        src++;
        dest++;
        len++;
    }
    dest[len] = 0;
    return str;
}

int main(int argc, char *argv[])
{
    char a[100] = "AbcdefG";
    char b[100] = "";
    printf("%s -len %d", tolowers(a, b), strlen(b));
}
