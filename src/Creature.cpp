#include "Creature.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#define MAX_X 1000
#define MAX_Y 1000


#include "NeuralNetwork.h"

Creature::Creature(){
    //ctor
}

Creature::Creature(sf::RenderWindow *window, float *deltaTime){
    this->initialize(window, deltaTime);
    double x = rand() % 1000 + 1;
    double y = rand() % 1000 + 1;
    this->setPosition(x, y);
    this->setRandomColor();
}

Creature::Creature(sf::RenderWindow *window, float *deltaTime, const std::string &genome){
    this->initialize(window, deltaTime);
    this->setGenome(genome);
    this->setPosition(0, 0);
}

Creature::Creature(sf::RenderWindow *window, float *deltaTime, sf::Vector2f position){
    this->initialize(window, deltaTime);
    this->position = position;
    this->setRandomColor();
}

Creature::Creature(sf::RenderWindow *window, float *deltaTime, const std::string &genome, sf::Vector2f position){
    this->initialize(window, deltaTime);
    this->setGenome(genome);
    this->position = position;
}

void Creature::initialize(sf::RenderWindow *window, float *deltaTime){
    this->window = window;
    this->deltaTime = deltaTime;
    this->health = 100;
    this->energy = 100;
}

Creature::~Creature(){
    //dtor
}

void Creature::draw(){
    sf::CircleShape self(this->health/10);
    self.setFillColor(this->color);
    self.setPosition(this->position);

    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = this->position + sf::Vector2f(this->health/10, this->health/10);
    line[0].color  = sf::Color::Red;
    sf::Vector2f position2 = sf::Vector2f(100*std::cos(this->angle), 100*std::sin(this->angle));
    line[1].position = position2 + this->position + sf::Vector2f(this->health/10, this->health/10);
    line[1].color = sf::Color::Red;

    this->window->draw(line);
    this->window->draw(self);
}

void Creature::setRandomColor(){
    int r = rand() % 256;
    int g = rand() % 256;
    int b = rand() % 256;
    this->color = sf::Color(r, g, b);
}

void Creature::setPosition(double x, double y){
    this->position = sf::Vector2f(x, y);
}

void Creature::setGenome(const std::string &genome){
    this->genome = genome;
    this->nn.setGenome(this->genome);

}

void Creature::update(){
    this->consumeEnergy();
    double *outputData = this->getOutputData();
    /*
     * Output Data
     ** 0 acceleration forward
     ** 1 angular acceleration
     ** 2 Memory 1 (sigmoid)
     ** 3 Memory 2
     ** 4 eat
     ** 5 drink
     ** 6 birth
     */
    this->accelerate(NeuralNetwork::sigmoid(outputData[1]), std::abs(outputData[0]));
    this->memory1 = NeuralNetwork::sigmoid(outputData[2]);
    this->memory2 = outputData[3];
    double eat = NeuralNetwork::sigmoid(outputData[3]);
    double drink = NeuralNetwork::sigmoid(outputData[4]);
    this->consumeNutrients(eat, drink);

    double velocityX = (*(this->deltaTime)) * std::cos(this->angle)*this->velocityForward;
    double velocityY = (*(this->deltaTime)) * std::sin(this->angle)*this->velocityForward;
    this->position += sf::Vector2f(velocityX, velocityY);
    this->detectBounds();
}

void Creature::consumeEnergy(){
    this->energy -= (this->position.y/10);
    if(this->energy <= 0){
        this->health--;
        this->energy = 100;
    }
}

void Creature::consumeNutrients(double eat, double drink){
    if(eat >= 0.9 && drink < 0.9){
        this->energy++;
    }else if(drink >= 0.9 && eat < 0.9){
        this->energy++;
    }else if(eat >= 0.9 && drink >= 0.9){
        this->energy--;
    }
}

void Creature::detectBounds(){
    if(this->position.x <= 0){
        this->position.x = 0;
        if(this->health > 0)
            this->health--;
    }
    if(this->position.x >= MAX_X-this->health){
        this->position.x = MAX_X-this->health;
        if(this->health > 0)
            this->health--;
    }
    if(this->position.y <= 0){
        this->position.y = 0;
        if(this->health > 0)
            this->health--;
    }
    if(this->position.y >= MAX_Y-this->health){
       this->position.y = MAX_Y-this->health;
        if(this->health > 0)
            this->health--;
    }
}

void Creature::accelerate(double angularAccel, double accel){
    this->angle += angularAccel * (*(this->deltaTime));
    this->velocityForward = accel;
}

double* Creature::getInputData(){
    double* inputData = new double[NeuralNetwork::INPUT_LENGTH];
    inputData[0] = this->position.x;
    inputData[1] = this->position.y;
    inputData[2] = this->health;
    inputData[3] = this->memory1;
    inputData[4] = this->memory2;
    for(int i = 5; i < NeuralNetwork::INPUT_LENGTH; i++){
        inputData[i] = 0;
    }
    return inputData;
}

double* Creature::getOutputData(){
    double *inputData = this->getInputData();
    nn.feedForward(inputData);
    delete[] inputData;
    return this->nn.getOutputData();
}

std::string Creature::giveBirth(){
    std::string genome = this->nn.getGenome();

    return genome;
}
