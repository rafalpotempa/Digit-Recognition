#pragma once
#include <vector>
#include "Global.h"
#include "Layer.h"
#include "InputLayer.h"
#include "HiddenLayer.h"
#include "OutputLayer.h"
#include "Data.h"

class Model
{
public:
	Model();
	~Model();

	Data* data;
	Minibatch* batch;
	vector<Layer*> layers;

	void train(unsigned int, bool output = false);
};

