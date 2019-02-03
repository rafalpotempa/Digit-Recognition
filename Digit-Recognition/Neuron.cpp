#include "pch.h"
#include "Neuron.h"


Neuron::Neuron()
{
}


Neuron::~Neuron()
{
}

double Neuron::sigmoid(double x)
{
	return 1.0 / (1 + exp(-x));
}
