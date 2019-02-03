#pragma once
#include <math.h>
#include <vector>
#include "Constants.h"

class Layer
{
	int rows;
	int cols;

	vector<vector<double>> w; //weights matrix
	vector<vector<double>> S; //computational matrix
	vector<vector<double>> Z; 


public:
	Layer(int, int);
	~Layer();

	void sigmoid();
};

