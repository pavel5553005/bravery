#pragma once

#include "HudElement.hpp"
#include <list>
#include <string>
#include "Block.hpp"
#include "Button.hpp"

class HudManager
{
private:
    struct OpenedBlock
    {
        Block* block;
        bool isOpen;
        OpenedBlock(Block* block, bool isOpen) : block(block), isOpen(isOpen) {}
    };
    
    std::list<OpenedBlock*> elements;
public:
    HudManager();

    void addElement(Block& element);
    void tick();
    void draw();
    void openBlock(Block& block);

    ~HudManager();
};

HudManager::HudManager()
{
}

void HudManager::addElement(Block& element)
{
    elements.push_back(new OpenedBlock(&element, false));
}

void HudManager::openBlock(Block& block)
{
    for (auto i : elements)
    {
        if (i->block == &block)
        {
            BaS.console.log("block already open");
            i->isOpen = true;
            return;
        }
    }
}

void HudManager::tick()
{
    for (auto i : elements)
    {
        if (i->isOpen) i->block->tick();
    }
}

void HudManager::draw()
{
    for (auto i : elements)
    {
        if (i->isOpen)
        {
            i->block->draw();
        }
    }
}

HudManager::~HudManager()
{
    for (auto i : elements)
    {
        delete i;
    }
}

HudManager hudManager;