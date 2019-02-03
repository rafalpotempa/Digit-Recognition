#pragma once
#include <math.h>

using namespace std;

class Neuron
{
public:
	Neuron();
	~Neuron();

	double sigmoid(double);
};

