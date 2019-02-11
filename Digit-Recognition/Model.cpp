#include "pch.h"
#include "Model.h"


Model::Model()
{
}


Model::~Model()
{
}


void Model::train(unsigned int epochs, bool output) //run model for given number of epochs
{ 
	for (unsigned int e = 0; e < epochs; e++)
	{
		cout << "Epoch: " << e + 1 << " / " << epochs << endl;
		for (int k = 0; k < datasetSize/minibatchSize; k++)
		{
			dynamic_cast<InputLayer*>(layers.front())->loadMinibatch(batch->operator()(k));

			cout << "forward feed...";
			for (unsigned int i = 0; i < layers.size(); i++)
				layers[i]->forward();
			for (unsigned int i = 0; i < strlen("forward feed..."); i++)
				cout << "\b \b"; //string delete

			cout << "backpropagation...";
			for (unsigned int i = layers.size(); i > 0; i--)
				layers[i - 1]->backward();
			for (unsigned int i = 0; i < strlen("backpropagation..."); i++)
				cout << "\b \b"; //string delete
			
			cout << "update...";
			for (unsigned int i = 0; i < layers.size(); i++)
				layers[i]->update();
			for (unsigned int i = 0; i < strlen("update..."); i++)
				cout << "\b \b"; //string delete

			if (output)
				cout << *dynamic_cast<OutputLayer*>(layers.back());
		}
	}
}

