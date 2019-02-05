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

ostream & operator<<(ostream &stream, Digit& digit)
{
	stream << "Label: " << (int)digit.label << endl;

	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
		{
			if (digit.image[i][j] > 204)
				stream << (char)219;
			else if (digit.image[i][j] > 153)
				stream << (char)178;
			else if (digit.image[i][j] > 102)
				stream << (char)177;
			else if (digit.image[i][j] > 51)
				stream << (char)176;
			else
				stream << " ";
		}
		stream << "\n";
	}
	return stream;
}
