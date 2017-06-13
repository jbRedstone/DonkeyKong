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
    
    //FIXME: add bg bits
    
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
    
    //REWRITE ME
//    for (std::vector<std::unique_ptr<Ladder>>::const_iterator i = m_ladders.begin(); i != m_ladders.end(); ++i)
//    {
//        (*i) -> draw(window);
//    }
//    
//    for (std::vector<std::shared_ptr<Girder>>::const_iterator i = m_girders.begin(); i != m_girders.end(); ++i)
//    {
//        (*i) -> draw(window);
//    }
//    
//    m_peach -> draw(window);
}

//const std::shared_ptr<Peach> Board::getPeach()
//{
//    return m_peach;
//}
