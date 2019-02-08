#pragma once
#include "Global.h"
#include "Digit.h"
#include "Data.h"

class Minibatch
{
	Data* data;

public:
	vector<Digit> digits;
	Minibatch();
	Minibatch(Data&);
	~Minibatch();

	Minibatch& operator()(int);
	Digit& operator[](int);
};

