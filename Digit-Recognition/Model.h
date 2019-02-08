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

	vector<Layer*> layers;
	Data* data;

	void train(int);
};

