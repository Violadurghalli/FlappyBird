//
// Created by Viola Durghalli on 11/20/25.
//

#include "FlyingObject.h"
FlyingObject::FlyingObject() : FlyingObject(25.f, 25.f)
{

}
FlyingObject::FlyingObject(float size_x, float size_y)
{
    setPosition({155,310});
    setSize({size_x, size_y});

    // ^^physics
    velocity = {0.f, 0.f};
    gravity = 800.f;            // pixels per second squared
    jumpStrength = -300.f;
}


sf::Vector2f FlyingObject::get_velocity() const
{
    return velocity;
}
void FlyingObject::set_velocity(const sf::Vector2f &velocity)
{
    this->velocity = velocity;

}
void FlyingObject::run(const sf::Vector2u &boundaries)
{
    velocity.x = 0;
    velocity.y = 0;
    move(velocity);
    sf::Vector2f currentPos = getPosition();
    if(currentPos.x > boundaries.x || currentPos.y > boundaries.y)
    {
        setPosition({});
    }
}

void FlyingObject::update(sf::Time dt)
{
    velocity.y += gravity * dt.asSeconds(); // gravity

    move({0, velocity.y * dt.asSeconds()}); // move object

    setRotation(sf::degrees(velocity.y * 0.05f));    // If falling, look down - if jumping, look up

    if (getPosition().y < 0) setPosition({getPosition().x, 0}); // Don't fly into space
}

void FlyingObject::jump()
{
    // instantly set upward velocity
    velocity.y = jumpStrength;
}
