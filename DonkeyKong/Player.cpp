//
//  Player.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Player.hpp"

#include <iostream>

Player::Player(const sf::Texture & spriteMap)
: MoveableSprite(spriteMap,
                 "Peach",
                 {NumOfFrameType (1, "StandRight"),
                    NumOfFrameType (1, "StandLeft"),
                    NumOfFrameType (2, "RunLeft"),
                    NumOfFrameType (2, "RunRight"),
                    NumOfFrameType (2, "Climb"),
                    NumOfFrameType (2, "EndClimb"),
                    NumOfFrameType (1, "JumpRight"),
                    NumOfFrameType (1, "JumpLeft"),
                    NumOfFrameType (2, "DieRight"),
                    NumOfFrameType (2, "DieLeft")})
{

}

void Player::move(Movement movement)
{
    if (m_frozen)
        return;
    
    if (m_dying)
    {
        if (m_deathClock.getElapsedTime() <= Consts::DEATH_TIME)
        {
            return;
        }
        else
        {
            m_dying = false;
            m_sprite.setOrigin(0, 0);
        }
    }
        
    environmentCheck(movement);
    
    m_location.first += movement.x;
    m_location.second += movement.y;
    
    if (!m_isJumping)
        gravity();
    
    m_sprite.setPosition(m_location.first, m_location.second);
    
    if (movement.x < 0)
    {
        if (m_isJumping)
        {
            setCurrentAnimation("JumpLeft");
            m_looped = false;
        }
        else
        {
            setCurrentAnimation("RunLeft");
        }
        
        m_lastDirection = "StandLeft";
    }
    else if (movement.x > 0)
    {
        
        if (m_isJumping)
        {
            setCurrentAnimation("JumpRight");
            m_looped = false;
        }
        else
        {
            setCurrentAnimation("RunRight");
        }
        
        m_lastDirection = "StandRight";
    }
    else if (movement.y != 0 && !m_isJumping)
    {
        if (atLadderTop() || atLadderBottom())
        {
            setCurrentAnimation("EndClimb");
            m_lastDirection = "EndClimb";
            m_looped = false;
        }
        else
        {
            setCurrentAnimation("Climb");
            m_lastDirection = "Climb";
        }

    }
}

void Player::environmentCheck(Movement & movement)
{
    if (m_isJumping && movement.y == m_jumpVelocity && movement.x == 1)
    {
        float temp = movement.y;
        movement.x = 0;
        MoveableSprite::environmentCheck(movement);
        movement.y = temp;
    }
    else
    {
        MoveableSprite::environmentCheck(movement);
    }
        
}

void Player::stop()
{
    
    if (!m_dying)
    {
        setCurrentAnimation(m_lastDirection);
        AnimatedSprite::stop();
    }

}

void Player::jump()
{
    if (!m_onLadder && !m_isJumping)
    {
        if (m_lastDirection.compare("StandLeft") == 0)
        {
            setCurrentAnimation("JumpLeft");
            m_looped = false;
        }
        else if (m_lastDirection.compare("StandRight") == 0 || m_lastDirection.compare("EndClimb") == 0)
        {
            setCurrentAnimation("JumpRight");
            m_lastDirection = "StandRight";
            m_looped = false;
        }
        else
        {
            throw Exception("Error: jumpMove function called illegally.");
        }
        
        m_isJumping = true;
        jumpMove();
    }
}

void Player::jumpMove()
{
    
    if (m_jumpVelocity >= Consts::JUMP_HEIGHT)
    {
        m_isJumping = false;
        gravity();
        m_jumpVelocity = -1 * Consts::JUMP_HEIGHT;
    }
    else
    {
        move(Movement(1, m_jumpVelocity));
        m_jumpVelocity += Consts::GRAVITY_SPEED;

    }
    
}

void Player::update()
{
    if (m_isJumping)
        jumpMove();
    
    AnimatedSprite::update();
}

void Player::looseLife()
{
    stop();

    
    m_onLadder = false;
    m_isJumping = false;
    m_looped = true;
    
    
    if (m_lastDirection.compare("StandLeft") == 0 || m_lastDirection.compare("RunLeft") == 0)
    {
        setCurrentAnimation("DieLeft");
    }
    else
    {
        setCurrentAnimation("DieRight");
    }
    
    m_sprite.setOrigin(0, - m_frameSize.y);
    
    move(Movement(0,0));
    m_dying = true;
    m_deathClock.restart();
    update();
}

bool Player::getDying()
{
    return m_dying;
}

bool Player::overBarrel(std::shared_ptr<AnimatedSprite> barrelPtr)
{
    std::shared_ptr<Barrel> ptr = std::dynamic_pointer_cast<Barrel>(barrelPtr);
    
    if (!ptr)
    {
        throw Utilities::Exception("Error: player checking if jumped over object which is not barrel");
    }
    else if (ptr -> getScored())
    {
        return false;
    }
    
    if (!m_isJumping || meet(barrelPtr))
        return false;
    
    bool overBarrel = false;
    
    for (int i = 1; i != 4; ++i)
    {
        sf::FloatRect squareUnderPlayer = m_sprite.getGlobalBounds();
        squareUnderPlayer.top += m_frameSize.y * i;
        
        overBarrel = overBarrel || squareUnderPlayer.intersects(barrelPtr -> getBounds());
    }
    
    if (overBarrel)
        ptr -> setScored(true);
    
    return overBarrel;
}

void Player::setLastDirection(std::string lastDirection)
{
    m_lastDirection = lastDirection;
}
