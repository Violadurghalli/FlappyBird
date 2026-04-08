//
// Created by Viola Durghalli on 11/24/25.
//

#ifndef PIPE_H
#define PIPE_H
#include <SFML/Graphics.hpp>
#include <iostream>

class Pipe : public sf::RectangleShape{
    sf::Vector2f velocity;

public:
    Pipe(); //default constructor
    Pipe(float size_x, float size_y);
    Pipe(float size_x, float size_y, const sf::Texture& texture); // overloaded constructor, allows user to choose size of rect
    //void eventHandler(sf::RenderWindow& window);


    sf::Vector2f get_velocity() const;
    void set_velocity(const sf::Vector2f &velocity);
    void run(const sf::Vector2u &boundaries);
    bool moving;

};



#endif //PIPE_H
