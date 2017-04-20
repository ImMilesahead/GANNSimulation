#ifndef POPULATION_H
#define POPULATION_H

#include <SFML/Graphics.hpp>

#include "Creature.h"

#define BIRTH

#define MIN_POP_SIZE 60

class Population{
public:
    Population();
    Population(sf::RenderWindow*, float*);
    void update();
    void clean();
private:
    sf::RenderWindow *window;
    float *deltaTime;
    Creature *creatures;
    int populationAlive;
    int numCreatures;
    int arraySize;
};

#endif // POPULATION_H
