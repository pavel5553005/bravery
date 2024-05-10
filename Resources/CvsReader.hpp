#ifndef CSVREADER_HPP_
#define CSVREADER_HPP_

#include <vector>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "../InternalServer/AnimatedTexture.hpp"
#include "../Exception/UnableToLoadFile.hpp"

std::vector<std::vector<std::string>> getTableFromCsv(std::string path)
{
    std::ifstream file(path);
    std::string line;
    std::vector<std::vector<std::string>> table;

    while (std::getline(file, line))
    {
        std::stringstream rowStream(line);
        std::string cell;
        std::vector<std::string> row;

        while (std::getline(rowStream, cell, ','))
        {
            if (cell[0] == '\"')
            {
                cell = cell.substr(1, cell.size() - 2);
            }
            row.push_back(cell);
        }

        table.push_back(row);
    }
    return table;
}

std::vector<sf::Texture>* getTextureFromCsv(std::string path)
{
    std::vector<sf::Texture>* textures = new std::vector<sf::Texture>;
    std::vector<std::vector<std::string>> table = getTableFromCsv(path);
    int x = stoi(table[0][0]);
    int y = stoi(table[0][1]);
    for (int i = 0; i < table.size() - 1; i++)
    {
        // sf::Image image;
        // image.create(x, y, sf::Color(255, 0, 0));

        sf::Texture t;
        try
        {
            if (!t.loadFromFile(table[i + 1][0]))
            {
                throw UnableToLoadFile(table[i + 1][0]);
            }
        }
        catch (UnableToLoadFile e)
        {
            debuger.errorLog(e.what());
        }

        // t.loadFromImage(image);
        std::cout << table[i + 1][0] << std::endl;
        textures->push_back(t);
    }
    std::cout << (*textures)[0].getSize().x << " " << (*textures)[0].getSize().y << std::endl;
    return textures;
}

#endif