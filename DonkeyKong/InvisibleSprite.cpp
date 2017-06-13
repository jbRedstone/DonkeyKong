//
//  InvisibleSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "InvisibleSprite.hpp"

InvisibleSprite::InvisibleSprite(const sf::Texture & spriteMap, Size size, Location location)
: Sprite(spriteMap, size, location)
{
    m_rectangle.setPosition(m_location.first, m_location.second);
    m_rectangle.setSize(m_frameSize);
}
