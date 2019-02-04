#pragma once
#include <math.h>
#include <vector>
#include "Constants.h"

class Layer
{
public:
	int inputs = 0;
	int neurons = 0;
	int outputs = 0;

	Layer* nextLayer;

	vector<vector<double>> w; //forward weights matrix
	vector<double> S; //leading matrix
	vector<double> Z; //output matrix

	Layer();
	~Layer();

	void sigmoid();
};

