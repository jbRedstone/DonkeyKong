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
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
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
//        sf::Time frameTime = frameClock.restart();
//        movement move(0,0);
//        
//        //FIXME: add ladder checks + gravity
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
//        {
//            board.getPeach() -> animationSwitch("RunLeft");
//            move.x -= WALK_SPEED;
//            keyPressed = true;
//            lastDirection = "Left";
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
//        {
//            board.getPeach() -> animationSwitch("RunRight");
//            move.x += WALK_SPEED;
//            keyPressed = true;
//            lastDirection = "Right";
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
//        {
//            board.getPeach() -> animationSwitch("Climb");
//            move.y += CLIMB_SPEED;
//            keyPressed = true;
//            lastDirection = "Climb";
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
//        {
//            board.getPeach() -> animationSwitch("Climb");
//            move.x -= CLIMB_SPEED;
//            keyPressed = true;
//            lastDirection = "Climb";
//        }
//        
//        board.getPeach() -> play();
//        board.getPeach() -> move(move * frameTime.asSeconds());
//        
//        if (!keyPressed)
//        {
//            if (lastDirection.compare("Right") == 0)
//            {
//                board.getPeach() -> animationSwitch("StandRight");
//            }
//            else if (lastDirection.compare("Left") == 0)
//            {
//                board.getPeach() -> animationSwitch("StandLeft");
//            }
//            
//            board.getPeach() -> stop();
//            
//        }
        
        keyPressed = false;
        
        board.getPeach() -> update(frameTime);

        // Clear screen
        window.clear();

        board.draw(window);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
