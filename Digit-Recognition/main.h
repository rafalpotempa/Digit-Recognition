#pragma once
#include <stdlib.h>
#include "Global.h"
#include "Digit.h"
#include "Data.h"
#include "Layer.h"
#include "InputLayer.h"
#include "OutputLayer.h"
#include "HiddenLayer.h"
#include "Minibatch.h"
#include "Model.h"
#include "ConsoleColor.h"

void dataParameters();
void initialise(Model&);
void epochsNumber();