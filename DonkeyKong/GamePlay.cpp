//
//  GamePlay.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 22/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "GamePlay.hpp"

GamePlay::GamePlay()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(Consts::BOARD_SIZE.x, Consts::BOARD_SIZE.y), "Save Mario!");
    window.setFramerateLimit(Consts::WINDOW_REFRESH_RATE);
    
    // Load a sprite to display
    sf::Texture spriteMap;
    if (!spriteMap.loadFromFile(resourcePath() + "SpriteMap.png"))
    {
        return EXIT_FAILURE; //FIXME: add exception
    }
    
    //FIXME: move all created objects in cpp to hpp as members and functions.
    
    Board board(spriteMap);
    
    sf::Clock m_clock;
    m_clock.restart();
    std::srand(std::time(0));
    
    bool keyPressed = false;
        
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
        
        Movement move(0,0);
        
        //FIXME: add ladder checks + gravity
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            move.x -= Consts::WALK_SPEED;
            keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            move.x += Consts::WALK_SPEED;
            keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            move.y -= Consts::CLIMB_SPEED;
            keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            move.y += Consts::CLIMB_SPEED;
            keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            board.getPlayer() -> jump();
            keyPressed = true;
        }
        
        if (m_clock.getElapsedTime() > sf::seconds(std::rand() % 10))
        {
            board.barrelThrow();
            m_clock.restart();
        }
        
//        if (m_clock.getElapsedTime() > sf::seconds(2))
//        {
//            m_clock.restart();
//        }
//        
        board.getPlayer() -> move(move);
        board.getPlayer() -> play();
        
        if (!keyPressed)
        {
            board.getPlayer() -> stop();
        }
        
        keyPressed = false;
        
        board.update();
        
        // Clear screen
        window.clear();
        
        board.draw(window);
        
        // Update the window
        window.display();
    }
}
