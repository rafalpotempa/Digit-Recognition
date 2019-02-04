#include "pch.h"
#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
	for (int i = 0; i < neurons; i++)
	{
		w[i].clear();
		S[i].clear();
		Z[i].clear();

	}
	w.clear();
	S.clear();
	Z.clear();
}

void Layer::sigmoid()
{
	//for (int i = 0; i < S.size(); i++)
	//{
	//	for (int j = 0; j < S[0].size(); j++)
	//	{
	//		Z[i][j] = 1.0 / (1.0 / -exp(-S[i][j]));
	//	}
	//}
}
