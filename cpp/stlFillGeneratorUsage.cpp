#include <iostream>
#include <algorithm>
#include <array>
#include <iterator>

using namespace std;

char nextLetter();

int main(int argc, char *argv[]) {
    array<char, 10> chars;
    ostream_iterator<char> output(cout, " ");
    fill(chars.begin(), chars.end(), '5');
    
    cout << "chars after filling with 5s:\n";
    copy(chars.cbegin(), chars.cend(), output);
    
    fill_n(chars.begin(), 5, 'A');
    
    cout << "\n\nchars after filling five elements with As:\n";
    copy(chars.cbegin(), chars.cend(), output);
    
    generate(chars.begin(), chars.end(), nextLetter);
    
    cout << "\n\nchars after generating letters A-J:\n";
    copy(chars.cbegin(), chars.cend(), output);
    
    generate_n(chars.begin(), 5, nextLetter);
    cout << "\n\nchars after generating K-O for the " << " first five elements:\n";
    copy( chars.cbegin(), chars.cend(), output);
    cout << endl;
}

char nextLetter()
{
    static char letter ='A';
    return letter++;
}