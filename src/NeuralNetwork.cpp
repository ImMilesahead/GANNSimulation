#include "NeuralNetwork.h"
#include "../functions.h"

#include <fstream>
#include <cmath>
#include <cstdlib>

NeuralNetwork::NeuralNetwork(){
    for(int i = 0; i < NeuralNetwork::INPUT_LENGTH; i++){
        for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
            this->inputHidden[i][j] = static_cast<DNA>(rand() % 255 - 127);
        }
    }
    for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
        for(int k = 0; k < NeuralNetwork::OUTPUT_LENGTH; k++){
            this->hiddenOutput[j][k] = static_cast<DNA>(rand() % 255 - 127);
        }
    }
}

void NeuralNetwork::feedForward(double inputData[INPUT_LENGTH]){
    for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
        this->hiddenLayer[j] = 0.0;
        for(int i = 0; i < NeuralNetwork::INPUT_LENGTH; i++){
            this->hiddenLayer[j] += inputData[i] * this->inputHidden[i][j];
        }
        this->hiddenLayer[j] = NeuralNetwork::sigmoid(this->hiddenLayer[j]);
    }
    for(int k = 0; k < NeuralNetwork::OUTPUT_LENGTH; k++){
        this->outputLayer[k] = 0.0;
        for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
            this->outputLayer[k] += this->hiddenLayer[j] * this->hiddenOutput[j][k];
        }
    }
}

double* NeuralNetwork::getOutputData(){
    return this->outputLayer;
}

void NeuralNetwork::saveToFile(std::string fileName){
    std::ofstream myFile;
    myFile.open(fileName);
    myFile << this->getGenome();
    myFile.close();
}

void NeuralNetwork::loadFromFile(std::string fileName){
    std::ifstream myFile;
    myFile.open(fileName);
    std::string genome;
    myFile >> genome;
    myFile.close();
    this->setGenome(genome);
}

std::string NeuralNetwork::getGenome(){
    std::string genome = "";
    for(int i = 0; i < NeuralNetwork::INPUT_LENGTH; i++){
        for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
            genome += convertToBinary(this->inputHidden[i][j]);
        }
    }
    for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
        for(int k = 0; k < NeuralNetwork::OUTPUT_LENGTH; k++){
            genome += convertToBinary(this->hiddenOutput[j][k]);
        }
    }
    return genome;
}

void NeuralNetwork::setGenome(std::string newGenome){
    unsigned int expectedLength = 8 * NeuralNetwork::HIDDEN_LENGTH * (NeuralNetwork::INPUT_LENGTH + NeuralNetwork::OUTPUT_LENGTH);
    if(expectedLength != newGenome.length()){
        return;
    }
    int gene = 0;
    for(int i = 0; i < NeuralNetwork::INPUT_LENGTH; i++){
        for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
            this->inputHidden[i][j] = convertFromBinary(newGenome.substr(gene*8, 8));
            gene++;
        }
    }
    for(int j = 0; j < NeuralNetwork::HIDDEN_LENGTH; j++){
        for(int k = 0; k < NeuralNetwork::OUTPUT_LENGTH; k++){
            this->hiddenOutput[j][k] = convertFromBinary(newGenome.substr(gene*8, 8));
            gene++;
        }
    }
}

