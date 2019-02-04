#include "pch.h"
#include "main.h"

int main()
{
	Data data;

	data.readMnist();

	Digit digit;
	digit.label = data.labels[50];
	digit.image = data.images[50];

	cout << digit.ToString() << endl;

	OutputLayer outputLayer(10);
	HiddenLayer test(800, outputLayer);


	cout << &outputLayer << endl;
	cout << test.nextLayer << endl;
}
