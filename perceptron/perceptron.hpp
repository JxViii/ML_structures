#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <random>

static constexpr bool step( double x ) { return x >= 0 ? 1 : 0; }

/*
* Function that initializes weights using normal distribution
*/
void initializeWeights(std::vector<double> &weigths);

/*
* Function to get the perceptron
* y = step( w1x1 + w2x2 + ... + wnxn + bias )
*/
double createPerceptron(
  std::vector<double> x,
  std::vector<double> w,
  double bias = 0
);

/*
* Function to get the error function of the perceptron
* e = | w1x1 + w2x2 + ... + wnxn + bias |
*/
double perceptronError(
  std::vector<double> x,
  std::vector<double> w,
  double bias = 0
);

/*
* Function to update the weights w and the bias 
* w' = w + nx(y - ŷ)
* bias = bias + n(y - ŷ)
*/
void updateWeights(
  std::vector<double> &w,
  double &bias,
  const std::vector<double> x,
  const double perceptron,
  const int label,
  const double learning_rate
);


#endif