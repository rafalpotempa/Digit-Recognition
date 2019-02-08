#include "pch.h"
#include "main.h"

int main()
{
#if !debug
	Data data;
	Minibatch batch(data);

	data.readMnist();

	OutputLayer outputLayer(10);
	HiddenLayer hiddenLayer2(80, outputLayer);
	HiddenLayer hiddenLayer1(800, hiddenLayer2);
	InputLayer inputLayer(hiddenLayer1);

	for (int k = 0; k < 2; k++)
	{
		inputLayer.loadMinibatch(batch(k));

		inputLayer.forward();
		hiddenLayer1.forward();
		hiddenLayer2.forward();
		outputLayer.forward();

		cout << batch[0];

	}

#endif
	
#if debug
	Minibatch batch;
	Digit digit1, digit2;

	digit1.label = 1;
	digit1.image[0][0] = 1;
	digit1.image[0][1] = 1;
	digit1.image[1][0] = 0;
	digit1.image[1][1] = 1;

	digit2.label = 1;
	digit2.image[0][0] = 0;
	digit2.image[0][1] = 1;
	digit2.image[1][0] = 0;
	digit2.image[1][1] = 1;

	OutputLayer out(2);
	HiddenLayer hid2(5, out);
	HiddenLayer hid1(3, hid2);
	InputLayer in(hid1);

	in.w[0][0] = 1;
	hid1.w[0][0] = 1;
	hid2.w[0][0] = 1;

	batch.digits.push_back(digit1);
	//batch.digits.push_back(digit2);

	in.loadMinibatch(batch);
	out.loadMinibatch(batch);

	in.forward();
	hid1.forward();
	hid2.forward();
	out.forward();

	cout << out;

	out.backward();
	hid2.backward();
	hid1.backward();
	in.backward();

#endif

	system("pause");
}
