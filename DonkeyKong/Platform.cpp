//
//  Platform.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Platform.hpp"

Platform::Platform(const LocationRectangle locRec, int platformNum)
: InvisibleSprite(Size(locRec.width, locRec.height),
                  Location(locRec.left, locRec.top))
{

    //Rotate all but first, second last and last platforms
    if (platformNum != 0 &&
        platformNum != 1 &&
        platformNum != Maps::PLATFORM_MAP.size() - 1)
    {
        m_rectangle.setRotation(((-2 * (platformNum % 2)) + 1) * (Consts::PLATFORM_ROTATION * (180.f/3.14f)));
    }
}
