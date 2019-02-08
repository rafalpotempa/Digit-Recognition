#pragma once
#include "Layer.h"
#include "Digit.h"
#include "Minibatch.h"

class InputLayer :
	public Layer
{
public:
	vector<vector<double>> X; //input matrix

	InputLayer(Layer&);
	~InputLayer();

	void forward();
	void backward();
	void loadDigit(Digit&);
	void loadMinibatch(Minibatch&);
};

