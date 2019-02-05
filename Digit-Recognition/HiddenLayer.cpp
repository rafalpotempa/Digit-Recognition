#include "pch.h"
#include "HiddenLayer.h"

HiddenLayer::HiddenLayer(int _neurons, Layer &_nextLayer)
{
	neurons = _neurons;
	nextLayer = &_nextLayer;
	_nextLayer.previousLayer = this;

	outputs = nextLayer->neurons;
	nextLayer->inputs = neurons;

	for (int i = 0; i < outputs; i++)
		S.push_back(0);

	Z = S;

	vector<double> temp;
	for (int i = 0; i < neurons; i++)
	{
		temp.clear();
		for (int j = 0; j < outputs; j++)
		{
			temp.push_back(rand() % 600 / 1000.0);
		}
		w.push_back(temp);
	}
}

void HiddenLayer::forward()
{
	for (int i = 0; i < outputs; i++)
	{
		for (int j = 0; j < neurons; j++)
		{
			S[i] += previousLayer->Z[j] * w[j][i];
		}
	}
	sigmoid();
}
