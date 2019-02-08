#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Digit.h"
#include "Global.h"

class Data {
	ifstream imagesFile;
	ifstream labelsFile;
	char temp;

	Digit digit;

public: //!!!!
	vector<vector<vector<ubyte>>> images;
	vector<ubyte> labels;
	
	//!!!!
	~Data();

	void readMnist();
	Digit& operator[](int);
};
