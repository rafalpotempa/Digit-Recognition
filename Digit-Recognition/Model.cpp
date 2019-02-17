#include "pch.h"
#include "Model.h"


Model::Model(string path)
{
	fstream file;

	file.open(path, fstream::in);
	if (!file.is_open())
	{
		cerr << "<\"" << path << "\" cannot be opened for reading>" << endl;
		file.close();
		return;
	}


	string line;
	getline(file, line);

	istringstream iss(line);
	vector<int> layerSizes{istream_iterator<int>(iss), istream_iterator<int>{}};

	static OutputLayer outputLayer(layerSizes.back());

	if (layerSizes.size() > 2)
	{
		vector<HiddenLayer*> hiddenLayers;

		for (size_t i = 2; i < layerSizes.size(); i++)
		{
			if (i == 2)
				hiddenLayers.push_back(new HiddenLayer(layerSizes[layerSizes.size() - i], outputLayer));
			else
				hiddenLayers.push_back(new HiddenLayer(layerSizes[layerSizes.size() - i], *hiddenLayers.back()));
		}

		static InputLayer inputLayer(*hiddenLayers.back());
		layers.push_back(&inputLayer);
		for (int i = hiddenLayers.size() - 1; i >= 0; i--)
			layers.push_back(hiddenLayers[i]);
		layers.push_back(&outputLayer);
	}
	else
	{
		InputLayer inputLayer(outputLayer);
		layers.push_back(&inputLayer);
		layers.push_back(&outputLayer);
	}
	getline(file, line);

	for (size_t k = 0; k < layers.size() - 1; k++)
	{
		for (int i = 0; i < layers[k]->neurons; i++)
		{
			getline(file, line);
			istringstream iss(line);
			vector<double> temp{ istream_iterator<double>(iss), istream_iterator<double>{} };

			layers[k]->w[i] = temp;
		}
		getline(file, line);
	}
	cout << "Model loaded from \"" << path << "\"" << endl << endl;
}


void Model::saveToFile()
{
	string path = "";
	ofstream file;

	for (size_t i = 0; i < layers.size(); i++)
	{
		path += to_string(layers[i]->neurons);

		if (i != (layers.size() - 1))
			path += "-";
	}
	path += " eta=";
	path += to_string(eta);
	path += ".nn";

	file.open(path, fstream::out);
	if (!file.is_open())
	{
		cerr << "<\"" << path << "\" cannot be opened>" << endl;
		file.open(path, fstream::out | fstream::trunc);
	}

	for (size_t i = 0; i < layers.size(); i++)
		file << layers[i]->neurons << " ";
	
	file << endl << endl;

	for (size_t k = 0; k < layers.size() - 1; k++)
	{
		for (int i = 0; i < layers[k]->neurons; i++)
		{
			for (int j = 0; j < layers[k]->outputs; j++)
			{
				file << layers[k]->w[i][j] << "\t";
			}
			file << endl;
		}
		file << endl;
	}

	file.close();
	cout << endl << "Model saved to: \"" << path << "\"" << endl << endl;
}

void Model::train(unsigned int epochs, bool output) //run model for given number of epochs
{ 
	InputLayer& inputLayer = *dynamic_cast<InputLayer*>(layers.front());
	OutputLayer& outputLayer = *dynamic_cast<OutputLayer*>(layers.back());

	for (unsigned int e = 0; e < epochs; e++)
	{
		cout << "Epoch: " << e + 1 << " / " << epochs << endl;
		for (int k = 0; k < datasetSize/minibatchSize; k++)
		{
			inputLayer.loadMinibatch(batch->operator()(k));
			cout << outputLayer.minibatchNumber << ":\t";

			cout << "forward feed...";
			for (unsigned int i = 0; i < layers.size(); i++)
				layers[i]->forward();
			for (unsigned int i = 0; i < strlen("forward feed..."); i++)
				cout << "\b \b";

			cout << "backpropagation...";
			for (unsigned int i = layers.size(); i > 0; i--)
				layers[i - 1]->backward();
			for (unsigned int i = 0; i < strlen("backpropagation..."); i++)
				cout << "\b \b";
			
			if (output)
				cout << outputLayer;

			outputLayer.previousError[k] = outputLayer.squareError();
		}
		cout << "update...";
		for (unsigned int i = 0; i < layers.size(); i++)
			layers[i]->update();
		for (unsigned int i = 0; i < strlen("update..."); i++)
			cout << "\b \b";
	}
}

