//
//  MoveableSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 23/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "MoveableSprite.hpp"

MoveableSprite::MoveableSprite(const sf::Texture & spriteMap, std::string type, std::vector<NumOfFrameType> animationsVector)
: AnimatedSprite(spriteMap, type, animationsVector)
{}

void MoveableSprite::move(Movement & movement)
{
    if (m_frozen)
        return;
    
    environmentCheck(movement);
    
    m_location.first += movement.x;
    m_location.second += movement.y;
    
    gravity();
    
    m_sprite.setPosition(m_location.first, m_location.second);
}

void MoveableSprite::environmentCheck(Movement & movement)
{
    //This function must perform a few functions:
    //1. If not on ladder, keep sprite on platform
    //2. If not on ladder, check left/right for platform end
    //3. If not on ladder, check up/down for ladder bottom/top
    //4. If on ladder, halt left/right
    //5. If on ladder, check for ladder bottom/top
    
    float ladderY = 0;
    
    if (!m_onLadder)
    {
        //If moved off side of platform, and there's no other platform next to it
        if ((movement.x < 0 &&
             m_location.first + movement.x < platformCorner("left").first &&
             m_location.first + movement.x < Maps::platformGap) ||
            (movement.x > 0 &&
             m_location.first + m_frameSize.x + movement.x > platformCorner("right").first &&
             Consts::BOARD_SIZE.x - (m_location.first + m_frameSize.x + movement.x) < Maps::platformGap))
        {
            movement.x = 0;
        }
        //if he's on the top platform, and at its end
        else if ((platformCorner("left").second == Maps::PLATFORM_MAP.begin() -> second.top) &&
                ((movement.x < 0 && m_location.first + movement.x < platformCorner("left").first) ||
                 (movement.x > 0 && m_location.first + m_frameSize.x + movement.x > platformCorner("right").first)))
        {
            movement.x = 0;
        }
        // if moved up or down and is at ladder bottom or top
        else if ((movement.y < 0 && atLadderBottom()) || (movement.y > 0 && atLadderTop()))
        {
            m_onLadder = true;
        }
        else if (movement.y != 0)
        {
            movement.y = 0;
        }
    }
    else
    {
        if (movement.x != 0)
        {
            movement.x = 0;
        }
        else if (movement.y < 0 && atLadderTop(ladderY))
        {
            // auto move off ladder
            m_onLadder = false;
            m_ladderRef = Maps::LADDER_MAP.end();
        }
        else if (movement.y > 0 && atLadderBottom(ladderY))
        {
            // auto move off ladder
            m_onLadder = false;
            m_ladderRef = Maps::LADDER_MAP.end();
        }
    }
    
}

// This funciton will take the movement and adjust it so the character remains on the platform
void MoveableSprite::gravity()
{
    if (platformDistance() != 0 && !m_onLadder)
    {
        m_location.second += (platformDistance() - Maps::boardToLevelRatio.y);
    }
}

//returns true if not on ladder and at its bottom
bool MoveableSprite::atLadderBottom()
{
    float minLadderHeight = (--Maps::LADDER_MAP.end()) -> second.height;
    float maxLadderHeight = (--(--(-- Maps::LADDER_MAP.end()))) -> second.height;
    
    for (InvisibleSpriteMap::const_iterator i =
         Maps::LADDER_MAP.lower_bound(m_location.second + (0.5 * m_frameSize.y) - maxLadderHeight);
         i != Maps::LADDER_MAP.upper_bound(m_location.second + (1.5 * m_frameSize.y) - minLadderHeight);// &&
         ++i)
    {
        
        if (! ((m_location.first + (0.5 * m_frameSize.x)) >= (i -> second.left) &&
              (m_location.first + (0.5 * m_frameSize.x)) <= (i -> second.left) + (i -> second.width)))
            continue;
        
        m_ladderRef = i;
        return !m_onLadder;
    }
    
    return false;
}

// This function returns true in two scenarios:
//1. if the player is not on the ladder, but standing at it's base
//2. if the player is on the ladder, and climbing close to it's base
bool MoveableSprite::atLadderBottom(float & ladderBottomY)
{
    if (m_ladderRef == Maps::LADDER_MAP.end())
    {
        throw Utilities::Exception("Error: m_ladderRef unpopulated.");
    }
    
    //if on ladder, check that bottom of character is 80% down the ladder
    if (m_onLadder && m_location.second + m_frameSize.y >= m_ladderRef -> second.top + (0.8 * m_ladderRef -> second.height))
    {
        ladderBottomY = m_ladderRef -> second.top + m_ladderRef -> second.height;
        return true;
    }
    
    return false;
}

