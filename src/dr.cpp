//============================================================================
// Name        : dr.cpp
// Author      : K. C. Juntunen
// Version     :
// Copyright   : GNU GPL v2
// Description : daily_reading in C++
//============================================================================
#include <iostream>
#include "./BiblePlan.h"


using namespace std;
//using namespace boost::property_tree;

int main(int argc, char** argv) {
	string pathstring = argv[1];
	BiblePlan* bp = new BiblePlan(pathstring);

	string* res = bp->GetToday();

	for (int j = 0 ; j < bp->GetArraySize(); j++) {
		cout << j+1 << ": " << res[j] << endl;
	}

	delete bp;
	return 0;
}
