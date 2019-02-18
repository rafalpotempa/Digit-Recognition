#pragma once
#include "Layer.h"
#include "Minibatch.h"
#include "ConsoleColor.h"

class OutputLayer :
	public Layer
{
public:
	vector<vector<double>> Y; //desired output matrix
	vector<vector<double>> P; //probabilities matrix
	vector<double> previousError;
	unsigned int minibatchNumber;
	unsigned int numberOfMistakes;

	OutputLayer() {};
	OutputLayer(int);
	~OutputLayer();

	void forward();
	void backward();

	void softMax();
	double squareError();
	friend ostream& operator<<(ostream&, OutputLayer&);
};