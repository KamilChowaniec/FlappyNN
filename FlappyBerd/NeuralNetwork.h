#pragma once
#include <armadillo>
using namespace arma;
using namespace std;
class NeuralNetwork
{
private:
	int iSize;
	int hSize;
	int oSize;
	mat weight[2];
	vec bias[2];
public:
	NeuralNetwork() {}
	NeuralNetwork(int inputs, int hidden, int outputs);
	NeuralNetwork(const NeuralNetwork & network);
	vec feedforward(vec inputs);
	void mutate(double chance, double amount);
	static NeuralNetwork crossover(const NeuralNetwork& parent1, const NeuralNetwork& parent2);
	static NeuralNetwork crossover2(const NeuralNetwork & parent1, const NeuralNetwork & parent2);
	void changeNeuron(const NeuralNetwork & from, int layer, int row);
	static double sigmoid(double x);
	static double random();
};

