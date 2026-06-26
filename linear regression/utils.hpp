#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>
#include <iostream>

class Point
{

private:
  double x;
  double y;

public:

  Point() : x(0), y(0) {}
  Point(double x, double y) : x(x), y(y) {}

  double getX() { return x; }
  double getY() { return y; }
  void setX(double x) { this->x = x; }
  void setY(double y) { this->x = y; }
};

class Line
{

private:
  double m; // slope
  double b; // y-intercept
  double n; // learning rate

public:
  Line() : m(1), b(0), n(.001) {}
  Line(double m, double b, double n)
  {
    this->m = m;
    this->b = b;
    this->n = n;
  }

  double getSlope() { return m; }
  double getYIntercept() { return b; }
  double getLearningRate() { return n; }
  double getP(double r) { return (m * r + b); }

  void setM(double m) { this->m = m; }
  void setB(double b) { this->b = b; }
  void setR(double n) { this->n = n; }

  void rotate(Point p);
  void translate(Point p);
};

double drand();
double MSE(double real, double p);

#endif