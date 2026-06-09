#include "utils.hpp"

void Line::rotate(Point pt){

  const double n = this->getLearningRate();
  const double x = pt.getX();
  const double y = pt.getY();
  const double p = this->getP(x);
  const double m = this->getSlope();

  double newSlope = m + n*x*(y-p);
  this->setM(newSlope);

}

void Line::translate(Point pt){

  const double n = this->getLearningRate();
  const double x = pt.getX();
  const double y = pt.getY();
  const double p = this->getP(x);
  const double b = this->getYIntercept();

  double newYIntercept = b + n*(y-p);
  this->setB(newYIntercept);

}

double drand(){
    double lower_bound = 0;
    double upper_bound = 2;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> unif(lower_bound, upper_bound);

    double a_random_double = unif(rng);

    return a_random_double;
}

double MSE(double real, double p){

  double err = real - p;
  return err * err;

}
