#include <iostream>
#include <queue>

using namespace std;
int main(int argc, char *argv[]) {
	priority_queue<double> priorities;
	priorities.push(3.2);
	priorities.push(9.8);
	priorities.push(5.4);
	
	cout << "Popping from priorities: ";
	
	while (!priorities.empty()) {
		cout << priorities.top() << ' ';
		priorities.pop();
	}
	cout << endl;
}