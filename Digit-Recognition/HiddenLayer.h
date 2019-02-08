#pragma once
#include "Layer.h"

class HiddenLayer :
	public Layer
{
public:
	HiddenLayer(int, Layer&);
	void forward();
	void backward();
	void update();
};