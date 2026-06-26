#include "utils.hpp"
#include "perceptron.hpp"
#include <bits/stdc++.h>

int main(){

  // * Leer datos del CSV
  const std::vector<Email> emails = readEmailsCSV("emails/emails_spam.csv");

  // * Normalizar datos
  const std::vector<std::pair<double,double>> limits = maxMinValuesEmail(emails);
  std::vector<std::vector<double>> normalizedData;
  for(const Email &email : emails){
    normalizedData.push_back( normalizeEmailLine(email, limits) );
  }

  // * Separar features y labels
  std::vector<std::vector<double>> features;
  std::vector<double> labels;
  for( const auto &row : normalizedData ){
    labels.push_back( row.back() );
    features.push_back( {row.begin(), row.end() - 1} );
  }

  // * Pesos capa oculta
  // 3x7
  const int n_tags = static_cast<int>( features[0].size() );
  const int n_weights = 3;

  // * Crear la matriz de pesos
  std::vector<std::vector<double>> weightMatrix;
  std::vector<double> biases;

  for( int i{} ; i < n_weights ; ++i ){
    std::vector<double> w_temp(n_tags, -1);
    initializeWeights(w_temp);
    biases.push_back(0.0);
    weightMatrix.push_back(w_temp);
  }

  // * Pesos capa de salida
  std::vector<double> w_out(n_weights, -1);
  double bias_out = 0.0;
  initializeWeights(w_out);

  double eta   = 0.01;
  int epochs   = 5000;
  int check    = 50;
  double error = 0.0;

  for( int i{} ; i < epochs ; ++i ){

    error = 0.0;

    for( size_t j{} ; j < features.size() ; ++j ){

      const auto&  x = features[j];
      const double y = labels[j];

      // ── FORWARD PASS 

      // * Cálculo de los perceptrones

      std::vector<double> output(n_weights);

      for( int pos{} ; pos < n_weights ; ++pos ){
        output[pos] = createPerceptron(
          x, weightMatrix[pos], biases[pos]
        );

        output[pos] = sigmoide(output[pos]);
      }

      // * Cálculo del output

      double mlp_y = createPerceptron(
        output, w_out, bias_out
      );
      double mlp_z = sigmoide(mlp_y);

      // ── BACKWARD PASS

      // * Delta de la capa oculta
      // * Cuanto contriibuye cada neurona al error

      std::vector<double> delta_hidden(n_weights);

      for( int pos{} ; pos < n_weights ; ++pos ){
        // * Básicamente la derivada del sigmoide
        // * σ(x) = 1 / (1 + e⁻ˣ)
        // * σ'(x) = σ(x) · (1 − σ(x))
        delta_hidden[pos] = w_out[pos] * (mlp_z - y) * output[pos] * ( 1 - output[pos] );
      }

      // * Actualizar pesos de la capa de salida (despues de calcular delta_hidden)
      updateWeights(
        w_out, bias_out, output, mlp_y, y, eta, sigmoide
      );

      // * Actualizar pesos de la capa oculta
      // * Usamos delta aquí

      for( int pos{} ; pos < n_weights ; ++pos ){
        updateWeights(weightMatrix[pos], biases[pos], x, delta_hidden[pos], eta);
      }

      // * Log Loss
      error += logLoss(mlp_z, y);

    }

    if( i % check == 0 ){
      std::cout << "[ Epoch: " << i << " | Error: " << error / features.size() << " ]" << std::endl;
    }

  }

  return 0;
}
