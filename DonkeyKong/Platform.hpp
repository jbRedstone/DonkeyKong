//
//  Platform.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Platform_hpp
#define Platform_hpp

#include "InvisibleSprite.hpp"

class Platform : public InvisibleSprite
{
public:
    Platform(const LocationRectangle locRec, int platformNum);
};

#endif /* Platform_hpp */
