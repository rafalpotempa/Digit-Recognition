#pragma once
#include "Layer.h"
#include "Digit.h"

class InputLayer :
	public Layer
{
public:
	vector<double> X; //input matrix

	InputLayer(Layer&);
	~InputLayer();

	void forward();
	void loadDigit(Digit&);
};

