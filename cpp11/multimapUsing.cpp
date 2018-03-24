#include <iostream>
#include <map>

using namespace std;
int main(int argc, char *argv[]) {
	multimap<int, double, less<int> > pairs;
	
	cout << "There are currently " << pairs.count(15)
	<< " pairs with key 15 in the multimap\n";
	
	pairs.insert(make_pair(15, 2.7));
	pairs.insert(make_pair(15, 99.3));
	
	cout << "After inserts, there are " << pairs.count(15)
	<< " pairs with key 15 \n\n";
	
	pairs.insert(make_pair(30, 111.11));
	pairs.insert(make_pair(10, 22.22));
	pairs.insert(make_pair(25,33.333));
	pairs.insert(make_pair(20,9.345));
	pairs.insert(make_pair(5,77.54));
	
	cout << "Multimap pairs contains:\nKey\tValue\n";
	
	for(auto mapItem:pairs)
		cout << mapItem.first << '\t' << mapItem.second << '\n';
	
	cout << endl;
}