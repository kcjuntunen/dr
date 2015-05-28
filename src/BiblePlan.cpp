/*
 * BiblePlan.cpp
 *
 *  Created on: May 26, 2015
 *      Author: kcjuntunen
 */

#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ptree_serialization.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>
#include <streambuf>
#include <cerrno>
#include <time.h>

#include "BiblePlan.h"

int _arraySize;

BiblePlan::BiblePlan(std::string filename) {
	// TODO Auto-generated constructor stub
	jsonFile = filename;
	_arraySize = 0;
	this->initialize();
}

BiblePlan::~BiblePlan() {
	// TODO Auto-generated destructor stub
}

std::string jsonFile;
std::string fileContents;
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
	std::string * s;
	// http://stackoverflow.com/questions/17124652/how-can-i-parse-json-arrays-with-c-boost
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


