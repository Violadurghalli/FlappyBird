#include "Pipe.h"


Pipe::Pipe() : Pipe(48.f,300.f)//default constructor
{
}


Pipe::Pipe(float size_x, float size_y)
{
    setSize({size_x, size_y});
    setPosition({0,0});
}

Pipe::Pipe(float size_x, float size_y, const sf::Texture &texture) : Pipe(size_x, size_y)
{
    setTexture(&texture);
}

sf::Vector2f Pipe::get_velocity() const
{
    return velocity;
}


void Pipe::set_velocity(const sf::Vector2f &velocity)
{
    this->velocity = velocity;
}


void Pipe::run(const sf::Vector2u &boundaries)
{
    velocity.x = 2;
    velocity.y = 0;
    move(velocity);
    sf::Vector2f currentPos = getPosition();
    if(currentPos.x > boundaries.x)
    {
        setPosition({0-getSize().x,currentPos.y}); // have it set up before showing on screen so it shows up more smoothly
    }
}
