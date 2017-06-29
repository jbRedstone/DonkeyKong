//
//  GamePlay.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 22/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "GamePlay.hpp"

GamePlay::GamePlay() : m_window(sf::VideoMode(Consts::BOARD_SIZE.x, Consts::BOARD_SIZE.y), "Save Mario!")
{
    // Create the main window
    m_window.setFramerateLimit(Consts::WINDOW_REFRESH_RATE);
    std::srand(std::time(0));
    
    loadFiles();

    if (m_intro)
    {
        intro();
    }
    if (m_play)
    {
        play();
    }
    if (m_endLoose)
    {
        endLoose();
    }
    if (m_endWin)
    {
        endWin();
    }
    

    
}

void GamePlay::loadFiles()
{
    if (!m_spriteMap.loadFromFile(resourcePath() + "SpriteMap.png"))
    {
        throw Utilities::Exception("Error: SpriteMap loading issue");
    }
    
    if (!m_font.loadFromFile(resourcePath() + "arcadeClassic.ttf"))
    {
        throw Utilities::Exception("Error: font loading issue");
    }
    
    m_highScoreReadFile.open(resourcePath() + "highScore.txt");
    
    if (!m_highScoreReadFile.is_open())
    {
        throw Utilities::Exception("Error: highScore save file read-loading issue");
    }
    
    m_highScoreReadFile >> m_highScoreNum;
    
    if (m_highScoreNum == -1)
    {
        throw Utilities::Exception("Error: highScore save file carrying faulty data");
    }
    
    m_highScoreReadFile.close();
}

void GamePlay::pollClose()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // Close window: exit
        if (event.type == sf::Event::Closed)
        {
            m_window.close();
        }
        
        // Escape pressed: exit
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        {
            m_window.close();
        }
    }
}

void GamePlay::intro()
{
    sf::RectangleShape backRect;
    backRect.setSize(Consts::BOARD_SIZE);
    backRect.setFillColor(Consts::BACKGROUND_BLACK);
    
    Text enterPlay(m_font, "EnterPlay");
    AnimatedSprite dkWords(m_spriteMap, "DonkeyKongWords", std::vector<NumOfFrameType>{NumOfFrameType(4, "DonkeyKongWords"),
                                                                                        NumOfFrameType(1, "DonkeyKongWordsGone")});
    AnimatedSprite feminism(m_spriteMap, "#feminism", std::vector<NumOfFrameType>{NumOfFrameType(1, "#feminism"),
        NumOfFrameType(1, "#feminismGone")});
    
    feminism.setCurrentAnimation("#feminismGone");
    
    while (m_window.isOpen() && m_intro)
    {
        
        pollClose();
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            enterPlay.setFillColor(sf::Color(255,255,255,0));
            dkWords.setCurrentAnimation("DonkeyKongWordsGone");
            feminism.setCurrentAnimation("#feminism");
            m_intro2 = true;
            m_clock.restart();
        }
        
        if (m_intro2 && m_clock.getElapsedTime() >= Consts::FEMINISM_TIME)
        {
            m_intro = false;
            m_play = true;
        }
        
        // Clear screen
        m_window.clear();
        
        dkWords.update();
        
        m_window.draw(backRect);
        m_window.draw(enterPlay);
        dkWords.draw(m_window);
        feminism.draw(m_window);
        
        
        // Update the window
        m_window.display();

    }

}


void GamePlay::play()
{
    Board board(m_spriteMap, m_font, m_highScoreNum);
    
    m_clock.restart();
    
    while (m_window.isOpen() && !(m_endLoose || m_endWin))
    {
        pollClose();
    
        Movement move(0,0);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            move.x -= Consts::WALK_SPEED;
            m_keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            move.x += Consts::WALK_SPEED;
            m_keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            move.y -= Consts::CLIMB_SPEED;
            m_keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            move.y += Consts::CLIMB_SPEED;
            m_keyPressed = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            board.getPlayer() -> jump();
            m_keyPressed = true;
        }
        
        if (m_clock.getElapsedTime() > sf::seconds(std::rand() % Consts::BARREL_FREQUENCY))
        {
            board.barrelThrow();
            m_clock.restart();
        }
        
        board.getPlayer() -> move(move);
        board.getPlayer() -> play();
        
        if (!m_keyPressed)
        {
            board.getPlayer() -> stop();
        }
        
        m_keyPressed = false;
        
        board.update();
        
        // Clear screen
        m_window.clear();
        
        board.draw(m_window);
        
        // Update the window
        m_window.display();
        
        m_endWin = board.getGameWon();
        m_endLoose = board.getGameOver();
        
        if (m_highScoreNum < board.getHighScore())
        {
            m_highScoreNum = board.getHighScore();
        }
        
    }
    
    if (m_endLoose && m_endWin)
    {
        throw Utilities::Exception("Error: Game won and lost simultaneously");
    }
    
    m_play = false;
}

void GamePlay::endWin()
{
    
    Text enterPlay(m_font, "EnterEnd");
    Text wellDone(m_font, "WellDone");
    
    m_highScoreWriteFile.open(resourcePath() + "highScore.txt");
    
    if (!m_highScoreWriteFile.is_open())
    {
        throw Utilities::Exception("Error: highScore save file write-loading issue");
    }
    
    std::cout<<m_highScoreNum<<std::endl;
    m_highScoreWriteFile << m_highScoreNum;
    
    m_highScoreWriteFile.close();
    
    while (m_window.isOpen() && m_endWin)
    {
        pollClose();
        
        sf::RectangleShape backRect;
        backRect.setSize(Consts::BOARD_SIZE);
        backRect.setFillColor(Consts::BACKGROUND_BLACK);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            m_window.close();
            return;
        }
        
        // Clear screen
        m_window.clear();
        
        m_window.draw(backRect);
        m_window.draw(enterPlay);
        m_window.draw(wellDone);

        
        // Update the window
        m_window.display();
    }
}

void GamePlay::endLoose()
{
    Text enterPlay(m_font, "EnterEnd");
    Text gameOver(m_font, "GameOver");
    
    while (m_window.isOpen() && m_endLoose)
    {
        pollClose();
        
        sf::RectangleShape backRect;
        backRect.setSize(Consts::BOARD_SIZE);
        backRect.setFillColor(Consts::BACKGROUND_BLACK);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            m_window.close();
            return;
        }
        
        // Clear screen
        m_window.clear();
        
        m_window.draw(backRect);
        m_window.draw(enterPlay);
        m_window.draw(gameOver);
        
        // Update the window
        m_window.display();
        
    }
}






