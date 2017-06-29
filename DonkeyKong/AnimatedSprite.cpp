//
//  AnimatedSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//

#include "AnimatedSprite.hpp"

#include <iostream>

AnimatedSprite::AnimatedSprite(const sf::Texture & spriteMap,
                               std::string type,
                               std::vector<NumOfFrameType> animationsVector)
: Sprite(spriteMap, type)
{
//    platformUpdate();
    
    m_animations.clear();

    // Populate the map with new Animations, and strings of their names
    for (std::vector<NumOfFrameType>::const_iterator i = animationsVector.begin();
         i != animationsVector.end(); ++i)
    {
        m_animations.insert(std::pair<std::string, std::shared_ptr<Animation>>(i->second,std::make_shared<Animation>(*i)));
        
        if (i == animationsVector.begin())
        {
            m_currentAnimation = m_animations.begin() -> second;
        }
    }
        
    m_currentFrame = m_currentAnimation -> getFirstFrame();
    
    m_sprite.setTextureRect(*m_currentFrame);
    m_sprite.setScale(m_frameSize.x / m_sprite.getGlobalBounds().width,
                      m_frameSize.y / m_sprite.getGlobalBounds().height);


}

void AnimatedSprite::setCurrentAnimation(std::string action)
{
    if (m_currentAnimation != m_animations.find(action) -> second)
    {
        m_currentAnimation = m_animations.find(action) -> second;
        m_currentFrame = m_currentAnimation -> getFirstFrame();
        setFrame(m_currentFrame);
        m_looped = true;
    }
}

void AnimatedSprite::play()
{
    if (m_paused)
        m_clock.restart();
    
    m_paused = false;
}

void AnimatedSprite::play(std::string action)
{
    if (m_currentAnimation != m_animations.find(action) -> second)
        setCurrentAnimation(action);
    
    play();
}

void AnimatedSprite::pause()
{
    m_paused = true;
}

void AnimatedSprite::stop()
{
    m_paused = true;
    if (m_looped)
    {
        m_currentFrame = m_currentAnimation -> getFirstFrame();
        setFrame(m_currentFrame);
    }
}

void AnimatedSprite::setFrame(FrameVector::const_iterator newFrame)
{
    if (m_currentAnimation)
    {
        m_sprite.setTextureRect(m_currentAnimation -> getFrame(newFrame));
    }
    
}

void AnimatedSprite::setLooped(bool b)
{
    m_looped = b;
}

void AnimatedSprite::update()
{
    // if not paused and we have a valid animation
    if (!m_paused && m_currentAnimation)
    {
        // if current time is bigger then the frame time advance one frame
        if (m_clock.getElapsedTime() >= Consts::FRAME_RATE)
        {
            // reset time, but keep the remainder
            m_clock.restart();
            
            m_currentFrame ++;
                
            // if animation has ended
            if (m_currentFrame >= m_currentAnimation -> getLastFrame())
            {
                if (!m_looped)
                {
                    stop();
                    return;
                }
                
                m_currentFrame = m_currentAnimation -> getFirstFrame(); // reset to start
            }
            
            // set the current frame
            setFrame(m_currentFrame);
        }
    }
}

bool AnimatedSprite::getPaused()
{
    return m_paused;
}

void AnimatedSprite::draw(sf::RenderWindow & window)
{
    window.draw(m_sprite);
}
