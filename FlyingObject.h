//
// Created by Viola Durghalli on 11/20/25.
//

#ifndef FLYINGOBJECT_H
#define FLYINGOBJECT_H
#include <SFML/Graphics.hpp>
#include "SFML/Graphics/RectangleShape.hpp"


class FlyingObject : public sf::RectangleShape {
    sf::Vector2f velocity;

    float gravity;
    float jumpStrength;

public:
    FlyingObject(); //default constructor
    FlyingObject(float size_x, float size_y); // overloaded constructor, allows user to choose size of rect
    //void eventHandler(sf::RenderWindow& window);

    sf::Vector2f get_velocity() const;
    void set_velocity(const sf::Vector2f &velocity);
    void run(const sf::Vector2u &boundaries); // not used

    // We need dt(delta time) to make it move smoothly
    void update(sf::Time dt);

    void jump();

    using sf::RectangleShape::setSize;

};



#endif //FLYINGOBJECT_H
