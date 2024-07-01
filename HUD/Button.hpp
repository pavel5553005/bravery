#pragma once

#include "HudElement.hpp"

class Button : public HudElement
{
private:
    
public:
    Button();
    Button(const std::string id);



    ~Button();
};

Button::Button()
{
}

Button::~Button()
{
}
