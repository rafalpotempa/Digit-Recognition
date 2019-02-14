#define debug false
#if !debug
#define imageSize 28
#define minibatchSize 1
#define datasetSize 5
#endif
#if debug
#define imageSize 2
#define minibatchSize 2
#define datasetSize 2
#endif

#define ubyte unsigned char

#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static string trainingImages = "mnist/train-images.idx3-ubyte";
static string trainingLabels = "mnist/train-labels.idx1-ubyte";
static double eta = 0.01; //learning rate