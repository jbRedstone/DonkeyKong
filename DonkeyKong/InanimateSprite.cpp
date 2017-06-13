//
//  InanimateSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "InanimateSprite.hpp"

InanimateSprite::InanimateSprite(const sf::Texture & spriteMap, Size size, Location location, std::string type)
: Sprite(spriteMap, size, location)
{
    m_sprite.setPosition(m_location.first, m_location.second);
    m_sprite.setScale(m_frameSize.x / m_sprite.getGlobalBounds().width,
                      m_frameSize.y / m_sprite.getGlobalBounds().height);
    m_sprite.setTextureRect(Locations::FRAME_MAP.find(type) -> second);
    m_sprite.setTexture(spriteMap);

}

void InanimateSprite::draw(sf::RenderWindow &window)
{
    window.draw(m_sprite);
}
