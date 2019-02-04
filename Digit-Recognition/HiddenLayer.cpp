#include "pch.h"
#include "HiddenLayer.h"

HiddenLayer::HiddenLayer(int _neurons, Layer &_nextLayer)
{
	neurons = _neurons;
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


HiddenLayer::~HiddenLayer()
{
}
