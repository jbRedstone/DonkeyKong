//
//  main.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "Board.hpp"
#include "types.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(Sizes::BOARD_SIZE.x, Sizes::BOARD_SIZE.y), "Save Mario!");
    window.setFramerateLimit(60);
    
    // Load a sprite to display
    sf::Texture spriteMap;
    if (!spriteMap.loadFromFile(resourcePath() + "SpriteMap.png"))
    {
        return EXIT_FAILURE;
    }
    
    Board board(spriteMap);
    
    sf::Clock frameClock;
    bool keyPressed = false;
    std::string lastDirection = "Right";

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        //REWRITE ME
        sf::Time frameTime = frameClock.restart();
        Movement move(0,0);
        
//        //FIXME: add ladder checks + gravity
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            board.getPlayer() -> setCurrentAnimation("RunLeft");
            move.x -= Utilities::WALK_SPEED;
            keyPressed = true;
            lastDirection = "Left";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            board.getPlayer() -> setCurrentAnimation("RunRight");
            move.x += Utilities::WALK_SPEED;
            keyPressed = true;
            lastDirection = "Right";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            board.getPlayer() -> setCurrentAnimation("Climb");
            move.y += Utilities::CLIMB_SPEED;
            keyPressed = true;
            lastDirection = "Climb";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            board.getPlayer() -> setCurrentAnimation("Climb");
            move.x -= Utilities::CLIMB_SPEED;
            keyPressed = true;
            lastDirection = "Climb";
        }
        
        board.getPlayer() -> play();
        board.getPlayer() -> move(move * frameTime.asSeconds());
        
        if (!keyPressed)
        {
            if (lastDirection.compare("Right") == 0)
            {
                board.getPlayer() -> setCurrentAnimation("StandRight");
            }
            else if (lastDirection.compare("Left") == 0)
            {
                board.getPlayer() -> setCurrentAnimation("StandLeft");
            }
            
            board.getPlayer() -> stop();
            
        }
        
        keyPressed = false;
        
        board.getPlayer() -> update(frameTime);

        // Clear screen
        window.clear();

        board.draw(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