bool MoveableSprite::atLadderTop()
{
    //go through all ladder bases at sprite's aproximate y location (+/- his height from his middle), and iterate through the ladders his x-middle is somewhere on their width
    for (InvisibleSpriteMap::const_iterator i =
         Maps::LADDER_MAP.lower_bound(m_location.second + m_frameSize.y + Maps::PLATFORM_MAP.begin() -> second.height);
         i != Maps::LADDER_MAP.upper_bound(m_location.second + (1.5 * m_frameSize.y) + Maps::PLATFORM_MAP.begin() -> second.height) &&
         ((m_location.first + (0.5 * m_frameSize.x)) >= (i -> second.left) &&
          (m_location.first + (0.5 * m_frameSize.x)) <= (i -> second.left) + (i -> second.width)); ++i)
    {
        m_ladderRef = i;
        return !m_onLadder;
    }
    
    return false;
}

bool MoveableSprite::atLadderTop(float & ladderTopY)
{
    if (m_ladderRef == Maps::LADDER_MAP.end())
    {
        throw Utilities::Exception("Error: m_ladderRef unpopulated.");
    }
    
    //if on ladder, check that top of character is at top of ladder
    if (m_onLadder &&
        m_location.second + m_frameSize.y <= m_ladderRef -> second.top - (0.5 * Maps::PLATFORM_MAP.begin() -> second.height))
    {
        ladderTopY = m_ladderRef -> second.top - Maps::PLATFORM_MAP.begin() -> second.height;
        return true;
    }
    
    return false;
}

//This function recieves distance to the closest platform underneath the sprite's center
float MoveableSprite::platformDistance()
{
    //Set i to point to the next platform down underneath the bottom of the character
    InvisibleSpriteMap::const_iterator i = Maps::PLATFORM_MAP.lower_bound(m_location.second + (0.5* m_frameSize.y));
    
    // Iterate through all the platforms under the character, starting from the closest.
    // If the character is not in it's x-bounds, try the next platform.
    
    while (i != Maps::PLATFORM_MAP.end() &&
           !((m_location.first + (0.5 * m_frameSize.x) >= i -> second.left) &&
             (m_location.first + (0.5 * m_frameSize.x) <= i -> second.left + i -> second.width)))
    {
        ++i;
    }
    
    float distanceToFlatPlatform = (i -> second.top) - (m_location.second + m_frameSize.y);

    
    float distanceFromLeftCornerToSpriteCentre = std::fabsf((i -> second.left) - (m_location.first + (0.5f * m_frameSize.x)));
    float distanceFromFlatPlatformToRotatedPlatform = distanceFromLeftCornerToSpriteCentre * tanf(Maps::PLATFORM_ROTATION_MAP.find(i -> first) -> second);
    
    return distanceToFlatPlatform - distanceFromFlatPlatformToRotatedPlatform;
    
}

// This returns the platorm's requested corner location, based on its rotation.
Location MoveableSprite::platformCorner(std::string side)
{
    //Set i to point to the next platform down underneath the bottom of the character
    InvisibleSpriteMap::const_iterator i = Maps::PLATFORM_MAP.lower_bound(m_location.second + (m_frameSize.y));
    
    // Iterate through all the platforms under the character, starting from the closest.
    // If the character is not in it's x-bounds, try the next platform.
    while (i != Maps::PLATFORM_MAP.end() &&
           !((m_location.first + (0.5 * m_frameSize.x) >= i -> second.left) &&
             (m_location.first + (0.5 * m_frameSize.x) <= i -> second.left + i -> second.width)))
    {
        ++i;
    }
    
    if (side.compare("left") == 0)
    {
        return Location (i -> second.left, i -> second.top);
    }
    else if (side.compare("right") != 0)
    {
        throw Exception("Error: Bad string passed to 'platformCorner' function.");
    }
    
    return Location (i -> second.left + (i -> second.width * cosf(Maps::PLATFORM_ROTATION_MAP.find(i -> first) -> second)),
                     i -> second.top + i -> second.width * sinf(Maps::PLATFORM_ROTATION_MAP.find(i -> first) -> second));
    
}

void MoveableSprite::setFreeze(bool b)
{
    m_frozen = b;
}


