#pragma once
#include "Layer.h"

class OutputLayer :
	public Layer
{
public:
	OutputLayer(int);

	void forward();
	void softMax();
	friend ostream& operator<<(ostream&, OutputLayer&);
};