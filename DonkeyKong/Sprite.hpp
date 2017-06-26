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

#include <SFML/Graphics.hpp>
#include "types.hpp"

class Sprite
{
public:
    
    Sprite(const sf::Texture & spriteMap, std::string type);
    
    sf::FloatRect getBounds();
    bool meet(std::shared_ptr<Sprite> otherGuy);
    std::string getType();
        
protected:
    
    sf::Sprite m_sprite;

    Size m_frameSize;
    Location m_location;
    std::string m_type;
};

#endif /* Sprite_hpp */
