#pragma once

#include "HudElement.hpp"
#include <SFML/Graphics.hpp>
#include <functional>

class Button : public HudElement
{
private:
    std::string text;
    std::function<void()> onClick;
    bool isHover;
    bool isPressed;
public:
    Button();
    Button(const std::string id);

    void setText(const std::string text) { this->text = text; }
    void setFuncOnClick(const std::function<void()> func) { this->onClick = func; }

    const std::string getText() const { return text; }

    void draw() const;
    void tick();

    ~Button();
};

Button::Button() : HudElement() { }

Button::Button(const std::string id) : HudElement(id) { }

void Button::draw() const
{
    sf::RectangleShape rect(sf::Vector2f(getSize().x, getSize().y));
    rect.setPosition(getPos().x, getPos().y);
    rect.setFillColor(!isHover ? sf::Color(0, 255, 0) : sf::Color(0, 200, 0));
    BaS.window.draw(rect);

    sf::Text text;
    text.setFont(BaS.font);
    text.setString(this->text);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(getPos().x + getSize().x / 2, getPos().y + getSize().y / 2);
    BaS.window.draw(text);
}

void Button::tick()
{
    if (sf::Mouse::getPosition(BaS.window).x >= getPos().x and
        sf::Mouse::getPosition(BaS.window).x <= getPos().x + getSize().x and
        sf::Mouse::getPosition(BaS.window).y >= getPos().y and
        sf::Mouse::getPosition(BaS.window).y <= getPos().y + getSize().y)
    {
        isHover = true;
    } else
    {
        isHover = false;
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and isHover and !isPressed)
    {
        onClick();
        isPressed = true;
    } else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) and isPressed)
    {
        isPressed = false;
    }

}

Button::~Button() { }
