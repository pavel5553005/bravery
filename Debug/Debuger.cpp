#include "Debuger.hpp"
#include "../Camera.hpp"

Debuger::Debuger()
{
    this->window = nullptr;
    this->camera = nullptr;
}

void Debuger::setCamera(Camera* camera) { this->camera = camera; }

void Debuger::setWindow(sf::RenderWindow* window) { this->window = window; }

void Debuger::setFont(sf::Font& font) { this->font = font; }

void Debuger::consoleLog(std::string text)
{
    ConsoleText* consoleText = new ConsoleText;
    consoleText->text = text;
    consoleText->time = 0;
    console.push_back(consoleText);

    if (console.size() > 20)
    {
        console.pop_front();
    }
}

void Debuger::drawRectangle(sf::Color color, Coordinates pos, Vector2d size)
{
    camera->drawRectangle(color, pos, size);
}

void Debuger::drawConsole()
{
    int index = 0;
    for (auto i : console)
    {
        if (i->time >= 600) continue;
        i->time++;

        sf::Text text;
        text.setFont(font);
        text.setString(i->text);
        text.setCharacterSize(16);
        if (i->time < 515)
        {
            text.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color(0, 0, 0, (600 - i->time) * 3));
        }
        // text.setFillColor(sf::Color(255, 255, 255));
        text.setPosition(0, index * 20);
        window->draw(text);
        index++;
    }
}

Debuger::~Debuger() { }

Debuger debuger;