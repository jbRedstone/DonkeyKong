//
//  Sprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Sprite.hpp"

Sprite::Sprite(const sf::Texture & spriteMap, Size size, Location location)
: m_frameSize(size), m_location(location)
{
    m_spriteMap = std::make_shared<sf::Texture>(spriteMap);
}
