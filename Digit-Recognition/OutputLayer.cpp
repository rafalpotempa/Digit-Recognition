#include "pch.h"
#include "OutputLayer.h"

OutputLayer::OutputLayer()
{
}

OutputLayer::OutputLayer(int _neurons)
{
	neurons = _neurons;
	outputs = _neurons;

	vector<double> temp;
	for (int i = 0; i < outputs; i++)
		temp.push_back(0);
	for (int i = 0; i < minibatchSize; i++)
		S.push_back(temp);

	Z = S;
	Y = S;

	//D.size = (S.size)transposed 
	temp.clear();
	for (int i = 0; i < minibatchSize; i++)
		temp.push_back(0);
	for (int i = 0; i < outputs; i++)
		D.push_back(temp);

	F = D;
}

OutputLayer::~OutputLayer()
{
	Y.clear();
}

void OutputLayer::loadMinibatch(Minibatch & minibatch)
{
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			if (i == minibatch.digits[k].label)
			{
				Y[k][i] = 1.0;
			}
		}
	}
}

void OutputLayer::forward()
{
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			S[k][i] = previousLayer->S[k][i];
		}
	}
	softMax();
}

void OutputLayer::softMax()
{
	double sum;
	for (int k = 0; k < minibatchSize; k++)
	{
		sum = 0;
		for (int i = 0; i < outputs; i++)
			sum += exp(previousLayer->Z[k][i]);

		for (int i = 0; i < outputs; i++)
		{
			Z[k][i] = exp(previousLayer->Z[k][i]) / sum;
		}
	}
}

void OutputLayer::backward()
{
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
		{
			D[i][k] = Z[k][i] - Y[k][i];
		}
	}
}

ostream & operator<<(ostream & stream, OutputLayer & outputLayer)
{
	double max;
	for (int k = 0; k < minibatchSize; k++)
	{
		max = 0;
		for (int i = 0; i < outputLayer.outputs; i++)
			if (outputLayer.Z[k][i] > max)
				max = outputLayer.Z[k][i];

		for (int i = 0; i < outputLayer.outputs; i++)
		{
			stream << i << ":  " << outputLayer.S[k][i] << "\t" << outputLayer.Z[k][i] * 100.0 << "%";
			if (outputLayer.Z[k][i] == max)
				stream << " <- ";

			stream << endl;
		}
		stream << endl;
	}

	return stream;
}
