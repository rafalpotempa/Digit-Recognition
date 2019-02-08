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

	vector<vector<double>> w; //synaptic weights matrix
	vector<vector<double>> S; //leading matrix
	vector<vector<double>> Z; //output matrix

	vector<vector<double>> F; //derivative values matrix
	vector<vector<double>> D; //error signals matrix
	
	Layer();
	~Layer();

	void sigmoid();
	void forward();
	void backward();
};

