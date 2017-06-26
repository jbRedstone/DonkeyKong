//
//  Barrel.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 23/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Barrel.hpp"

#include <iostream>
#include <ctime>

Barrel::Barrel(const sf::Texture & spriteMap)
: AutoMoveSprite(spriteMap,
                 "Barrel",
                 {NumOfFrameType (4, "BarrelRollRight"),
                     NumOfFrameType (4, "BarrelRollLeft"),
                     NumOfFrameType (2, "BarrelFall")})
{}

void Barrel::move(Movement & movement)
{
    MoveableSprite::environmentCheck(movement);
    
    if (movement.x < 0)
    {
        setCurrentAnimation("BarrelRollLeft");
    }
    else if (movement.x > 0)
    {
        setCurrentAnimation("BarrelRollRight");
    }
    else if (movement.y != 0)
    {
        setCurrentAnimation("BarrelFall");
    }
    
    m_location.first += movement.x;
    m_location.second += movement.y;
    
    gravity();
    
    m_sprite.setPosition(m_location.first, m_location.second);
}

void Barrel::update() //call the content of this function only when a direction update needs to be made, and not all the time...
{
    std::srand(std::time(0));

    if (m_onLadder)
    {
        autoMove("Down");
    }
    else if (atLadderTop() && (lastLadder() || (std::rand() % 219 > 104)))
        // 100 is a 1/3 chance of all three ladders, 109 is a 1/2 chance of two ladders. 104 is a compromise
    {
        m_onLadder = true;
        m_location = Location(m_ladderRef -> second.left + 0.5 * m_ladderRef -> second.width - 0.5 * Maps::SIZE_MAP.find("BarrelFall") -> second.x,
                              m_ladderRef -> second.top -  Maps::SIZE_MAP.find("BarrelFall") -> second.y - Maps::PLATFORM_MAP.begin() -> second.height);
        autoMove("Down");
    }
    else if (platformCorner("right").second == platformCorner("left").second)
    {
        if (platformCorner("left").second <= Consts::BOARD_SIZE.y / 2)
        {
            autoMove("Right");
        }
        else
        {
            autoMove("Left");
        }
    }
    else if (platformCorner("right").second < platformCorner("left").second)
    {
        autoMove("Right");
    }
    else
    {
        autoMove("Left");
    }
    
    AutoMoveSprite::update();

}

bool Barrel::atLadderTop()
{
    if (MoveableSprite::atLadderTop())
        return true;
    
    for (InvisibleSpriteMap::const_iterator i =
         Maps::BROKEN_LADDER_MAP.lower_bound(m_location.second + m_frameSize.y + Maps::PLATFORM_MAP.begin() -> second.height);
         i != Maps::BROKEN_LADDER_MAP.upper_bound(m_location.second + (1.5 * m_frameSize.y) + Maps::PLATFORM_MAP.begin() -> second.height) &&
         ((m_location.first + (0.5 * m_frameSize.x)) >= (i -> second.left) &&
          (m_location.first + (0.5 * m_frameSize.x)) <= (i -> second.left) + (i -> second.width)); ++i)
    {
        
        m_ladderRef = i;
        
        return !m_onLadder;
        
    }
    
    return false;
}

bool Barrel::lastLadder()
{
    if (platformCorner("right").second < platformCorner("left").second)
    {
        return m_location.first >= Maps::lastLadder;
    }
    else
    {
        return m_location.first <= Maps::firstLadder + Maps::LADDER_MAP.begin() -> second.width;

    }
}
