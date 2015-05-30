/*
 * BiblePlan.cpp
 *
 *  Created on: May 26, 2015
 *      Author: kcjuntunen
 */
#include "BiblePlan.h"

int _arraySize;
std::string jsonFile;
std::string fileContents;
std::string * s;

BiblePlan::BiblePlan(std::string filename) {
	jsonFile = filename;
	_arraySize = 0;
	this->initialize();
}

BiblePlan::~BiblePlan() {
	delete [] s;
}

std::string GetJsonFile() {
	return jsonFile;
}

std::string BiblePlan::get_file_contents(const char *filename) {
	std::ifstream in(filename, std::ios::in | std::ios::binary);
	if (in)
	{
		return(std::string((std::istreambuf_iterator<char>(in)),
				std::istreambuf_iterator<char>()));
	}
	throw(errno);
}

void BiblePlan::initialize() {
	fileContents = get_file_contents(this->jsonFile.c_str());
}

std::string* BiblePlan::GetDay(int d) {
	boost::property_tree::ptree pt;
	std::istringstream is (fileContents);
	boost::property_tree::read_json(is, pt);
	int count = 0;

	BOOST_FOREACH(boost::property_tree::ptree::value_type &data,
			pt.get_child("data2")) {
		count++;
		if (count == d) {
			int j = 0;
			_arraySize = data.second.size();
			s = new std::string[_arraySize];
			BOOST_FOREACH(boost::property_tree::ptree::value_type &set,
					data.second) {
				s[j++] = set.second.get_value<std::string>();
			}
		}
	}

	return s;
}

int BiblePlan::GetDayOfYear() {
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);
	int yday = aTime->tm_yday + 1;
	return yday;
}

std::string* BiblePlan::GetToday() {
	return GetDay(GetDayOfYear());
}

int BiblePlan::GetArraySize() {
	return _arraySize;
}


