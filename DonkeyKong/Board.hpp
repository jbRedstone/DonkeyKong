//
//  Board.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#pragma once

#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include <memory>
#include <cassert>
#include "AnimatedSprite.hpp"
#include "InanimateSprite.hpp"
#include "Player.hpp"
#include "Barrel.hpp"
#include "Text.hpp"
#include "types.hpp"

using::Maps::LADDER_MAP;
using::Maps::PLATFORM_MAP;
using::std::fstream;

class Board
{
public:
    Board(const sf::Texture & spriteMap, const sf::Font & font, int highScore);
    void draw(sf::RenderWindow & window);
    const std::shared_ptr<Player> getPlayer();
    
    void update();
    
    void barrelThrow();
    void marioCry();
    void looseLife();
    
    void win();
    void loose();
    
    int getHighScore();
    
    bool getGameOver();
    bool getGameWon();
    
private:
    
    sf::RectangleShape m_backRect;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<AnimatedSprite> m_fireBarrel;
    std::shared_ptr<InanimateSprite> m_lives;
    std::shared_ptr<AnimatedSprite> m_DK;
    std::shared_ptr<AnimatedSprite> m_mario;
    std::shared_ptr<Text> m_score;
    std::shared_ptr<Text> m_highScore;

    std::vector<std::shared_ptr<InanimateSprite>> m_inactiveSprites;
    std::vector<std::shared_ptr<AnimatedSprite>> m_activeSprites;
    std::vector<std::shared_ptr<Text>> m_texts;
    
    int m_livesLeft = 3;
    
    const sf::Texture & m_spriteMap;
    const sf::Font & m_font;
    
    sf::Clock m_throwClock;
    sf::Clock m_cryClock;
    sf::Clock m_endClock;
    
    bool m_isThrow = false;
    bool m_alreadyBarrel = false;
    bool m_marioCry = false;
    
    bool m_gameOver = false;
    bool m_gameWon = false;
    bool m_winWait = false;
    bool m_looseWait = false;
    
    int m_highScoreNum;
    int m_scoreNum = 0;
    

};

#endif /* Board_hpp */
