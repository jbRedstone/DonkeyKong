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
#include <cmath>


class Platform;
//--------------------------Type Definitions------------------------------

typedef std::pair<float, float> Location;
typedef sf::Vector2f Size;
typedef sf::Vector2f Movement;
typedef sf::IntRect LocationRectangle;
typedef std::pair<int, std::string> NumOfFrameType;
typedef std::map<std::string, LocationRectangle> FrameInSpriteMap;
typedef std::multimap<float, LocationRectangle, std::less<float>> InvisibleSpriteMap;
typedef std::multimap<float, float> PlatformRotationMap;
typedef std::vector<LocationRectangle> FrameVector;
typedef std::vector<std::shared_ptr<Platform>> PlatformVector;
typedef std::map<std::string, Size> SizeMap;
typedef std::map<std::string, Location> LocationMap;
typedef std::map<std::string, std::pair<std::string, std::pair<Location, Size>>> TextMap;

//--------------------------Operations---------------------------

LocationRectangle operator * (const Size & boardSize, const LocationRectangle & locRec);
LocationRectangle operator / (const LocationRectangle & locRec, const float & num);
Size operator / (const Size & size, const LocationRectangle & locRec);
Size operator * (const Size & s1, const Size s2);
Location operator * (const Size & size, const Location & location);
Size operator / (const Size & size, const float & num);
std::pair<Location, Size> operator * (const Size & size, const std::pair<Location, Size> & pair);

//--------------------------Namespaces------------------------------

namespace Consts
{
    const Size BOARD_SIZE = {1600.f,1200.f};
    const float CLIMB_SPEED = 3;
    const float WALK_SPEED = 5;
    const float GRAVITY_SPEED = 1;
    const float JUMP_HEIGHT = 12;
    const float PLATFORM_ROTATION = atanf((1.f/16.f) * (BOARD_SIZE.y/BOARD_SIZE.x));
    const sf::Color BACKGROUND_BLACK (7,7,5);
    const sf::Time FRAME_RATE = sf::seconds(0.2);
    const sf::Time THROW_TIME = sf::seconds(1.3);
    const sf::Time BARREL_TIME = sf::seconds(0.75);
    const sf::Time MARIO_STAND_TIME = sf::seconds(4);
    const sf::Time MARIO_CRY_TIME = sf::seconds(2);
    const sf::Time DEATH_TIME = sf::seconds(1.5);
    const sf::Time SCORE_FADE_TIME = sf::seconds(1);
    const sf::Time WIN_TIME = sf::seconds(3);
    const sf::Time FEMINISM_TIME = sf::seconds(0.8);
    const int WINDOW_REFRESH_RATE = 60;
    const int BARREL_FREQUENCY = 5;
    //Fixme: put more here
}

namespace Maps
{
    // This maps the frame/sprite to its location on the sheet
    const FrameInSpriteMap FRAME_MAP =
    {
        {"StandRight1", LocationRectangle(82,0,64,94) },
        {"StandLeft1", LocationRectangle(167,0,64,93) },
        {"RunRight1", LocationRectangle(90,96,82,89) },
        {"RunRight2", LocationRectangle(184,93,64,93) },
        {"RunLeft1", LocationRectangle(104,389,64,93) },
        {"RunLeft2", LocationRectangle(185,393,82,89) },
        {"Climb1", LocationRectangle(90,185,60,105) },
        {"Climb2", LocationRectangle(175,199,67,90) },
        {"EndClimb1", LocationRectangle(82,290,70,98) },
        {"EndClimb2", LocationRectangle(183,290,65,98) },
        {"JumpRight1", LocationRectangle(90,96,82,89) },
        {"JumpLeft1", LocationRectangle(185,393,82,89) },
        {"DieLeft1", LocationRectangle(257,0,117,64) },
        {"DieLeft2", LocationRectangle(374,0,117,64) },
        {"DieRight1", LocationRectangle(257,102,117,64) },
        {"DieRight2", LocationRectangle(374,102,117,64) },
        {"Life", LocationRectangle(254,64,27,37) },
        {"DKStand1", LocationRectangle(0,32,37,32) },
        {"DKThrow3", LocationRectangle(43,0,40,32) },
        {"DKThrow4", LocationRectangle(43,0,40,32) },
        {"DKThrow6", LocationRectangle(0,0,43,32) } ,
        {"DKThrow5", LocationRectangle(0,0,43,32) } ,
        {"DKThrow1", LocationRectangle(38,32,43,32) } ,
        {"DKThrow2", LocationRectangle(38,32,43,32) } ,
        {"Level", LocationRectangle(0,514,224,224) },
        {"BarrelRollRight1", LocationRectangle(0,80,12,10) },
        {"BarrelRollRight2", LocationRectangle(15,80,12,10) },
        {"BarrelRollRight3", LocationRectangle(31,80,12,10) },
        {"BarrelRollRight4", LocationRectangle(48,80,12,10) },
        {"BarrelRollLeft4", LocationRectangle(0,80,12,10) },
        {"BarrelRollLeft3", LocationRectangle(15,80,12,10) },
        {"BarrelRollLeft2", LocationRectangle(31,80,12,10) },
        {"BarrelRollLeft1", LocationRectangle(48,80,12,10) },
        {"BarrelFall1", LocationRectangle(0,91,16,10) },
        {"BarrelFall2", LocationRectangle(18,91,16,10) },
        {"FourBarrels", LocationRectangle(0,101,20,32) },
        {"FireBarrel1", LocationRectangle(0,133,16,30) },
        {"FireBarrel2", LocationRectangle(16,133,16,30) },
        {"MarioCry1", LocationRectangle(0,163,39,15) },
        {"MarioCry2", LocationRectangle(0,178,39,16) },
        {"MarioStand1", LocationRectangle(0,194,12,16) },
        {"Heart", LocationRectangle(0,211,15,13) },
        {"BrokenHeart", LocationRectangle(16,211,16,13) },
        {"DonkeyKongWords1", LocationRectangle(230,497,200,96) },
        {"DonkeyKongWords2", LocationRectangle(230,497,200,96) },
        {"DonkeyKongWords3", LocationRectangle(230,594,200,96) },
        {"DonkeyKongWords4", LocationRectangle(230,594,200,96) },
        {"DonkeyKongWordsGone1", LocationRectangle(230,594,200,96) },
        {"#feminism1", LocationRectangle(5,756,298,44)},
        {"#feminismGone1", LocationRectangle(5,810,298,44)},






    };
    
