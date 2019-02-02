#include "pch.h"
#include "Data.h"

Data::~Data()
{
	images.clear();
	labels.clear();
}

void Data::readMnist() {
	imagesFile.open(trainingImages, ios::binary);
	labelsFile.open(trainingLabels, ios::binary);

	//skipping fstream additional information
	for (int i = 0; i < 16; ++i)
		imagesFile.read(&temp, sizeof(ubyte));
	for (int i = 0; i < 8; ++i)
		labelsFile.read(&temp, sizeof(ubyte));

	//loop for reading all images to memory
	cout << "Reading mnist to memory:" << endl;


	for (int m = 0; m < 60000; m++)
	{
		labelsFile.read((char*)&digit.label, sizeof(ubyte));

		labels.push_back(digit.label);

		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				imagesFile.read((char*)&digit.image[i][j], sizeof(ubyte));
			}
		}
		images.push_back(digit.image);
		if (m % 600 == 0) {
			cout << "\r" << m / 600 << " %";
		}
	}
	cout << "\r100 %" << endl;
}