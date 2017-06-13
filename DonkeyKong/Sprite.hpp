//
//  Sprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#pragma once

#ifndef Sprite_hpp
#define Sprite_hpp

#include <SFML/Graphics/Texture.hpp>
#include "types.hpp"

class Sprite
{
public:
    
    Sprite(const sf::Texture & spriteMap, Size size, Location location);
    
    virtual void draw();
    
protected:
    
    std::shared_ptr<sf::Texture> m_spriteMap;
    
    Size m_frameSize;
    Location m_location;
};

#endif /* Sprite_hpp */