    const Size boardToLevelRatio = Consts::BOARD_SIZE / (FRAME_MAP.find("Level") -> second);

    
    const SizeMap SIZE_MAP =
    {
        {"Level", Consts::BOARD_SIZE},
        {"Peach", (boardToLevelRatio * Size(12, 16)) / 2},
        {"Barrel", (boardToLevelRatio * Size(12, 10)) / 2},
        {"BarrelFall", (boardToLevelRatio * Size(16, 10)) / 2},
        {"FourBarrels", (boardToLevelRatio * Size(20, 32)) / 2},
        {"FireBarrel", (boardToLevelRatio * Size(16, 30)) / 2},
        {"Life", (boardToLevelRatio * Size(7, 8)) / 2},
        {"DK", (boardToLevelRatio * Size(37, 32)) / 2},
        {"Mario", (boardToLevelRatio * Size(16, 22)) / 2},
        {"Heart", (boardToLevelRatio * Size(15, 13)) / 2},
        {"DonkeyKongWords", (boardToLevelRatio * Size(200, 96))},
        {"#feminism", (boardToLevelRatio * Size(150, 40))},



    };
    
    const LocationMap LOC_MAP =
    {
        {"Level", Location(0,0)},
        {"Peach", boardToLevelRatio * Location(30,204)},
        {"Barrel", boardToLevelRatio * Location(27,42)},
        {"BarrelEnd", boardToLevelRatio * Location(0,215)},
        {"FourBarrels", boardToLevelRatio * Location(0,36)},
        {"FireBarrel", boardToLevelRatio * Location(10,201)},
        {"Life", boardToLevelRatio * Location(200,13)},
        {"DK", boardToLevelRatio * Location(12,36)},
        {"Mario", boardToLevelRatio * Location(88,13)},
        {"WinSpot", boardToLevelRatio * Location(116,13)},
        {"Heart", boardToLevelRatio * Location(102,11)},
        {"DonkeyKongWords", boardToLevelRatio * Location(14,30)},
        {"#feminism", boardToLevelRatio * Location(30,90)},


    };
    
    const TextMap TEXT_MAP =
    {
        {"Score", { "Score" , std::pair<Location, Size>(boardToLevelRatio * Location(16,0) , (boardToLevelRatio / 2) * Size(40,10))}},
        {"HighScore", { "High  Score" , std::pair<Location, Size>(boardToLevelRatio * Location(124,0) , (boardToLevelRatio / 2) * Size(80,10))}},
        {"ScoreNum", { "00000" , std::pair<Location, Size>(boardToLevelRatio * Location(26,7) , (boardToLevelRatio / 2) * Size(6,10))}},
        {"HighScoreNum", { "00000" , std::pair<Location, Size>(boardToLevelRatio * Location(144,7) , (boardToLevelRatio / 2) * Size(6,10))}},
        {"SmallScoreNum", { "100" , std::pair<Location, Size>(boardToLevelRatio * Location(0,0) , (boardToLevelRatio / 2) * Size(9,5))}},
        {"Lives", { "Lives" , std::pair<Location, Size>(boardToLevelRatio * Location(202,0) , (boardToLevelRatio / 2) * Size(40,10))}},
        {"EnterPlay", { "Press  Enter  to  play" , std::pair<Location, Size>(Location(650,1000) , (boardToLevelRatio / 2) * Size(150,10))}},
        {"EnterEnd", { "Press  Enter  to  exit" , std::pair<Location, Size>(Location(650,1000) , (boardToLevelRatio / 2) * Size(150,10))}},
        {"GameOver", { "GAME  OVER" , std::pair<Location, Size>(Location(700,200) , (boardToLevelRatio / 2) * Size(200,40))}},
        {"WellDone", { "WELL  DONE" , std::pair<Location, Size>(Location(700,200) , (boardToLevelRatio / 2) * Size(200,40))}},



    };
    
    
    
