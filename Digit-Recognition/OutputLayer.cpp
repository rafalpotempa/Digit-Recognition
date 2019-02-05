#include "pch.h"
#include "OutputLayer.h"

OutputLayer::OutputLayer(int _neurons)
{
	neurons = _neurons;
	outputs = _neurons;

	for (int i = 0; i < neurons; i++)
		S.push_back(0);
	Z = S;
}

void OutputLayer::forward()
{
	for (int i = 0; i < outputs; i++)
	{
		S[i] = previousLayer->S[i];
	}
	softMax();
}

void OutputLayer::softMax()
{
	double sum = 0;
	for (int i = 0; i < outputs; i++)
		sum += S[i];
	
	for (int i = 0; i < outputs; i++)
	{
		Z[i] = S[i] / sum * 100.0;
	}
}

ostream & operator<<(ostream & stream, OutputLayer & outputLayer)
{
	double max = 0;
	for (int i = 0; i < outputLayer.outputs; i++)
		if (outputLayer.S[i] > max)
			max = outputLayer.S[i];

	for (int i = 0; i < outputLayer.outputs; i++)
	{
		stream << i << ": " << outputLayer.S[i] << "\t" << outputLayer.Z[i] << "%";
		if (outputLayer.S[i] == max)
			stream << " <- ";

		stream << endl;
	}
	return stream;
}
