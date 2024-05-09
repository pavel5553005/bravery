#ifndef ANIMATEDTEXTURE_HPP_
#define ANIMATEDTEXTURE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Position/Vector2d.hpp"

class AnimatedTexture
{
private:
    std::vector<sf::Texture>* textures;
    double index;
    double speed;
public:
    AnimatedTexture(std::vector<sf::Texture>* textures, double speed = 1);
    AnimatedTexture();

    sf::Texture* getTexture();

    void tick() { index += speed; }
    bool operator == (const AnimatedTexture& other) { return textures == other.textures; }
    bool operator == (const std::vector<sf::Texture>& other) { return textures == &other; }

    ~AnimatedTexture();
};

AnimatedTexture::AnimatedTexture(std::vector<sf::Texture>* textures, double speed)
{
    this->textures = textures;
    this->speed = speed;
    index = 0;
}

AnimatedTexture::AnimatedTexture()
{
    textures = nullptr;
    speed = 1;
    index = 0;
}

sf::Texture* AnimatedTexture::getTexture()
{
    std::cout << (*textures)[int(index)].getSize().x << std::endl;
    return &(*textures)[int(index)];
}

AnimatedTexture::~AnimatedTexture()
{
}


#endif