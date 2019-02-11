#define debug false
#if !debug
#define imageSize 28
#define minibatchSize 20
#define datasetSize 20
#endif
#if debug
#define imageSize 2
#define minibatchSize 2
#define datasetSize 1
#endif

#define ubyte unsigned char

#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

static string trainingImages = "mnist/train-images.idx3-ubyte";
static string trainingLabels = "mnist/train-labels.idx1-ubyte";
static double eta = 0.1; //learning rate