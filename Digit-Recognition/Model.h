#pragma once
#include "Global.h"
#include <vector>
#include <sstream>
#include <iterator>
#include <Windows.h>
#include "Layer.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "Data.h"

class Model
{
public:
	Model() {};
	Model(vector<int>);
	Model(string);
	~Model() {};

	Minibatch* batch;
	vector<Layer*> layers;

	void train(unsigned int, bool output = false);
	void saveToFile();
};

