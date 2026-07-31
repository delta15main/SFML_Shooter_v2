#include <SFML/Graphics.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <memory>
#include <vector>
#include <iostream>
#include <chrono>
#include <cmath>
#include <random>

#include "game.h"
#include "../cor/hitbox.h"
#include "../obj/player.h"
#include "../obj/bullet.h"


namespace gmr {
    Game::Game() :
        window(sf::VideoMode({1920, 1080}), "SFML_Shooter_v2"),
        resourses(),
        player(resourses.getPlayerTexture(), 100, 10, resourses.getFont()),
        world(resourses.getMapTexture()),
        healthText(resourses.getFont()),
        scoreText(resourses.getFont()) {
        camera.setSize({1920, 1080});
        camera.setCenter(player.getPosition());
        for (int i = 0; i < 80; ++i) { bullets.push_back(std::make_shared<blt::Bullet>(resourses.getBulletTexture(), resourses.getFont())); }
    }
    
    void Game::spawnEnemies() {
        for (int i = 0; i < 5; ++i) {
            auto enemy = std::make_shared<enm::Enemy>(resourses.getEnemyTexture(), resourses.getFont());
            enemy->setAlive(true, player.getPosition());
            enemys.push_back(enemy);
        }
    }
    
    sf::Vector2f Game::findNearestEnemy(const sf::Vector2f& playerPos) {
        sf::Vector2f nearestDir = {1.f, 0.f};
        float nearestDist = std::numeric_limits<float>::max();
        bool found = false;
        
        for (auto& e : enemys) {
            if (!e->IsAlive()) continue;
            sf::Vector2f enemyPos = e->getPosition();
            sf::Vector2f diff = enemyPos - playerPos;
            float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
            
            if (dist < nearestDist) {
                nearestDist = dist;
                nearestDir = diff;
                found = true;
            }
        }
        
        if (found) {
            float len = std::sqrt(nearestDir.x * nearestDir.x + nearestDir.y * nearestDir.y);
            if (len > 0) {
                nearestDir.x /= len;
                nearestDir.y /= len;
            }
        }
        
        return nearestDir;
    }
    
