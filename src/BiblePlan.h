/*
 * BiblePlan.h
 *
 *  Created on: May 26, 2015
 *      Author: kcjuntunen
 */

#ifndef BIBLEPLAN_H_
#define BIBLEPLAN_H_

class BiblePlan {
public:
	BiblePlan(std::string filename);
	virtual ~BiblePlan();

	std::string GetJsonFile();
	std::string* GetDay(int d);
	std::string* GetToday();
	int GetArraySize();
private:
	int GetDayOfYear();
	std::string jsonFile;
	std::string fileContents;
	void initialize();
	std::string get_file_contents(const char *filename);
	int _arraySize;
};


#endif /* BIBLEPLAN_H_ */
