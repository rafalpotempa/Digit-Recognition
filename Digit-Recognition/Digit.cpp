#include "pch.h"
#include "Digit.h"

Digit::Digit()
{
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

string Digit::ToString()
{
	string result;

	result += "Label: ";
	result += label + '0';

	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (image[i][j] > 204)
				result += 219;
			else if (image[i][j] > 153)
				result += 178;
			else if (image[i][j] > 102)
				result += 177;
			else if (image[i][j] > 51)
				result += 176;
			else
				result += " ";
		}
		result += "\n";
	}
	return result;
}