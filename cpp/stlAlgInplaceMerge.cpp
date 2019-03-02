#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <iterator>

using namespace std;
int main(int argc, char *argv[]) {
    const int SIZE = 10;
    array<int, SIZE> a1 = {1,3,5,7,9,1,3,5,7,9};
    ostream_iterator<int> output(cout, " ");
    
    cout << "array a1 contains: ";
    copy(a1.cbegin(), a1.cend(), output);
    cout << endl;
    
    inplace_merge(a1.begin(), a1.begin()+5, a1.end());
    cout << "after inplace_merge array a1 contains: ";
    copy(a1.cbegin(), a1.cend(), output);

    vector<int> results1;

    unique_copy(a1.cbegin(), a1.cend(), back_inserter(results1));
    cout << "\nAfter unique copy results1 contains: ";
    copy(results1.cbegin(), results1.cend(), output);
    
    vector<int> results2;
    
    reverse_copy(a1.cbegin(), a1.cend(), back_inserter(results2));
    cout << "\nAfter reverse copy, results2 contains: ";
    copy(results2.cbegin(),results2.cend(),output);
    cout << endl;
}