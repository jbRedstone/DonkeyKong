//
//  AutoMoveSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 23/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef AutoMoveSprite_hpp
#define AutoMoveSprite_hpp

#include "MoveableSprite.hpp"

class AutoMoveSprite : public MoveableSprite
{
public:
    
    AutoMoveSprite(const sf::Texture & spriteMap, std::string type, std::vector<NumOfFrameType> animationsVector);
    
    void autoMove(std::string direction);
    virtual void update();
protected:
    
    std::string m_currentDirection = "Right";
    
};

#endif /* AutoMoveSprite_hpp */
