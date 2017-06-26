//
//  InvisibleSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "InvisibleSprite.hpp"

InvisibleSprite::InvisibleSprite(Size size, Location location)
: Sprite(size, location)
{    
    m_rectangle.setPosition(m_location.first, m_location.second);
    m_rectangle.setSize(m_frameSize);
    m_rectangle.setFillColor(sf::Color (255,255,255,128));
}

sf::FloatRect InvisibleSprite::getRect()
{
    return m_rectangle.getGlobalBounds();
}

void InvisibleSprite::draw(sf::RenderWindow & window)
{
    window.draw(m_rectangle);
}
