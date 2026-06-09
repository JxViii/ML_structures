#include "utils.hpp"
#include <vector>
#include <fstream>

int main(){

  std::vector<Point> v;

  for(int i{}; i<5; ++i){
    v.emplace_back(drand(), drand());
  }

  std::cout << "V: [ ";
  for(auto &pt: v){
    std::cout << "(" << pt.getX() << "," << pt.getY() << ") ";
  }
  std::cout << "]" << std::endl;

  Line *line = new Line();
  // learning rate of .001;

  double last_mse = INT16_MAX;

  for(int epoch{} ; epoch < 10000; ++epoch){
    for(auto& pt : v){
      line->rotate(pt);
      line->translate(pt);
    }

    if(epoch % 500 == 0){
      double mse = 0;
      for(auto &pt : v){
        mse += MSE(pt.getY(), line->getP(pt.getX()));
      }
      mse /= static_cast<int>(v.size());
      std::cout << "MSE: " << mse << std::endl;

      std::cout << last_mse << " - " << mse << " = " << std::fabs(last_mse - mse) << std::endl;

      if( (std::fabs(last_mse - mse)) < .0001){
        std::cout << "CONVERGENCY ACHIEVED" << std::endl;
        break;
      }

      last_mse = mse;

    }

  }

  // after training, write data
  std::ofstream file("plot.dat");
  for (auto& pt : v) {
      file << pt.getX() << " " << pt.getY() << std::endl;
  }
  file.close();

  std::ofstream script("plot.gp");
  script << "set terminal qt" << std::endl;
  script << "set title 'Linear Regression'" << std::endl;
  script << "m = " << line->getSlope() << std::endl;
  script << "b = " << line->getYIntercept() << std::endl;
  script << "plot 'plot.dat' with points title 'Data', "
        << "m*x+b with lines title 'Fit'" << std::endl;
  script << "pause -1" << std::endl;
  script.close();

  system("gnuplot plot.gp");

  return 0;

}

