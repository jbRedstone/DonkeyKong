//
//  Barrel.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 23/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Barrel_hpp
#define Barrel_hpp

#include "AutoMoveSprite.hpp"

class Barrel : public AutoMoveSprite
{
public:
    
    Barrel(const sf::Texture & spriteMap);
        
    void move(Movement & movement);
    void update();
    
    bool atLadderTop();
    bool lastLadder();
    
private:
    
    bool m_nextFall;
    
};
#endif /* Barrel_hpp */
