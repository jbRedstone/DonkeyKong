//
//  Player.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "MoveableSprite.hpp"

class Player : public MoveableSprite
{
public:
    
    Player(const sf::Texture & spriteMap);
    
    void move(Movement movement);
    void environmentCheck(Movement & movement);
    void stop();
    void update();
    
    void jump();
    void jumpMove();
    
    void looseLife();
    bool getDying();
    
private:
    
    std::string m_lastDirection = "StandRight";
    
    bool m_isJumping = false;
    float m_jumpVelocity = -1 * Consts::JUMP_HEIGHT;
    
    bool m_dying = false;
    sf::Clock m_deathClock;
};
#endif /* Player_hpp */
