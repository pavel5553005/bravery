#ifndef ANIMATEDTEXTURE_HPP_
#define ANIMATEDTEXTURE_HPP_

#include <SFML/Graphics.hpp>
#include <list>

class AnimatedTexture
{
private:
    std::list<sf::Texture> textures;
    int index;
    double speed;
public:
    AnimatedTexture(std::list<sf::Texture> textures, double speed);
    sf::Texture getTexture();
    void tick();
    ~AnimatedTexture();
};

AnimatedTexture::AnimatedTexture(std::list<sf::Texture> textures, double speed)
{
    this->textures = textures;
    this->speed = speed;
}

AnimatedTexture::~AnimatedTexture()
{
}


#endif