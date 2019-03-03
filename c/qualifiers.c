#include <stdio.h>

void foo(const char** p) {}

int main(int argc, char* argv[])
{
    // argument passing behave like assignment
    // 左边的修饰词拥有所有右边的修饰
    foo(argv);
    char* cp;
    const char* ccp;
    ccp = cp;
    //	cp = ccp; // warinig
    const int limit = 10;
    // 指针指向的值是只读的，但是指针本身可以指向不同的变量
    const int* limitp = &limit;
    int i = 27;
    limitp = &i;

    return 0;
}