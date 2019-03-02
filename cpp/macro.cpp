#include <iostream>

using namespace std;
void register_test_a(){ printf("register_test_a\n"); }
int main(int argc, char *argv[]) {
	const char* report="aaa";
	for (int next = 1; next < argc; ++next) {
		char* arg = argv[next];

#define CASE(name)                                 \
	else if (strstr(arg, "--" #name "=") == arg) { \
	  cout<<#name<<endl; \
	  name = arg + strlen(#name) + 3;             \
	  cout<<name<<endl; \
	}
	
#define REGTEST(name)          \
		void register_test_##name(); \
		register_test_##name()

			if (strstr(arg, "--help") == arg || strstr(arg, "-h") == arg) {
				exit(0);
			}
			if (strstr(arg, "-version") == arg || strstr(arg, "-v") == arg) {
				exit(0);
			}
			CASE(report)
			else {
				cout<<"haha";
			}
			REGTEST(a);
			cout<<"\r\033[K123";
			cout<<"\r\033[K123";
			cout<<"\r\033[K123";
		}
}