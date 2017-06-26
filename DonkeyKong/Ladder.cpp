//
//  Ladder.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Ladder.hpp"

Ladder::Ladder(const LocationRectangle locRec)
: InvisibleSprite(Size(locRec.width, locRec.height),
                  Location(locRec.left, locRec.top))
{
}
