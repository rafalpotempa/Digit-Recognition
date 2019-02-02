#include "pch.h"
#include "main.h"

int main()
{
	Data data;

	data.readMnist();

	Digit digit;
	digit.label = data.labels[10];
	digit.image = data.images[10];

	cout << digit.ToString() << endl;
}
