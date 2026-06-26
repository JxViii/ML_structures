#ifndef PERCEPTRON_HPP
#define PERCEPTRON_HPP

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <random>
#include <functional>
#include <cmath>

static constexpr double step( double x ) { return x >= 0 ? 1.0 : 0.0; }
static inline double sigmoide( double x ) { return 1.0 / (1.0 + std::exp(-x)); }

/*
* Function that initializes weights using normal distribution
*/
void initializeWeights(std::vector<double> &weigths);

/*
* Function to get the perceptron
* y = step( w1x1 + w2x2 + ... + wnxn + bias )
*/
double createPerceptron(
  const std::vector<double>& x,
  const std::vector<double>& w,
  double bias = 0
);

/*
* Function to get the error function of the perceptron
* e = | w1x1 + w2x2 + ... + wnxn + bias |
*/
double trueValueError(
  const std::vector<double>& x,
  const std::vector<double>& w,
  double bias = 0
);

/*
* F(x) = log loss
* e = -yln(ŷ) - (1-y)ln(1-ŷ)
*/
double logLoss(
  const double perceptron,
  const int y
);

/*
* Function to update the weights w and the bias 
* w' = w + nx(y - ŷ)
* bias = bias + n(y - ŷ)
*/
void updateWeights(
  std::vector<double> &w,
  double &bias,
  const std::vector<double>& x,
  const double perceptron,
  const int label,
  const double learning_rate,
  const std::function<double(double)> activation
);

/*
* Function to update the weights w and the bias 
* w' = w + nx(y - ŷ)
* bias = bias + n(y - ŷ)
*/
void updateWeights(
  std::vector<double> &w,
  double &bias,
  const std::vector<double>& x,
  double delta,
  double eta
);


#endif