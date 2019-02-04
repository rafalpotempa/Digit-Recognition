#include "pch.h"
#include "OutputLayer.h"


OutputLayer::OutputLayer(int _neurons)
{
	neurons = _neurons;
	outputs = _neurons;

	for (int i = 0; i < neurons; i++)
		S.push_back(0);
	Z = S;
}


OutputLayer::~OutputLayer()
{
}
