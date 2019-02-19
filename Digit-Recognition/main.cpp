#include "pch.h"
#include "main.h"

int minibatchSize;
int datasetSize;
int numberOfEpochs;
double eta;

void dataParameters() {
	string answer;
	string cleanLine = "                                                  ";

	cout << "Enter dataset size: ";
	while (true)
	{
		cin >> answer;
		for (int i = 0; i < 50; i++)
			cout << "\b \b";

		char* p = 0;
		strtol(answer.c_str(), &p, 10);
		if (!(*p))
		{
			if (stoi(answer) <= 60000)
			{
				cout << "\r" << cleanLine << "\r";

				datasetSize = stoi(answer);
				break;
			}
			else
			{
				cout << "\r" << cleanLine << "\r";
				cerr << "<maximum 60000> ";
				cin.clear();
				continue;
			}
		}
		else
		{
			cout << "\r" << cleanLine << "\r";
			cerr << "<not an integer> ";
			cin.clear();
			continue;
		}
	}

	cout << "Enter minibatch size: ";
	while (true)
	{
		cin >> answer;
		for (int i = 0; i < 50; i++)
			cout << "\b \b";

		char* p = 0;
		strtol(answer.c_str(), &p, 10);
		if (!(*p))
		{
			if (stoi(answer) <= datasetSize)
			{
				cout << "\r" << cleanLine << "\r";
				minibatchSize = stoi(answer);
				break;
			}
			else
			{
				cout << "\r" << cleanLine << "\r";
				cerr << "<maximum " << datasetSize << "> ";
				cin.clear();
				continue;
			}
		}
		else
		{
			cout << "\r" << cleanLine << "\r";
			cerr << "<not an integer> ";
			cin.clear();
			continue;
		}
	}
}

void initialise(Model& model) {
	string answer;
	cout << "Initialise network from file? [\"yes\"/\"no\"]  ";
	cin >> answer;

	if (answer == "yes")
	{
		cout << "Enter file name: ";
		cin >> answer;

		model = Model(answer);
		if (model.layers.empty())
			initialise(model);
	}
	else if (answer == "no")
	{
		cout << "Give layers size:" << endl;
		cout << "    [number] + [enter]" << endl;
		cout << "    \"end\" to break" << endl;
		cout << "    \"del\" to delete last layer" << endl << endl;

		vector<int> layerSizes;
		layerSizes.push_back(784);
		string cleanLine = "                                                  ";

		answer = "";
		cout << "784-";

		while (true)
		{
			cin >> answer;
			for (int i = 0; i < 50; i++)
				cout << "\b \b";

			if (answer == "end")
			{
				if (layerSizes.size() == 1)
				{
					cout << "\r" << cleanLine << "\r";
					cerr << "<two layers required> ";
					for (size_t i = 0; i < layerSizes.size(); i++)
						cout << layerSizes[i] << "-";

					cin.clear();
					continue;
				}
				else
					break;
			}
			else if (answer == "del")
			{
				if (layerSizes.empty())
				{
					cout << "\r" << cleanLine << "\r";
					cerr << "<model is empty> ";
					cin.clear();
					continue;
				}
				else if (layerSizes.size() == 1)
				{
					cout << "\r" << cleanLine << "\r";
					cerr << "<cannot delete> ";
					for (size_t i = 0; i < layerSizes.size(); i++)
						cout << layerSizes[i] << "-";
					cin.clear();
					continue;
				}

				else
				{
					layerSizes.pop_back();
					cout << "\r" << cleanLine << "\r";
					for (size_t i = 0; i < layerSizes.size(); i++)
						cout << layerSizes[i] << "-";

				}

				if (layerSizes.empty())
				{
					cout << "\r" << cleanLine << "\r";
					cout << "<model clear> ";
				}
			}
			else
			{
				char* p = 0;
				strtol(answer.c_str(), &p, 10);
				if (!(*p))
				{
					layerSizes.push_back(stoi(answer));
					cout << "\r" << cleanLine << "\r";
					for (size_t i = 0; i < layerSizes.size(); i++)
						cout << layerSizes[i] << "-";
				}
				else
				{
					cout << "\r" << cleanLine << "\r";
					cerr << "<not an integer> ";
					for (size_t i = 0; i < layerSizes.size(); i++)
						cout << layerSizes[i] << "-";

					cin.clear();
					continue;
				}
			}
		}
		for (int i = 0; i < 50; i++)
			cout << "\b \b";

		while (true)
		{
			cout << "\r" << cleanLine << "\r";
			cout << "Learning rate: eta = ";
			cin >> answer;

			char* p = 0;
			strtod(answer.c_str(), &p);
			if (!(*p))
			{
				eta = stod(answer);
				cout << "\r" << cleanLine << "\r";
				break;
			}
			else
			{
				cout << "\r" << cleanLine << "\r";
				cerr << "<not a number> ";
				cin.clear();
				continue;
			}
		}

		cout << "\r" << cleanLine << "\r";
		cout << "Generating model: ";
		for (size_t i = 0; i < layerSizes.size(); i++)
		{
			cout << layerSizes[i];
			if (i != layerSizes.size() - 1)
				cout << "-";
		}
		cout << endl << endl;

		model = Model(layerSizes);
	}
	else
	{
		cerr << "<wrong input>" << endl;
		initialise(model);
	}
}

void epochsNumber() {
	string answer;
	string cleanLine = "                                                  ";

	cout << "Enter number of epochs: ";
	while (true)
	{
		cin >> answer;
		for (int i = 0; i < 50; i++)
			cout << "\b \b";

		char* p = 0;
		strtoul(answer.c_str(), &p, 10);
		if (!(*p))
		{
			cout << "\r" << cleanLine << "\r";
			numberOfEpochs = stoi(answer);
			break;
		}
		else
		{
			cout << "\r" << cleanLine << "\r";
			cerr << "<not a positive integer> ";
			cin.clear();
			continue;
		}
	}
}

int main()
{
	dataParameters();
	epochsNumber();
	
	Data data;
	Minibatch batch(data);

	Model model;
	initialise(model);
	model.batch = &batch;

	data.readMnist();
	
	model.train(numberOfEpochs, true);
	model.saveToFile();
	
	system("pause");
}