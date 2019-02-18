#pragma once
#include <iostream>
#include <string>
#include <vector>

#define ubyte unsigned char

using namespace std;

static string trainingImages = "mnist/train-images.idx3-ubyte";
static string trainingLabels = "mnist/train-labels.idx1-ubyte";

static int imageSize = 28;

extern int minibatchSize;
extern int datasetSize;
extern int numberOfEpochs;
extern double eta;
