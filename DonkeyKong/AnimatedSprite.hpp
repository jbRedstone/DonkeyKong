//
//  AnimatedSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//
#pragma once

#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "Sprite.hpp"
#include "Platform.hpp"
#include "types.hpp"

using Utilities::Animation;
using Utilities::Exception;

class AnimatedSprite : public Sprite
{
public:
    
    AnimatedSprite(const sf::Texture & spriteMap, std::string type, std::vector<NumOfFrameType> animationsVector);
    
    virtual void update();
    void play();
    void play(std::string action);
    void pause();
    virtual void stop();

    void setLooped(bool b);
    void setCurrentAnimation(std::string action);
    void setFrame(FrameVector::const_iterator newFrame);
    
    void draw(sf::RenderWindow & window);

protected:
    
    std::map<std::string, std::shared_ptr<Animation>> m_animations;
    std::shared_ptr<Animation> m_currentAnimation;
    
    sf::Clock m_clock;
    
    FrameVector::const_iterator m_currentFrame;
    
    bool m_paused = false;
    bool m_looped = true;
    
    sf::CircleShape m_dot;
    sf::CircleShape m_dot2;
};


#endif /* AnimatedSprite_hpp */
