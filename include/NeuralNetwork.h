#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <string>
#include <cmath>

typedef char DNA;

class NeuralNetwork{
public:

    static constexpr double e = 2.718281828459045;

    static const int INPUT_LENGTH = 37;
    static const int HIDDEN_LENGTH = 18;
    static const int OUTPUT_LENGTH = 9;

    NeuralNetwork();
    void feedForward(double inputData[INPUT_LENGTH]);
    double* getOutputData();
    void saveToFile(std::string fileName);
    void loadFromFile(std::string fileName);
    std::string getGenome();
    void setGenome(std::string);

    static double sigmoid(double x){
        return 1/(1+std::pow(NeuralNetwork::e, -x));
    }
private:
    double inputLayer[INPUT_LENGTH];
    double hiddenLayer[HIDDEN_LENGTH];
    double outputLayer[OUTPUT_LENGTH];

    DNA inputHidden[INPUT_LENGTH][HIDDEN_LENGTH];
    DNA hiddenOutput[HIDDEN_LENGTH][OUTPUT_LENGTH];
};

#endif // NEURALNETWORK_H
