//
//  types.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#pragma once

#ifndef types_hpp
#define types_hpp

#include <vector>
#include <SFML/Graphics.hpp>

//--------------------------Type Definitions------------------------------
typedef std::pair<float, float> Location;
typedef sf::Vector2f Size;
typedef sf::Vector2f Movement;
typedef sf::IntRect LocationRectangle;
typedef std::pair<int, std::string> NumOfFrameType;
typedef std::map<std::string, LocationRectangle> FrameInSpriteMap;
typedef std::map<float, LocationRectangle> InvisibleSpriteMap; //map ladder/platform locations
typedef std::vector<LocationRectangle> FrameVector;
//typedef std::map<int, location> ladderLocations;


//--------------------------Operations---------------------------
LocationRectangle operator * (const Size & boardSize, const LocationRectangle & locRec)
{
    return LocationRectangle(locRec.left * (int)boardSize.x,
                             locRec.top * (int)boardSize.y,
                             locRec.width * (int)boardSize.x,
                             locRec.height * (int)boardSize.y);
}

//--------------------------Namespaces------------------------------


namespace Sizes
{
    const Size BOARD_SIZE = {1600,1200};
    //Fixme: put more here
}

namespace Locations
{
    // This maps the frame/sprite to its location on the sheet
    const FrameInSpriteMap FRAME_MAP =
    {
        {"StandRight1", LocationRectangle(82,0,64,94) },
        {"StandLeft1", LocationRectangle(167,0,64,94) },
        {"RunRight1", LocationRectangle(90,96,82,89) },
        {"RunRight2", LocationRectangle(165,93,60,93) },
        {"RunLeft1", LocationRectangle(104,389,60,93) },
        {"RunLeft2", LocationRectangle(185,393,82,89) },
        {"Climb1", LocationRectangle(90,185,60,105) },
        {"Climb2", LocationRectangle(175,199,67,90) },
        {"EndClimb1", LocationRectangle(82,324,70,64) },
        {"EndClimb2", LocationRectangle(183,290,65,98) },
        {"Girder", LocationRectangle(0,64,16,8) },
        {"Ladder", LocationRectangle(0,72,8,8) },
        {"DKStand", LocationRectangle(0,32,37,32) },
        {"DKThrow", LocationRectangle(0,0,43,32) } ,
        {"Level", LocationRectangle(0,514,224,224) }
    };
    
    // This maps the y-coordinates of the platforms to their locations on the board
    // (Most the platforms are rotated, so their y-coordinate is based on their highest points, and their location is based on their top left corners)
    const InvisibleSpriteMap PLATFORM_MAP =
    {
        {Sizes::BOARD_SIZE.y * 216, Sizes::BOARD_SIZE * LocationRectangle(0,216,112,8)},
        {Sizes::BOARD_SIZE.y * 209, Sizes::BOARD_SIZE * LocationRectangle(112,215,112,8)},
        {Sizes::BOARD_SIZE.y * 176, Sizes::BOARD_SIZE * LocationRectangle(0,176,208,8)},
        {Sizes::BOARD_SIZE.y * 143, Sizes::BOARD_SIZE * LocationRectangle(16,155,208,8)},
        {Sizes::BOARD_SIZE.y * 110, Sizes::BOARD_SIZE * LocationRectangle(0,110,208,8)},
        {Sizes::BOARD_SIZE.y * 77, Sizes::BOARD_SIZE * LocationRectangle(16,89,208,8)},
        {Sizes::BOARD_SIZE.y * 144, Sizes::BOARD_SIZE * LocationRectangle(144,53,64,8)},
        {Sizes::BOARD_SIZE.y * 143, Sizes::BOARD_SIZE * LocationRectangle(0,143,144,8)},
        {Sizes::BOARD_SIZE.y * 24, Sizes::BOARD_SIZE * LocationRectangle(88,24,48,8)}
        
    };
    
    // This maps the x-coordinates of the ladders to their locations on the board, also based on top-left corners, x-coordinate is in the middle
    const InvisibleSpriteMap LADDER_MAP =
    {
        {Sizes::BOARD_SIZE.x * 188, Sizes::BOARD_SIZE * LocationRectangle(184,195,8,16)},
        {Sizes::BOARD_SIZE.x * 36, Sizes::BOARD_SIZE * LocationRectangle(32,162,8,16)},
        {Sizes::BOARD_SIZE.x * 100, Sizes::BOARD_SIZE * LocationRectangle(96,158,8,24)},
        {Sizes::BOARD_SIZE.x * 116, Sizes::BOARD_SIZE * LocationRectangle(112,125,8,24)},
        {Sizes::BOARD_SIZE.x * 188, Sizes::BOARD_SIZE * LocationRectangle(184,129,8,16)},
        {Sizes::BOARD_SIZE.x * 36, Sizes::BOARD_SIZE * LocationRectangle(32,96,8,16)},
        {Sizes::BOARD_SIZE.x * 76, Sizes::BOARD_SIZE * LocationRectangle(72,94,8,20)},
        {Sizes::BOARD_SIZE.x * 188, Sizes::BOARD_SIZE * LocationRectangle(184,63,8,16)},
        {Sizes::BOARD_SIZE.x * 132, Sizes::BOARD_SIZE * LocationRectangle(128,32,8,20)},

    };
    
}

namespace Utilities
{
    const float CLIMB_SPEED = 60;
    const float WALK_SPEED = 80;
    const float GRAVITY_SPEED = 100;
    const sf::Color backgroundBlack (7,7,5);
    const float PLATFORM_ROTATION = 1/16;
    
    class Animation
    {
    public:
        Animation(NumOfFrameType frameRef)
        {
            for (int i = 1; i <= frameRef.first; i++)
                addFrame((*Locations::FRAME_MAP.find(frameRef.second + std::to_string(i))).second);
        }
        void addFrame(LocationRectangle locRec)
        {
            m_frames.push_back(locRec);
        }
        FrameVector::const_iterator getEnd() const
        {
            return m_frames.end();
        }
        const LocationRectangle & getFrame(FrameVector::const_iterator i)
        {
            return *i;
        }
        FrameVector::const_iterator getFirstFrame()
        {
            return m_frames.begin();
        }
    private:
        FrameVector m_frames;
    };
    
}


#endif /* types_hpp */
