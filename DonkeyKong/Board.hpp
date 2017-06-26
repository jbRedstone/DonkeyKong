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
#include "AnimatedSprite.hpp"
#include "InanimateSprite.hpp"
#include "Player.hpp"
#include "Barrel.hpp"
#include "types.hpp"

using::Maps::LADDER_MAP;
using::Maps::PLATFORM_MAP;

class Board
{
public:
    Board(const sf::Texture & spriteMap);
    void draw(sf::RenderWindow & window);
    const std::shared_ptr<Player> getPlayer();
    
    void update();
    
    void barrelThrow();
    void marioCry();
    void looseLife();
    void gameOver();

    
private:
    
    sf::RectangleShape m_backRect;
    std::shared_ptr<Player> m_player;
    std::shared_ptr<AnimatedSprite> m_fireBarrel;
    std::shared_ptr<InanimateSprite> m_lives;
    std::shared_ptr<AnimatedSprite> m_DK;
    std::shared_ptr<AnimatedSprite> m_mario;

    std::vector<std::shared_ptr<InanimateSprite>> m_inactiveSprites;
    std::vector<std::shared_ptr<AnimatedSprite>> m_activeSprites;
    
    int m_livesLeft = 3;
    
    const sf::Texture & m_spriteMap;
    
    sf::Clock m_throwClock;
    sf::Clock m_cryClock;
    
    bool m_isThrow = false;
    bool m_alreadyBarrel = false;
    bool m_marioCry = false;

};

#endif /* Board_hpp */
