#include "pch.h"
#include "main.h"

int main()
{
	Data data;

	data.readMnist();

	cout << data[11];

	OutputLayer outputLayer(10);
	HiddenLayer hiddenLayer2(80, outputLayer);
	HiddenLayer hiddenLayer1(200, hiddenLayer2);
	InputLayer inputLayer(hiddenLayer1);

	inputLayer.loadDigit(data[10]);

	inputLayer.forward();
	hiddenLayer1.forward();
	hiddenLayer2.forward();
	outputLayer.forward();

	cout << outputLayer;
	system("pause");
}
