#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <filesystem>
#include <string>
#include <iostream>

namespace res {
class Resourses {
private:
    sf::Texture playerTexture, enemyTexture, bulletTexture, mapTexture;
    sf::Font fontJet;
    std::string pathToPlayer, pathToEnemy, pathToBullet, pathToMap, pathToFont;

public:
    Resourses() :
        pathToPlayer("/home/DeltaMain/texture/playerTexture.png"),
        pathToEnemy("/home/DeltaMain/texture/enemyTexture.png"),
        pathToBullet("/home/DeltaMain/texture/bulletTexture.png"),
        pathToMap("/home/DeltaMain/texture/mapTexture.png"),
        pathToFont("/usr/share/fonts/TTF/JetBrainsMonoNerdFont-Regular.ttf")
    {
        if (!playerTexture.loadFromFile(pathToPlayer)) {
            std::cout << "Error load from file " << pathToPlayer << std::endl;
        }
        if (!enemyTexture.loadFromFile(pathToEnemy)) {
            std::cout << "Error load from file " << pathToEnemy << std::endl;
        }
        if (!bulletTexture.loadFromFile(pathToBullet)) {
            std::cout << "Error load from file " << pathToBullet << std::endl;
        }
        if (!mapTexture.loadFromFile(pathToMap)) {
            std::cout << "Error load from file " << pathToMap << std::endl;
        }
        if (!fontJet.openFromFile(pathToFont)) {
            std::cout << "Error load from file " << pathToFont << std::endl;
        }
    }

    sf::Texture& getPlayerTexture() {
        return playerTexture;
    }
    sf::Texture& getEnemyTexture() {
        return enemyTexture;
    }
    sf::Texture& getBulletTexture() {
        return bulletTexture;
    }
    sf::Texture& getMapTexture() {
        return mapTexture;
    }
    sf::Font& getFont() {
        return fontJet;
    }
};
}
