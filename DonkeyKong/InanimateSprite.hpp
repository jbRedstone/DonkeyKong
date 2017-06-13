//
//  InanimateSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef InanimateSprite_hpp
#define InanimateSprite_hpp

#include "Sprite.hpp"

class InanimateSprite : public Sprite
{
public:
    InanimateSprite(const sf::Texture & spriteMap, Size size, Location location, std::string type);
    
    void draw(sf::RenderWindow & window);
private:
    sf::Sprite m_sprite;
};
#endif /* InanimateSprite_hpp */
