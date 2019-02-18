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
			temp.push_back(rand() % 1200 / 1000.0 - 0.6);
			//temp.push_back(0.6);
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
	{
		for (int i = 0; i < outputs; i++)
		{
			for (int j = 0; j < nextLayer->outputs; j++)
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

void InputLayer::update()
{
	for (int k = 0; k < minibatchSize; k++)
		for (int i = 0; i < outputs; i++)
			D[i][k] /= datasetSize/minibatchSize; //mean for all minibatches

	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < neurons; i++)
		{
			for (int j = 0; j < outputs; j++)
				w[i][j] += -eta * D[j][k] * X[k][i];
		}
	}

	for (int k = 0; k < minibatchSize; k++)
		for (int i = 0; i < outputs; i++)
			D[i][k] = 0; //clear residuals
}


void InputLayer::loadDigit(Digit &digit)
{
	X.clear();
	vector<double> temp;
	for (int i = 0; i < imageSize; i++)
	{
		for (int j = 0; j < imageSize; j++)
		{
			temp.push_back(digit.image[i][j] / 256.0);
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
				temp.push_back(minibatch[k].image[i][j] / 256.0);
			}
		}
		X.push_back(temp);
	}


	// output layer output initialization
	Layer* search = nextLayer;
	while (search->nextLayer)
		search = search->nextLayer;

	OutputLayer *_output;
	_output = dynamic_cast<OutputLayer*>(search);

	_output->minibatchNumber = minibatch.minibatchNumber;
	
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < _output->outputs; i++)
		{
			_output->Y[k][i] = 0.0;
		}
	}
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < _output->outputs; i++)
		{
			if (i == minibatch.digits[k].label)
			{
				_output->Y[k][i] = 1.0;
			}
		}
	}
}



