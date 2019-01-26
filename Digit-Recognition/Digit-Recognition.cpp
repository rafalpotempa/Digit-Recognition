#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#define ubyte unsigned char

using namespace std;

static string trainingImages = "mnist/train-images.idx3-ubyte";
static string trainingLabels = "mnist/train-labels.idx1-ubyte";

class Digit {
public:
	vector<vector<ubyte>> image;
	ubyte label;

	Digit() {
		vector<ubyte> imageRow;
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				imageRow.push_back(0);
			}
			image.push_back(imageRow);
		}
	}

	string ToString() {
		string result;
		for (int i = 0; i < 28; i++)
		{
			for (int j = 0; j < 28; j++)
			{
				if (image[i][j] > 204)
					result += "\219";
				else if (image[i][j] > 153)
					result += "\178";
				else if (image[i][j] > 102)
					result += "\177";
				else if (image[i][j] > 51)
					result += "\176";
				else
					result += " ";

			}
			result += "\n";
		}
		return result;
	}
};

class Data {
public:
	ifstream images;
	ifstream labels;
	char temp;

	vector<Digit> digits;

	void readMnist() {
		images.open(trainingImages, ios::binary);
		labels.open(trainingLabels, ios::binary);

		//skipping fstream additional information
		for (int i = 0; i < 16; ++i) 
			images.read(&temp, sizeof(ubyte));
		for (int i = 0; i < 8; ++i) 
			labels.read(&temp, sizeof(ubyte));
		
		//loop for reading all images to memory
		cout << "Reading mnist to memory:" << endl;
		for (int m = 0; m < 60000; m++)
		{
			digits.push_back(*(new Digit()));

			labels.read((char*)&digits[m].label, sizeof(ubyte));

			for (int i = 0; i < 28; i++)
			{
				for (int j = 0; j < 28; j++)
				{
					images.read((char*)&digits[m].image[i][j], sizeof(ubyte));
				}
			}
			if (m % 600 == 0) {
				cout << "\r" << m/600 << " %";
			}
		}
		cout << endl;
	}
};

int main()
{
	Data data;

	data.readMnist();

	cout << data.digits[0].ToString() << endl;
}
