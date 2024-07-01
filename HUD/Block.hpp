#pragma once

#include "HudElement.hpp"
#include <list>
#include <string>

class Block : public HudElement
{
private:
    std::list<HudElement*> elements;
public:
    Block();
    Block(const std::string id);

    void addElement(HudElement& element);

    const std::list<HudElement*> getElements() const { return elements; }

    void draw() const;
    void tick() { for (auto i : elements) { i->tick(); } }

    ~Block();
};

Block::Block() { }

Block::Block(const std::string id) : HudElement(id) { }

void Block::addElement(HudElement& element)
{
    element.setPos(Vector2d(getPos().x + element.getPos().x, getPos().y + element.getPos().y));
    elements.push_back(&element);
    BaS.console.log(element.getId());
}

void Block::draw() const
{
    sf::RectangleShape rect(sf::Vector2f(getSize().x, getSize().y));
    rect.setPosition(getPos().x, getPos().y);
    rect.setFillColor(sf::Color(165, 42, 42));
    BaS.window.draw(rect);

    for (auto i : elements)
    {
        i->draw();
    }
}
Block::~Block()
{
}
