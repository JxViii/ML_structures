#include "perceptron.hpp"

/*
* Function that initializes weights using normal distribution
*/
void initializeWeights(std::vector<double> &weigths){

  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<double> dist(0.0,1.0);

  for( size_t i{} ; i < weigths.size() ; ++i ) {
    weigths[i] = dist(gen);
  }
  
}

/*
* Function to get the perceptron
* y = step( w1x1 + w2x2 + ... + wnxn + bias)
*/
double createPerceptron(
  const std::vector<double>& x,
  const std::vector<double>& w,
  const double bias
){

  size_t n = x.size();
  size_t n_weights = w.size();

  if( n != n_weights ){
    std::cerr << "How did you make the weights.size() and norm.size() different" << std::endl;
    return -1;
  }

  double y = 0.0;

  for ( size_t i{} ; i < n ; ++i){

    y += w[i]*x[i];

  }

  y += bias;

  return y;

}

/*
* Function to get the error function of the perceptron
* e = | w1x1 + w2x2 + ... + wnxn + bias |
*/
double trueValueError(
  const std::vector<double>& x,
  const std::vector<double>& w,
  const double bias
){

  size_t n = x.size();
  size_t n_weights = w.size();

  if( n != n_weights ){
    std::cerr << "How did you make the weights.size() and norm.size() different" << std::endl;
    return -1;
  }

  double y = 0.0;

  for ( size_t i{} ; i < n ; ++i){

    y += w[i]*x[i];

  }

  y += bias;

  return std::fabs(y);

}

/*
* F(x) = log loss
* e = -yln(ŷ) - (1-y)ln(1-ŷ)
*/
double logLoss(
  const double perceptron,
  const int y
){
  return -y * std::log(perceptron) - (1 - y) * std::log(1 - perceptron);
}

/*
* Function to update the weight w
* w' = w + n(y - ŷ)x
*/
void updateWeights(
  std::vector<double> &w,
  double &bias,
  const std::vector<double>& x,
  const double perceptron,
  const int y,
  const double eta,
  const std::function<double(double)> activation
){

  size_t n = x.size();
  size_t n_weights = w.size();

  if( n != n_weights ){
    std::cerr << "How did you make the weights.size() and norm.size() different" << std::endl;
    return;
  }

  for( size_t i{} ; i < n ; ++i ){

    w[i] = w[i] + eta * x[i] * (y - activation(perceptron));

  }

  bias = bias + eta * (y - activation(perceptron));

}

void updateWeights(
  std::vector<double> &w,
  double &bias,
  const std::vector<double>& x,
  double delta,
  double eta
){

  size_t n = x.size();
  size_t n_weights = w.size();

  if( n != n_weights ){
    std::cerr << "How did you make the weights.size() and norm.size() different" << std::endl;
    return;
  }

  for( size_t i{} ; i < w.size() ; ++i ){
      w[i] -= eta * delta * x[i];
    }
  
    bias -= eta * delta;

}