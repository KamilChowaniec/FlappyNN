#include "stdafx.h"
#include "NeuralNetwork.h"
#include <random>

NeuralNetwork::NeuralNetwork(int inputs, int hidden, int outputs): iSize(inputs), hSize(hidden), oSize(outputs)
{
	weight[0].set_size(hSize, iSize);
	weight[1].set_size(oSize, hSize);
	bias[0].set_size(hSize);
	bias[1].set_size(oSize);
	for(int i = 0; i < 2; i++) {
		weight[i].for_each([](mat::elem_type& x) {x = random(); });
		bias[i].for_each([](mat::elem_type& x) {x = random(); });
	}
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& network): iSize(network.iSize), hSize(network.hSize), oSize(network.oSize)
{
	int size = 0;
	for(int i = 0; i < 2; i++) {
		weight[i] = network.weight[i];
		size = weight[i].size();
		bias[i] = network.bias[i];
	}
}

vec NeuralNetwork::feedforward(vec inputs)
{
	vec hidden = weight[0] * inputs;
	hidden += bias[0];
	hidden.for_each([](mat::elem_type& val) {val = sigmoid(val); });

	vec outputs = weight[1] * hidden;
	outputs += bias[1];
	outputs.for_each([](mat::elem_type& val) {val = sigmoid(val); });

	return outputs;
}

void NeuralNetwork::mutate(double chance, double amount)
{
	auto mut = [=](mat::elem_type& val) {
		if(random() < chance) {
			std::default_random_engine gen;
			std::normal_distribution<double> dist(0, amount);
			val += dist(gen);
			if(val > 1) val = 1;
			else if(val < -1) val = -1;
		}
	};
	for(int i = 0; i < 2; i++) {
		weight[i].for_each(mut);
		bias[i].for_each(mut);
	}
}

NeuralNetwork NeuralNetwork::crossover(const NeuralNetwork & parent1, const NeuralNetwork & parent2)
{
	NeuralNetwork child(parent1);
	for(int i = 0; i < child.hSize; i++) {
		double r = (random()*+1)*(1 / 2.);
		if(r < 0.5)
			child.changeNeuron(parent2, 1, i);
	}

	for(int i = 0; i < child.oSize; i++) {
		double r = (random()*+1)*(1 / 2.);
		if(r < 0.5)
			child.changeNeuron(parent2, 2, i);
	}

	return child;
}

NeuralNetwork NeuralNetwork::crossover2(const NeuralNetwork & parent1, const NeuralNetwork & parent2)
{
	NeuralNetwork child(parent1);
	int intersection = rand() % (child.hSize + child.oSize - 2) + 1;
	if(intersection < child.hSize) {
		for(int i = intersection; i < child.hSize; i++)
			child.changeNeuron(parent2, 1, i);
		for(int i = 0; i < child.oSize; i++)
			child.changeNeuron(parent2, 2, i);
	}
	else
		for(int i = intersection - child.hSize; i < child.oSize; i++)
			child.changeNeuron(parent2, 2, i);

	return child;
}

void NeuralNetwork::changeNeuron(const NeuralNetwork& from, int layer, int row) {
	if(layer == 1) {
		for(int i = 0; i < from.iSize; i++)
			weight[0].at(row, i) = from.weight[0].at(row, i);
		bias[0].at(row) = from.bias[0].at(row);
	}
	else if(layer == 2) {
		for(int i = 0; i < from.hSize; i++)
			weight[1].at(row, i) = from.weight[1].at(row, i);
		bias[1].at(row) = from.bias[1].at(row);
	}
}

double NeuralNetwork::sigmoid(double x) {
	return 1 / (1 + exp(-x));
}

double NeuralNetwork::random() {
	return (rand() / (double)RAND_MAX) * 2 - 1;
}