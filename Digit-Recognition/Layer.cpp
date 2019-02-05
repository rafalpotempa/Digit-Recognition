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

void Layer::sigmoid()
{
	for (int i = 0; i < outputs; i++)
	{
		Z[i] = 1.0 / (1.0 + exp(-S[i]));
	}
}