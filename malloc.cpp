#include <iostream>
#include <stdio.h>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[]) {
    while(1) {
        void*p = malloc(90000000L);
        if(p == 0) {
            printf("malloc failed.\n");
        }
        else{
            printf("malloc successful.\n");
        }
        sleep(0.01);
    }
    return 0;
}