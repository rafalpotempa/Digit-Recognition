#include "pch.h"
#include "Layer.h"


Layer::Layer(int r, int c)
{
	rows = r;
	cols = c;

	vector<double> temp;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			temp.push_back(0);
		}
		w.push_back(temp);

	}
}


Layer::~Layer()
{
}

void Layer::sigmoid()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			Z[i][j] = 1.0 / (1.0 / -exp(-S[i][j]));
		}
	}
}
