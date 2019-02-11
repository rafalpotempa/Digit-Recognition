#include "pch.h"
#include "OutputLayer.h"

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
	P = S;

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
			Z[k][i] = exp(previousLayer->Z[k][i]) / sum;

		for (int i = 0; i < outputs; i++)
			P[k][i] = exp(previousLayer->Z[k][i]) / sum;

	}
}

double OutputLayer::squareError()
{
	double result = 0;
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
			result += D[i][k] * D[i][k];
		
		result *= 0.5;
	}
	return result;
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
	stream.precision(2);
	stream << outputLayer.minibatchNumber << ": \t";

	if (minibatchSize <= 10)
	{
		double max;

		for (int k = 0; k < minibatchSize; k++)
		{
			for (int i = 0; i < outputLayer.outputs; i++)
			{
				if (outputLayer.Y[k][i] == 1)
				{
					stream << i << ", ";
					break;
				}
			}
		}
		stream.precision(4);
		stream << "\t" << outputLayer.squareError() << endl;
		stream.precision(4);
		stream << "\t";

		
		for (int k = 0; k < minibatchSize; k++)
		{
			max = 0;
			for (int i = 0; i < outputLayer.outputs; i++)
				if (outputLayer.Z[k][i] > max)
					max = outputLayer.Z[k][i];

			for (int i = 0; i < outputLayer.outputs; i++)
			{
				if (outputLayer.Z[k][i] == max)
				{
					stream << i;

					if (k == minibatchSize - 1)
						stream << " | ";
					else
						stream << ", ";
					break;
				}
			}
		}

		for (int k = 0; k < minibatchSize; k++)
		{
			max = 0;
			for (int i = 0; i < outputLayer.outputs; i++)
				if (outputLayer.Z[k][i] > max)
					max = outputLayer.Z[k][i];

			for (int i = 0; i < outputLayer.outputs; i++)
			{
				if (outputLayer.Z[k][i] == max)
				{
					stream << fixed << outputLayer.P[k][i] * 100 << "% ";
					break;
				}
			}
		}
		stream << endl;
	}
	else
	{
		stream.precision(4);
		stream << "Square error: " << outputLayer.squareError() << endl;
	}
	return stream;
}
