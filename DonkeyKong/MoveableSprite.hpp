//
//  MoveableSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 23/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef MoveableSprite_hpp
#define MoveableSprite_hpp

#include "AnimatedSprite.hpp"

class MoveableSprite : public AnimatedSprite
{
public:
    MoveableSprite(const sf::Texture & spriteMap, std::string type, std::vector<NumOfFrameType> animationsVector);
    
    virtual void move(Movement & movement);
    
    virtual void environmentCheck(Movement & movement);
    void gravity();
    
    bool atLadderBottom();
    bool atLadderBottom(float & ladderBottomY);
    virtual bool atLadderTop();
    bool atLadderTop(float & ladderTopY);
    
    float platformDistance();
    Location platformCorner(std::string side);

protected:
    
    bool m_onLadder = false;
    InvisibleSpriteMap::const_iterator m_ladderRef = Maps::LADDER_MAP.end();
    
};

#endif /* MoveableSprite_hpp */