    // This maps the y-coordinates of the platforms to their locations on the board
    // (Most the platforms are rotated, so their y-coordinate is based on their highest points, and their location is based on their top left corners)
    const InvisibleSpriteMap PLATFORM_MAP =
        {{boardToLevelRatio.y * 216.f, boardToLevelRatio * LocationRectangle(0,216,112,8)},
        {boardToLevelRatio.y * 215.f, boardToLevelRatio * LocationRectangle(112,215,112,8)},
        {boardToLevelRatio.y * 188.f, boardToLevelRatio * LocationRectangle(0,176,208,8)},
        {boardToLevelRatio.y * 155.f, boardToLevelRatio * LocationRectangle(16,155,208,8)},
        {boardToLevelRatio.y * 122.f, boardToLevelRatio * LocationRectangle(0,110,208,8)},
        {boardToLevelRatio.y * 89.f, boardToLevelRatio * LocationRectangle(16,89,208,8)},
        {boardToLevelRatio.y * 56.f, boardToLevelRatio * LocationRectangle(144,53,64,8)},
        {boardToLevelRatio.y * 52.f, boardToLevelRatio * LocationRectangle(0,52,144,8)},
        {boardToLevelRatio.y * 24.f, boardToLevelRatio * LocationRectangle(88,24,48,8)}};
    
    const PlatformRotationMap PLATFORM_ROTATION_MAP =
        {{boardToLevelRatio.y * 216.f, 0},
        {boardToLevelRatio.y * 215.f, Consts::PLATFORM_ROTATION},
        {boardToLevelRatio.y * 188.f, -1 * Consts::PLATFORM_ROTATION},
        {boardToLevelRatio.y * 155.f, Consts::PLATFORM_ROTATION},
        {boardToLevelRatio.y * 122.f, -1 * Consts::PLATFORM_ROTATION},
        {boardToLevelRatio.y * 89.f, Consts::PLATFORM_ROTATION},
        {boardToLevelRatio.y * 56.f, -1 * Consts::PLATFORM_ROTATION},
        {boardToLevelRatio.y * 52.f, 0},
        {boardToLevelRatio.y * 24.f, 0}};
    
    const float platformGap = boardToLevelRatio.x * 16;
    
    // This maps the x-coordinates of the ladders to their locations on the board, also based on top-left corners, x-coordinate is in the middle
    const InvisibleSpriteMap LADDER_MAP =
        {{boardToLevelRatio.y * 195, boardToLevelRatio * LocationRectangle(184,195,8,16)},
        {boardToLevelRatio.y * 162, boardToLevelRatio * LocationRectangle(32,162,8,16)},
        {boardToLevelRatio.y * 158, boardToLevelRatio * LocationRectangle(96,158,8,24)},
        {boardToLevelRatio.y * 125, boardToLevelRatio * LocationRectangle(112,125,8,24)},
        {boardToLevelRatio.y * 129, boardToLevelRatio * LocationRectangle(184,129,8,16)},
        {boardToLevelRatio.y * 96, boardToLevelRatio * LocationRectangle(32,96,8,16)},
        {boardToLevelRatio.y * 94, boardToLevelRatio * LocationRectangle(72,94,8,20)},
        {boardToLevelRatio.y * 63, boardToLevelRatio * LocationRectangle(184,63,8,16)},
        {boardToLevelRatio.y * 32, boardToLevelRatio * LocationRectangle(128,32,8,20)}};
    
    const float lastLadder = boardToLevelRatio.x * 184;
    const float firstLadder = boardToLevelRatio.x * 32;
    
    const InvisibleSpriteMap BROKEN_LADDER_MAP =
        {{boardToLevelRatio.y * 189, boardToLevelRatio * LocationRectangle(80,189,8,27)},
        {boardToLevelRatio.y * 122, boardToLevelRatio * LocationRectangle(64,122,8,30)},
        {boardToLevelRatio.y * 88, boardToLevelRatio * LocationRectangle(168,88,8,32)},
        {boardToLevelRatio.y * 60, boardToLevelRatio * LocationRectangle(88,60,8,25)}};
    
    
}

namespace Utilities
{

    class Animation
    {
    public:
        Animation(NumOfFrameType frameRef);
        void addFrame(LocationRectangle locRec);
        FrameVector::const_iterator getLastFrame() const;
        const LocationRectangle & getFrame(FrameVector::const_iterator i);
        FrameVector::const_iterator getFirstFrame() const;
    private:
        FrameVector m_frames;
    };
    
    class Exception
    {
    public:
        Exception(std::string message);
    };
}


#endif /* types_hpp */
