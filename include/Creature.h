#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <SFML/Graphics.hpp>
#include "NeuralNetwork.h"

class Creature{
public:

    static constexpr double SPEED = 100;
    static constexpr double MAX_ROTATION_SPEED = 10;
    Creature();
    Creature(sf::RenderWindow*, float*);
    Creature(sf::RenderWindow*, float*, sf::Vector2f);
    Creature(sf::RenderWindow*, float*, const std::string&);
    Creature(sf::RenderWindow*, float*, const std::string&, sf::Vector2f);

    void initialize(sf::RenderWindow*, float*);

    virtual ~Creature();

    void update();
    void draw();

    void accelerate(double, double);

    void setRandomColor();
    void setPosition(double, double);
    void setGenome(const std::string&);

    void consumeEnergy();
    void consumeNutrients(double, double);
    void detectBounds();
    double* getInputData();
    double* getOutputData();

    std::string giveBirth();

    NeuralNetwork* getNN() { return &this->nn; }
    int getHealth() const { return this->health; }

protected:

private:
    sf::RenderWindow *window;
    sf::Color color;
    std::string genome;
    NeuralNetwork nn;

    // Behaviour Variables
    double velocityForward;
    double angle;
    double angularVelocity;
    unsigned int energy;
    unsigned int health;
    bool isAlive;
    float *deltaTime;
    bool shouldReproduce;

    double memory1;
    double memory2;

    sf::Vector2f position;


};

#endif // CREATURE_H
