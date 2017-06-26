//
//  AutoMoveSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 23/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "AutoMoveSprite.hpp"

AutoMoveSprite::AutoMoveSprite(const sf::Texture & spriteMap, std::string type, std::vector<NumOfFrameType> animationsVector)
: MoveableSprite(spriteMap, type, animationsVector)
{}

void AutoMoveSprite::autoMove(std::string direction)
{
    m_currentDirection = direction;
}

void AutoMoveSprite::update()
{
    Movement movement(0,0);

    if (m_currentDirection.compare("Left") == 0)
    {
        movement.x -= Consts::WALK_SPEED;
    }
    else if (m_currentDirection.compare("Right") == 0)
    {
        movement.x += Consts::WALK_SPEED;
    }
    else if (m_currentDirection.compare("Up") == 0)
    {
        movement.y -= Consts::CLIMB_SPEED;
    }
    else if (m_currentDirection.compare("Down") == 0)
    {
        movement.y += Consts::CLIMB_SPEED;
    }
    else
    {
        throw Exception("Error: AutoMoveSprite moved in invalid direction.");
    }
    
    move(movement);
    
    AnimatedSprite::update();
}
