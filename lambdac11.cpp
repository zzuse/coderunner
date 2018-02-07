#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
    int x=2,y,z,i=1;
    auto show = [&](int j){cout<<++j*x<<endl;};
    x*=(y=z=3); show(i);
    cout<<i<<endl;
    x == (y=z); show(i);
    x = (y==z); show(i);
    x = (y&z);  show(i);
    x = (y&&z); show(i);
    y = 4;      show(i);
    x = (y|z);  show(i);
    x = (y||z); show(i);
}