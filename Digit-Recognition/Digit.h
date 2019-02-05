#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Global.h"

class Digit
{
public:
	vector<vector<ubyte>> image;
	ubyte label;

	Digit();

	friend ostream& operator<<(ostream&, Digit&);
};

