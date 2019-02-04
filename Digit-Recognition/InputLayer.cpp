#include "pch.h"
#include "InputLayer.h"

InputLayer::InputLayer(Layer &_nextLayer)
{
	neurons = 784;
	nextLayer = &_nextLayer;

	outputs = nextLayer->neurons;
	nextLayer->inputs = neurons;

	for (int i = 0; i < neurons; i++)
		S.push_back(0);

	Z = S;

	vector<double> temp;
	for (int i = 0; i < outputs; i++)
	{
		temp.clear();
		for (int j = 0; j < neurons; j++)
		{
			temp.push_back(rand() % 600 / 1000.0);
		}
		w.push_back(temp);
	}
}

InputLayer::~InputLayer()
{
}

void InputLayer::LoadDigit(Digit &digit)
{
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			X.push_back(digit.image[i][j]);
		}
	}
}
