//
//  GamePlay.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 22/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#pragma once

#ifndef GamePlay_hpp
#define GamePlay_hpp

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <fstream>
#include "ResourcePath.hpp"
#include "Board.hpp"
#include "types.hpp"
#include "Text.hpp"

class GamePlay
{
public:
    
    GamePlay();
    
    void intro();
    void play();
    void endWin();
    void endLoose();
    
    void loadFiles();
    void pollClose();
    
    
private:
        
    sf::Texture m_spriteMap;
    sf::Font m_font;
    std::ifstream m_highScoreReadFile;
    std::ofstream m_highScoreWriteFile;
    int m_highScoreNum = -1;
    sf::Clock m_clock;
    bool m_keyPressed = false;
    sf::RenderWindow m_window;
    
    bool m_intro = true;
    bool m_play = false;
    bool m_endWin = false;
    bool m_endLoose = false;
    
    bool m_intro2 = false;
    

//    bool m_boardMade = false;
};

#endif /* GamePlay_hpp */
