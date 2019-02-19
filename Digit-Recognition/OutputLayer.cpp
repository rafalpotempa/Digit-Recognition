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

	for (int k = 0; k < datasetSize / minibatchSize; k++)
		previousError.push_back(0);
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
	double sum, max, label, answer;

	numberOfMistakes = 0;

	for (int k = 0; k < minibatchSize; k++)
	{
		sum = 0;

		for (int i = 0; i < outputs; i++)
			sum += exp(previousLayer->Z[k][i]);

		for (int i = 0; i < outputs; i++)
			Z[k][i] = previousLayer->Z[k][i];

		for (int i = 0; i < outputs; i++)
			P[k][i] = exp(previousLayer->Z[k][i]) / sum;


		max = 0;
		label = -1;
		answer = -2;
		for (int i = 0; i < outputs; i++)
			if (Y[k][i] == 1)
				label = i;

		for (int i = 0; i < outputs; i++)
		{
			if (Z[k][i] > max)
			{
				max = Z[k][i];
				answer = i;
			}
		}

		if (answer != label)
			numberOfMistakes += 1;
	}
}

double OutputLayer::squareError()
{
	double result = 0;
	for (int k = 0; k < minibatchSize; k++)
	{
		for (int i = 0; i < outputs; i++)
			result += D[i][k] * D[i][k];
		
	}
	result *= 0.5;
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
	double previousError = outputLayer.previousError[outputLayer.minibatchNumber];
	double currentError = outputLayer.squareError();

	if (minibatchSize <= 5)
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
		stream << "\t";

		//printing formatted square error
		stream << fixed << currentError;

		//printing change of squre error
		if (previousError != 0)
		{
			stream << " (";
			if (previousError > currentError)
				stream << green;
			else if (previousError < currentError)
				stream << red << "+";
			else
				stream << white;
			stream << currentError - previousError << white << ")";
		}
		else
			stream << "\t";

		//number of correct guesses
		stream << "\t" << minibatchSize - outputLayer.numberOfMistakes << " / " << minibatchSize;

		stream.precision(2);
		stream << endl << "\t";
		
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
	else //case for large minibatches
	{
		stream.precision(4);
		//printing formatted square error
		stream << "Square error: ";
		stream << fixed << currentError;

		//printing change of squre error
		if (previousError != 0)
		{
			stream << " (";
			if (previousError > currentError)
				stream << green;
			else if (previousError < currentError)
				stream << red << "+";
			else
				stream << white;
			stream << currentError - previousError << white << ")";
		}
		else
			stream << "\t";
		//number of correct guesses
		stream << "\t" << minibatchSize - outputLayer.numberOfMistakes << " / " << minibatchSize;

		stream << endl;
	}
	return stream;
}