    void Game::run() {
        sf::Clock shootClock;
        sf::Clock spawnClock;
        sf::Clock invincibilityClock;
        sf::Clock gameStartClock;
        const float shootDelay = 0.08f;
        const float spawnInterval = 5.0f;
        const float invincibilityDuration = 2.0f;
        const float startDelay = 3.0f;
        bool isInvincible = false;
        bool gameStarted = false;
        
        gameStartClock.restart();
        
        while (window.isOpen()) {
            window.clear(sf::Color::Black);
            playerPos = player.getPosition();
            sf::Vector2f newPosCam;
            sf::Vector2i playerDir = {0, 0};
            
            // Проверка начала игры
            if (!gameStarted && gameStartClock.getElapsedTime().asSeconds() >= startDelay) {
                gameStarted = true;
                spawnEnemies();
                spawnClock.restart();
            }
            
            // Key Verifity
            {
                // Key psessed
                {
                    while (auto event = window.pollEvent()) {
                        if (event->is<sf::Event::Closed>()) { window.close(); }
                    }
                }
                
                // Key isPressed для движения
                {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) { playerDir.y = -1; }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) { playerDir.x = -1; }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) { playerDir.y = 1; }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) { playerDir.x = 1; }
                }
                
                {
                    if (gameStarted && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
                        if (shootClock.getElapsedTime().asSeconds() >= shootDelay) {
                            sf::Vector2f dir = findNearestEnemy(playerPos);
                            
                            for (auto& b : bullets) {
                                if (b->IsAlive()) { continue; }
                                b->setDirection(dir);
                                b->setAlive(true, playerPos);
                                break;
                            }
                            shootClock.restart();
                        }
                    } else {
                        shootClock.restart();
                    }
                }
            }
            
            if (isInvincible && invincibilityClock.getElapsedTime().asSeconds() >= invincibilityDuration) {
                isInvincible = false;
            }
            
            if (gameStarted && spawnClock.getElapsedTime().asSeconds() >= spawnInterval) {
                spawnEnemies();
                spawnClock.restart();
            }
            
            // entity logic                                 
            {
                player.setDirection(playerDir);
                this->update_all(playerPos);
                this->intersections(playerPos, isInvincible, invincibilityClock);
                newPosCam.x = camera.getCenter().x + (playerPos.x - camera.getCenter().x) * 0.3f;
                newPosCam.y = camera.getCenter().y + (playerPos.y - camera.getCenter().y) * 0.3f;
            }
            // Window draw
            {
                camera.setCenter(newPosCam);
                window.setView(camera);
                world.draw(window);
                player.draw(window);
                for ( auto& e : enemys ) { if (e->IsAlive()) { e->draw(window); }}
                for ( auto& b : bullets ) { if (b->IsAlive()) { b->draw(window); }}
                
            }
            // view draw
            {
                healthText.update(window.getSize(), "Health: " + std::to_string(player.getHealth()));
                scoreText.update(window.getSize());
                window.setView(window.getDefaultView());
                healthText.draw(window);
                scoreText.draw(window);
                
                if (!gameStarted) {
                    sf::Text timerText(resourses.getFont(), "");
                    float remaining = startDelay - gameStartClock.getElapsedTime().asSeconds();
                    if (remaining < 0) remaining = 0;
                    timerText.setString("Starting in: " + std::to_string(int(remaining + 1)) + "s");
                    timerText.setCharacterSize(48.f);
                    timerText.setFillColor(sf::Color::White);
                    timerText.setOutlineColor(sf::Color::Black);
                    timerText.setOutlineThickness(2.f);
                    sf::FloatRect bounds = timerText.getGlobalBounds();
                    timerText.setPosition({(1920.f - bounds.size.x) / 2.f, (1080.f - bounds.size.y) / 2.f});
                    window.draw(timerText);
                }
            }
            window.display();
        }
    }
    void Game::update_all(sf::Vector2f& playerPos) {
        player.move(player.getPosition());
        for (auto& e : enemys) { e->move(playerPos); }
        for (auto& b : bullets) { b->move(playerPos); }
    }
    void Game::intersections(sf::Vector2f& playerPos, bool& isInvincible, sf::Clock& invincibilityClock) {
    for (auto& e : enemys) {
        if (!e->IsAlive()) continue;
        
        sf::Vector2f diff = e->getPosition() - playerPos;
        float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
        int damage = 1;
        if (dist < 100.f) {
            damage = 5;
        } else if (dist < 200.f) {
            damage = 3;
        } else if (dist < 350.f) {
            damage = 2;
        }
        
        for (auto& b : bullets) {
            if (!b->IsAlive()) continue;
            if (e->getHitbox().intersects(b->getHitbox())) {
                e->setHealth(e->getHealth() - damage);
                b->setAlive(false, playerPos);
                if (e->getHealth() <= 0) {
                    e->setAlive(false, playerPos);
                    scoreText.addScore(damage);
                    scoreText.addKill();
                }
                break;
            }
        }
    }

    for (auto& e : enemys) {
        if (!e->IsAlive()) continue;
        if (e->getHitbox().intersects(player.getHitbox())) {
            if (isInvincible) {
                continue;
            }
            
            player.setHealth(player.getHealth() - 5);
            
            isInvincible = true;
            invincibilityClock.restart();
            
            if (player.getHealth() <= 0) {
                window.close();
                return;
            }
            
            sf::Vector2f knockback = e->getPosition() - playerPos;
            float len = std::sqrt(knockback.x * knockback.x + knockback.y * knockback.y);
            if (len > 0) {
                knockback.x /= len;
                knockback.y /= len;
                sf::Vector2f newEnemyPos = e->getPosition() + knockback * 50.f;
                if (newEnemyPos.x < 0.f) newEnemyPos.x = 0.f;
                if (newEnemyPos.x > utl::get_max_size()) newEnemyPos.x = utl::get_max_size();
                if (newEnemyPos.y < 0.f) newEnemyPos.y = 0.f;
                if (newEnemyPos.y > utl::get_max_size()) newEnemyPos.y = utl::get_max_size();
                e->setPosition(newEnemyPos);
            }
            
            return;
        }
    }
}
}
