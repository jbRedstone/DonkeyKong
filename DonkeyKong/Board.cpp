//
//  Board.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Board.hpp"

Board::Board(const sf::Texture & spriteMap)
{
    
    m_backRect.setSize(Sizes::BOARD_SIZE);
    m_backRect.setFillColor(Utilities::backgroundBlack);
    
    m_background = std::make_shared<InanimateSprite>(spriteMap, Sizes::BOARD_SIZE, Location(0,0), "Level");
    
    for (InvisibleSpriteMap::const_iterator i = Locations::LADDER_MAP.begin(); i != Locations::LADDER_MAP.end(); ++i)
    {
        m_ladders.emplace_back(std::make_shared<Ladder>(spriteMap, i));
    }
    
    for (InvisibleSpriteMap::const_iterator i = Locations::PLATFORM_MAP.begin(); i != Locations::PLATFORM_MAP.end(); ++i)
    {
        m_platforms.emplace_back(std::make_shared<Platform>(i, spriteMap));
    }
    
    m_player = std::make_shared<Player>(spriteMap);
    
}

void Board::draw(sf::RenderWindow & window)
{
    window.draw(m_backRect);

    m_background -> draw(window);
    m_player -> draw(window);
}

const std::shared_ptr<Player> Board::getPlayer()
{
    return m_player;
}
