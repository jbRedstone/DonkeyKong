//
//  Platform.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Platform.hpp"

Platform::Platform(const sf::Texture & spriteMap, InvisibleSpriteMap::const_iterator i)
: InvisibleSprite(spriteMap,
                  Size(i->second.width, i->second.height),
                  Location(i->second.left, i->second.height))
{}
