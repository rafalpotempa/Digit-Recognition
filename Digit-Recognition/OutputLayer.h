#pragma once
#include "Layer.h"
#include "Minibatch.h"

class OutputLayer :
	public Layer
{
public:
	vector<vector<double>> Y; //desired output matrix

	OutputLayer();
	OutputLayer(int);
	~OutputLayer();

	void loadMinibatch(Minibatch&);
	void forward();
	void softMax();
	void backward();
	friend ostream& operator<<(ostream&, OutputLayer&);
};