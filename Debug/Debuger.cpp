#include "Debuger.hpp"

Debuger::Debuger()
{
    this->window = nullptr;
}

void Debuger::setWindow(sf::RenderWindow& window) { this->window = &window; }

void Debuger::setFont(sf::Font& font) { this->font = font; }

void Debuger::consoleLog(std::string text, sf::Color color)
{
    ConsoleText* consoleText = new ConsoleText;
    consoleText->text = text;
    consoleText->color = color;
    consoleText->time = 0;
    console.push_back(consoleText);

    if (console.size() > 20)
    {
        console.pop_front();
    }
}

void Debuger::errorLog(std::string text) { consoleLog("error: " + text, sf::Color(255, 128, 128)); }

void Debuger::drawConsole()
{
    int index = 0;
    for (auto i : console)
    {
        if (i->time >= 600) continue;
        i->time++;
        

        sf::RectangleShape rect(sf::Vector2f(i->text.length() * 10, 16));
        rect.setPosition(0, index * 16);

        sf::Text text;
        text.setFont(font);
        text.setString(i->text);
        text.setCharacterSize(16);
        if (i->time < 515)
        {
            text.setFillColor(i->color);
            rect.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color(i->color.r, i->color.g, i->color.b, (600 - i->time) * 3));
            rect.setFillColor(sf::Color(0, 0, 0, (600 - i->time) * 3));
        }
        text.setPosition(0, index * 16 - 3);
        window->draw(rect);
        window->draw(text);
        index++;
    }
}

Debuger::~Debuger() { }

Debuger debuger;