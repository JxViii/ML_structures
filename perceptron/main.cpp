#include "utils.hpp"
#include "perceptron.hpp"
#include <bits/stdc++.h>

void printEquation( const std::vector<double> w , const double bias ){

  char sign;

  std::cout << "\n" << " ẑ = [ ";

  if( !w.empty() ){
    std::cout << std::fixed << std::setprecision(6) << w[0] << "x1";
    for( size_t i{1} ; i < w.size() ; ++i ){

      sign = w[i] >= 0 ? '+' : '-';

      const double wx = std::fabs(w[i]);

      std::cout << ' ' << sign << ' ' << std::fixed << std::setprecision(6) << wx << 'x' << i+1;
    }
  }

  sign = bias >= 0 ? '+' : '-';
  std::cout << ' ' << sign << ' ' << std::fixed << std::setprecision(6) << std::fabs(bias) << " ]" << std::endl;

}

int main(){

  // * Leer datos del CSV
  const std::vector<Email> emails = readEmailsCSV("emails/emails_spam.csv");

  // * Normalizar datos, crear vector de limites por columna y crear normalizedData
  const std::vector<std::pair<double,double>> limits = maxMinValuesEmail(emails);
  std::vector<std::vector<double>> normalizedData;

  for(const Email &email : emails){

    std::vector<double> norm_ele = normalizeEmailLine(email, limits);
    normalizedData.push_back( norm_ele );

  }

  // * Separar features y labels
  std::vector<std::vector<double>> features;
  std::vector<double> labels;
  for( const auto &row : normalizedData ){
    labels.push_back( row.back() );
    features.push_back( {row.begin(), row.end() - 1} );
  }

  // * Inicializar los pesos basados en distribución normal

  const int n_tags = static_cast<int>( features[0].size() );
  std::vector<double> weigths(n_tags,-1);
  initializeWeights(weigths);

  // * Perceptron:

  double eta = .01;
  double bias = .0;
  int epochs = 5000;
  int check = 50;
  double error = 0.0;

  for( int i{} ; i < epochs ; ++i){

    error = 0.0;

    for( size_t j{} ; j < features.size() ; ++j ){

      const auto &x = features[j];
      const double y = labels[j];
      const double perceptron = createPerceptron( x, weigths, bias );

      error += logLoss( sigmoide(perceptron), y );

      updateWeights( weigths, bias, x, perceptron, y, eta );

    }

    if( i % check == 0 ){
      std::cout << "[ Epoch: " << i << " | Error: " << error / features.size() << " ]" << std::endl;

      if( error <= 0.01 ) break;
    }

  }

  printEquation( weigths, bias );

  return 0;

}