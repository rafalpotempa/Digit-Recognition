#pragma once
#include <vector>
#include <fstream>
#include <math.h>
#include "Global.h"

class Layer
{
public:
	int inputs = 0;
	int neurons = 0;
	int outputs = 0;

	Layer* nextLayer;
	Layer* previousLayer;

	vector<vector<double>> w; //forward weights matrix
	vector<double> S; //leading matrix
	vector<double> Z; //output matrix

	Layer();
	~Layer();

	void sigmoid();
};

