//
//  Player.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Player.hpp"

Player::Player(const sf::Texture & spriteMap)
: AnimatedSprite(spriteMap,
                 Size(Sizes::BOARD_SIZE.x * .025, Sizes::BOARD_SIZE.y*.035), //FIXME: move these to the namespace
                 Location(Sizes::BOARD_SIZE.x * .27, Sizes::BOARD_SIZE.y * 0.9),
                 {NumOfFrameType (1, "StandRight"),
                    NumOfFrameType (1, "StandLeft"),
                    NumOfFrameType (2, "RunLeft"),
                    NumOfFrameType (2, "RunRight"),
                    NumOfFrameType (2, "Climb"),
                    NumOfFrameType (2, "EndClimb")})
{

}
