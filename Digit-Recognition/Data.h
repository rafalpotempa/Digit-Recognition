#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Digit.h"
#include "Global.h"

class Data {
public:
	Digit digit;
	vector<vector<vector<ubyte>>> images;
	vector<ubyte> labels;
	
	Data() {};
	~Data();

	void readMnist();
	Digit& operator[](int);
};
