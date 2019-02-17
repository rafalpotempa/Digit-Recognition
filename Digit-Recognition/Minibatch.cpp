#include "pch.h"
#include "Minibatch.h"


Minibatch::Minibatch()
{
}

Minibatch::Minibatch(Data& _data)
{
	data = &_data;
}

Minibatch::~Minibatch()
{
	digits.clear();
}

Minibatch & Minibatch::operator()(int n) //returns minibatch number 'n' from data
{
	minibatchNumber = n;
	digits.clear();
	
	Digit temp;
	for (int k = 0; k < minibatchSize; k++)
	{
		temp.label = data->labels[n*minibatchSize + k];
		for (int i = 0; i < imageSize; i++)
		{
			for (int j = 0; j < imageSize; j++)
			{
				temp.image[i][j] = data->images[n*minibatchSize + k][i][j];
			}
		}
		digits.push_back(temp);
	}
	return *this;
}

Digit & Minibatch::operator[](int n)
{
	return digits[n];
}
