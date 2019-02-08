#include "pch.h"
#include "InputLayer.h"
#include "OutputLayer.h"

InputLayer::InputLayer(Layer &_nextLayer)
{
	neurons = imageSize*imageSize;
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
#if !debug
			temp.push_back(rand() % 600 / 1000.0);
#endif
#if debug
			temp.push_back(0.6);
#endif
		}
		w.push_back(temp);
	}
}

InputLayer::~InputLayer()
{
	X.clear();
}

void InputLayer::forward()
{
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			S[k][i] = 0; //clear residuals

			for (int j = 0; j < neurons; j++)
			{
				S[k][i] += X[k][j] * w[j][i];
			}
		}
	}
	sigmoid();
}

void InputLayer::backward()
{
	for (int k = 0; k < minibatchSize; k++)
		for (int i = 0; i < outputs; i++)
			D[i][k] = 0; //clear residuals

	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			for (int j = 0; j < nextLayer->outputs; j++)
				D[i][k] += nextLayer->w[i][j] * nextLayer->D[j][k];
		}
		for (int i = 0; i < outputs; i++)
			D[i][k] *= F[i][k];
	}
}


void InputLayer::loadDigit(Digit &digit)
{
	X.clear();
	vector<double> temp;
	for (int i = 0; i < imageSize; i++)
	{
		for (int j = 0; j < imageSize; j++)
		{
			temp.push_back(digit.image[i][j]);
		}
	}
	X.push_back(temp);
}

void InputLayer::loadMinibatch(Minibatch &minibatch)
{
	X.clear();
	vector<double> temp;
	for (int k = 0; k < minibatchSize; k++)
	{
		temp.clear();
		for (int i = 0; i < imageSize; i++)
		{
			for (int j = 0; j < imageSize; j++)
			{
				temp.push_back(minibatch[k].image[i][j]);
			}
		}
		X.push_back(temp);
	}
}



