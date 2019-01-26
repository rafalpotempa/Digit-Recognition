#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

static string trainingImages = "mnist/t10k-images-idx3-ubyte";
static string traininLabels  = "mnist/t10k-labels-idx1-ubyte";

class Data {
public:
	ifstream images;
	ifstream labels;
	char number;

	void readMnist() {
		images.open(trainingImages.c_str(), ios::binary);
		labels.open(trainingImages.c_str(), ios::binary);

		for (int i = 1; i <= 16; ++i) {
			images.read(&number, sizeof(char));
		}
		for (int i = 1; i <= 8; ++i) {
			labels.read(&number, sizeof(char));
		}
	}
};

int main()
{
	Data data;

	data.readMnist();

	cout << data.number << endl;
}
