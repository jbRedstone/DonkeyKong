//
//  Player.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "AnimatedSprite.hpp"

class Player : public AnimatedSprite
{
public:
    Player(const sf::Texture & spriteMap);
};
#endif /* Player_hpp */
