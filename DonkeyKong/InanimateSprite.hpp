//
//  InanimateSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#pragma once

#ifndef InanimateSprite_hpp
#define InanimateSprite_hpp

#include "Sprite.hpp"

class InanimateSprite : public Sprite
{
public:
    
    InanimateSprite(const sf::Texture & spriteMap, std::string type);
    
    void draw(sf::RenderWindow & window);
    void drawRight(sf::RenderWindow & window, float rightShift);

};
#endif /* InanimateSprite_hpp */
