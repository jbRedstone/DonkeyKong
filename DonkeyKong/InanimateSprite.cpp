//
//  InanimateSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "InanimateSprite.hpp"

InanimateSprite::InanimateSprite(const sf::Texture & spriteMap, std::string type)
: Sprite(spriteMap, type)
{
    m_sprite.setTextureRect(Maps::FRAME_MAP.find(type) -> second);
    m_sprite.setScale(m_frameSize.x / m_sprite.getGlobalBounds().width,
                      m_frameSize.y / m_sprite.getGlobalBounds().height);
}

void InanimateSprite::draw(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}

void InanimateSprite::drawRight(sf::RenderWindow &window, float rightShift)
{
    m_location.first += rightShift;
    m_sprite.setPosition(m_location.first, m_location.second);
    window.draw(m_sprite);
    m_location.first -= rightShift;
}
