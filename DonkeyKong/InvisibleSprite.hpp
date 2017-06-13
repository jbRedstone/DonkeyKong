//
//  InvisibleSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef InvisibleSprite_hpp
#define InvisibleSprite_hpp

#include "Sprite.hpp"

class InvisibleSprite : public Sprite
{
public:
    InvisibleSprite(const sf::Texture & spriteMap, Size size, Location location);
    
private:
    sf::RectangleShape m_rectangle;
};


#endif /* InvisibleSprite_hpp */
