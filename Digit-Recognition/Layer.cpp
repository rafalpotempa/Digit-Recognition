#include "pch.h"
#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
	w.clear();
	S.clear();
	Z.clear();
}

void Layer::sigmoid() //calculating sigmoid and its derivative
{
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
			Z[k][i] = 1.0 / (1.0 + exp(-S[k][i]));

		for (int i = 0; i < outputs; i++)
			F[i][k] = (exp(-S[k][i]) / pow(1 + exp(-S[k][i]), 2));
	}
}