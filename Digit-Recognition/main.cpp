#include "pch.h"
#include "main.h"

int main()
{
#if !debug

	Data data;
	Minibatch batch(data);
	Model model;
	model.batch = &batch;

	data.readMnist();

	OutputLayer outputLayer(10);
	HiddenLayer hiddenLayer2(80, outputLayer);
	HiddenLayer hiddenLayer1(200, hiddenLayer2);
	InputLayer inputLayer(hiddenLayer1);

	model.layers.push_back(&inputLayer);
	model.layers.push_back(&hiddenLayer1);
	model.layers.push_back(&hiddenLayer2);
	model.layers.push_back(&outputLayer);

	for (int k = 0; k < datasetSize/minibatchSize; k++)
	{
		model.train(100, true);
	}

#endif
	
#if debug
	Minibatch batch;
	Digit digit1, digit2;
	Model model;

	digit1.label = 1;
	digit1.image[0][0] = 1;
	digit1.image[0][1] = 1;
	digit1.image[1][0] = 0;
	digit1.image[1][1] = 1;

	digit2.label = 0;
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
	batch.digits.push_back(digit2);

	in.loadMinibatch(batch);
	out.loadMinibatch(batch);


	model.layers.push_back(&in);
	model.layers.push_back(&hid1);
	model.layers.push_back(&hid2);
	model.layers.push_back(&out);
	
	model.run(100);
	cout << out;
#endif
	system("pause");
}
