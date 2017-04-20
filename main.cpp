#include <ctime>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "Population.h"

#define GEN_SIZE 1000

using namespace std;

int main(){
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "GANN");
    sf::Clock clock;
    float deltaTime;

    Population population(&window, &deltaTime);

    while(window.isOpen()){
        deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear(sf::Color::Cyan);
        population.update();
        window.display();
    }

    cout << "Hello world!" << endl;
    return 0;
}
