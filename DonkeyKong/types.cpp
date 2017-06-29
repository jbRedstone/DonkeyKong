//
//  types.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 15/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "types.hpp"

#include <iostream>

//---------------------------------------------------------------------
using::Utilities::Animation;

Animation::Animation(NumOfFrameType frameRef)
{
    for (int i = 1; i <= frameRef.first; ++i)
    {
        addFrame((*Maps::FRAME_MAP.find(frameRef.second + std::to_string(i))).second);
    }
}

void Animation::addFrame(LocationRectangle locRec)
{
    m_frames.push_back(locRec);
}

FrameVector::const_iterator Animation::getLastFrame() const
{
    return m_frames.end();
}

const LocationRectangle & Animation::getFrame(FrameVector::const_iterator i)
{
    return *i;
}

FrameVector::const_iterator Animation::getFirstFrame() const
{
    return m_frames.begin();
}

//---------------------------------------------------------------------

Utilities::Exception::Exception(std::string message)
{
    std::cout << message << std::endl;
}

//---------------------------------------------------------------------

LocationRectangle operator * (const Size & boardSize, const LocationRectangle & locRec)
{
    return LocationRectangle(locRec.left * boardSize.x,
                             locRec.top * boardSize.y,
                             locRec.width * boardSize.x,
                             locRec.height * boardSize.y);
}

LocationRectangle operator / (const LocationRectangle & locRec, const float & num)
{
    return LocationRectangle(locRec.left / num,
                             locRec.top / num,
                             locRec.width / num,
                             locRec.height / num);
}

Size operator / (const Size & size, const LocationRectangle & locRec)
{
    return Size(size.x / locRec.width, size.y / locRec.height);
}

Size operator * (const Size & s1, const Size s2)
{
    return Size(s1.x * s2.x, s1.y * s2.y);
}

Size operator / (const Size & size, const float & num)
{
    return Size(size.x / num, size.y / num);
}

Location operator * (const Size & size, const Location & location)
{
    return Location(size.x * location.first, size.y * location.second);
}

std::pair<Location, Size> operator * (const Size & size, const std::pair<Location, Size> & pair)
{
    return std::pair<Location, Size>(size * pair.first, size * pair.second);
}

