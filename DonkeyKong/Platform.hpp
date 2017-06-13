//
//  Platform.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Platform_hpp
#define Platform_hpp

#include "InvisibleSprite.hpp"

class Platform : public InvisibleSprite
{
public:
    Platform(const sf::Texture & spriteMap, InvisibleSpriteMap::const_iterator i);
};

#endif /* Platform_hpp */
