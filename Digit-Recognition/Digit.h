#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "constatns.h"

class Digit
{
public:
	vector<vector<ubyte>> image;
	ubyte label;

	Digit();

	string ToString();
};

