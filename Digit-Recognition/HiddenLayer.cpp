#include "pch.h"
#include "HiddenLayer.h"

HiddenLayer::HiddenLayer(int _neurons, Layer &_nextLayer)
{
	neurons = _neurons;
	nextLayer = &_nextLayer;
	_nextLayer.previousLayer = this;

	outputs = nextLayer->neurons;
	nextLayer->inputs = neurons;

	vector<double> temp;
	for (int i = 0; i < outputs; i++)
		temp.push_back(0);
	for (int i = 0; i < minibatchSize; i++)
		S.push_back(temp);

	Z = S;
	
	//D.size = (S.size)transposed
	temp.clear();
	for (int i = 0; i < minibatchSize; i++)
		temp.push_back(0);
	for (int i = 0; i < outputs; i++)
		D.push_back(temp);

	F = D;

	for (int i = 0; i < neurons; i++)
	{
		temp.clear();
		for (int j = 0; j < outputs; j++)
		{
			temp.push_back(rand() % 1200 / 1000.0 - 0.6);
			//temp.push_back(0.6);
		}
		w.push_back(temp);
	}
}

void HiddenLayer::forward()
{
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			S[k][i] = 0; //clear residuals

			for (int j = 0; j < neurons; j++)
			{
				S[k][i] += previousLayer->Z[k][j] * w[j][i];
			}
		}
	}
	sigmoid();
}

void HiddenLayer::backward()
{
	//clearing is done after update

	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			if (!nextLayer->w.empty())
			{
				for (int j = 0; j < nextLayer->outputs; j++)
					D[i][k] += nextLayer->w[i][j] * nextLayer->D[j][k] * F[i][k];
			}
			else
				for (int j = 0; j < nextLayer->outputs; j++)
					D[i][k] += nextLayer->D[i][k];
		}
	}
}

void HiddenLayer::update()
{
	for (int k = 0; k < minibatchSize; k++)
		for (int i = 0; i < outputs; i++)
			D[i][k] /= datasetSize/minibatchSize; //mean for all minibatches

	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < neurons; i++)
		{
			for (int j = 0; j < outputs; j++)
				w[i][j] += -eta * D[j][k] * Z[k][j];
		}
	}

	for (int k = 0; k < minibatchSize; k++)
		for (int i = 0; i < outputs; i++)
			D[i][k] = 0; //clear residuals
}
