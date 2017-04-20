#include "Population.h"

Population::Population(){

}

Population::Population(sf::RenderWindow *window, float *deltaTime){
    this->creatures = new Creature[MIN_POP_SIZE];
    this->numCreatures = MIN_POP_SIZE;
    this->window = window;
    this->deltaTime = deltaTime;
    for(int i = 0; i < this->numCreatures; i++){
        this->creatures[i] = Creature(window, deltaTime);
    }
}

void Population::update(){
    this->populationAlive = 0;
    for(int i = 0; i < POPULATION_SIZE; i++){
        if(this->creatures[i].getHealth() > 0){
            this->creatures[i].update();
            this->creatures[i].draw();
            this->populationAlive++;
            double* outputData = this->creatures[i].getOutputData();
            if(outputData[BIRTH] >= 0.9){
                // Make new Creature
            }
        }else{
            this->remove(i);
        }
    }
}

void remove(int index){
    for(int i = index; i < this->numCreatures-1; i++){
        this->creatures[i] = this->creatures[i+1];
    }
    this->numCreatures--;
}
