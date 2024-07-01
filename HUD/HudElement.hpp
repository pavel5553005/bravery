#pragma once

#include <string>
#include "../System/System.hpp"
#include "../InternalServer/Position/Vector2d.hpp"

class HudElement
{
private:
    const std::string id;
    Vector2d pos;
    Vector2d size;
public:
    HudElement();
    HudElement(const std::string id);

    const std::string getId() const { return id; }
    const Vector2d getPos() const { return pos; }
    const Vector2d getSize() const { return size; }

    void setPos(const Vector2d pos) { this->pos = pos; }
    void setSize(const Vector2d size) { this->size = size; }

    virtual void draw() = 0;

    virtual ~HudElement();
};

HudElement::HudElement() : id(BaS.getUnicalId()) { }

HudElement::HudElement(const std::string id) : id(id) { }

HudElement::~HudElement() { BaS.hudIds.remove(id); }