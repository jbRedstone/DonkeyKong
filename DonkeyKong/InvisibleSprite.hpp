//
//  InvisibleSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#pragma once

#ifndef InvisibleSprite_hpp
#define InvisibleSprite_hpp

#include "Sprite.hpp"

class InvisibleSprite : public Sprite
{
public:
    InvisibleSprite(Size size, Location location);
    
    sf::FloatRect getRect();
    
    void draw(sf::RenderWindow & window);
    
protected:
    sf::RectangleShape m_rectangle;
};


#endif /* InvisibleSprite_hpp */
