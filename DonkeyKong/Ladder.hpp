//
//  Ladder.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Ladder_hpp
#define Ladder_hpp

#include "InvisibleSprite.hpp"

class Ladder : public InvisibleSprite
{
public:
    Ladder(const sf::Texture & spriteMap, InvisibleSpriteMap::const_iterator i);
};

#endif /* Ladder_hpp */
