#define debug true
#if !debug
#define imageSize 28
#define minibatchSize 2
#endif
#if debug
#define imageSize 2
#define minibatchSize 1
#endif

#define ubyte unsigned char

#pragma once
#include <iostream>
#include <string>

using namespace std;

static string trainingImages = "mnist/train-images.idx3-ubyte";
static string trainingLabels = "mnist/train-labels.idx1-ubyte";
static double eta = 10;