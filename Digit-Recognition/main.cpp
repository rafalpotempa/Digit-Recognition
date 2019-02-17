#include "pch.h"
#include "main.h"

int main()
{
	//string answer;
	//cout << "Initialise network from file? [\"yes\"/\"no\"]  ";
	//cin >> answer;

	//if (answer == "yes")
	//{
	//	cout << "good" << endl;
	//}
	//else if (answer == "no")
	//{
	//	cout << "also good" << endl;
	//}

#if !debug

	Data data;
	Minibatch batch(data);
	Model model("784-128-16-10 eta=0.010000.nn");
	model.batch = &batch;

	data.readMnist();

	model.train(10, true);
	model.saveToFile();
	
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

	model.layers.push_back(&in);
	model.layers.push_back(&hid1);
	model.layers.push_back(&hid2);
	model.layers.push_back(&out);
	
	model.train(100, true);
#endif
	system("pause");
}
