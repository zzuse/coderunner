#include <iostream>
#include "csv.hpp"

using namespace std;
using namespace csv;
int main(int argc, char *argv[]) {
	CSVReader reader("query_1w.csv");

//	for (CSVRow& row: reader) { 
//		for (CSVField& field: row) {
//			std::cout << field.get<>() << std::endl;
//		}
//	}
	for (auto row: reader) { 
		std::cout << row["filePath"].get<>() << std::endl;
	}
}