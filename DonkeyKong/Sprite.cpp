//
//  Sprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Sprite.hpp"

Sprite::Sprite(const sf::Texture & spriteMap, std::string type)
: m_frameSize(Maps::SIZE_MAP.find(type) -> second), m_location(Maps::LOC_MAP.find(type) -> second), m_type(type)
{
//    m_sprite.setTextureRect({0,0,0,0});
    m_sprite.setTexture(spriteMap);
    
    m_sprite.setPosition(m_location.first, m_location.second);

}

sf::FloatRect Sprite::getBounds()
{
    return m_sprite.getGlobalBounds();
}

bool Sprite::meet(const std::shared_ptr<Sprite> otherGuy)
{
    return (getBounds().intersects(otherGuy -> getBounds()));
}

std::string Sprite::getType()
{
    return m_type;
}
