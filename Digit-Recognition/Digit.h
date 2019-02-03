#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Constants.h"

class Digit
{
public:
	vector<vector<ubyte>> image;
	ubyte label;

	Digit();

	string ToString();
};

