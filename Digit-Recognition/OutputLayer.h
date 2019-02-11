#pragma once
#include "Layer.h"
#include "Minibatch.h"

class OutputLayer :
	public Layer
{
public:
	vector<vector<double>> Y; //desired output matrix
	vector<vector<double>> P; //probabilities matrix
	unsigned int minibatchNumber;

	OutputLayer() {};
	OutputLayer(int);
	~OutputLayer();

	void forward();
	void backward();

	void softMax();
	void crossEntropy();
	double squareError();
	friend ostream& operator<<(ostream&, OutputLayer&);
};