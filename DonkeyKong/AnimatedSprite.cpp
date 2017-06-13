//
//  AnimatedSprite.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//

#include "AnimatedSprite.hpp"

AnimatedSprite::AnimatedSprite(const sf::Texture & spriteMap,
                               Size size,
                               Location location,
                               std::vector<NumOfFrameType> animationsVector)
: Sprite(spriteMap, size, location)
{
    // Populate the map with new Animations, and strings of their names
    for (std::vector<NumOfFrameType>::const_iterator i = animationsVector.begin();
         i != animationsVector.end(); ++i)
    {
        m_animations.insert(std::pair<std::string, std::shared_ptr<Animation>>(i->second,std::make_shared<Animation>(*i)));
    }
    
    m_currentAnimation = std::make_shared<Animation>(animationsVector.begin());
    
    m_currentFrame = m_currentAnimation -> getFirstFrame();
    
    m_sprite.setPosition(m_location.first, m_location.second);
    m_sprite.setScale(m_frameSize.x / m_sprite.getGlobalBounds().width,
                      m_frameSize.y / m_sprite.getGlobalBounds().height);
}

void AnimatedSprite::setCurrentAnimation(std::string action)
{
    m_currentAnimation = m_animations.find(action) -> second;
    m_currentFrame = m_currentAnimation -> getFirstFrame();
    setFrame(m_currentFrame);
}

std::shared_ptr<Animation> AnimatedSprite::getCurrentAnimation() const
{
    return m_currentAnimation;
}

void AnimatedSprite::setFrameTime(sf::Time time)
{
    m_frameTime = time;
}

void AnimatedSprite::play()
{
    m_isPaused = false;
}

void AnimatedSprite::play(std::string action)
{
    if (m_currentAnimation != m_animations.find(action) -> second)
        setCurrentAnimation(action);
    
    m_isPaused = false;
}

void AnimatedSprite::pause()
{
    m_isPaused = true;
}

void AnimatedSprite::stop()
{
    m_isPaused = true;
    m_currentFrame = m_currentAnimation -> getFirstFrame();
    setFrame(m_currentFrame);
}

void AnimatedSprite::setLooped(bool looped)
{
    m_isLooped = looped;
}

sf::FloatRect AnimatedSprite::getLocalBounds() const
{
    sf::IntRect rect = m_currentAnimation -> getFrame(m_currentFrame);
    
    float width = static_cast<float>(std::fabs(rect.width));
    float height = static_cast<float>(std::fabs(rect.height));
    
    return sf::FloatRect(0.f, 0.f, width, height);
}

sf::FloatRect AnimatedSprite::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

bool AnimatedSprite::isLooped() const
{
    return m_isLooped;
}

bool AnimatedSprite::isPlaying() const
{
    return !m_isPaused;
}

sf::Time AnimatedSprite::getFrameTime() const
{
    return m_frameTime;
}

void AnimatedSprite::setFrame(FrameVector::const_iterator newFrame, bool resetTime)
{
    if (m_currentAnimation)
    {
        //calculate new vertex positions and texture coordiantes
        LocationRectangle rect = m_currentAnimation->getFrame(newFrame);
        
        m_sprite.setTextureRect(rect);
    }
    
    if (resetTime)
        m_currentTime = sf::Time::Zero;
    
    // Update sprite size
    m_sprite.setScale(m_frameSize.x / m_sprite.getGlobalBounds().width,
                      m_frameSize.y / m_sprite.getGlobalBounds().height);
}

void AnimatedSprite::update(sf::Time deltaTime)
{
    // if not paused and we have a valid animation
    if (!m_isPaused && m_currentAnimation)
    {
        // add delta time
        m_currentTime += deltaTime;
        
        // if current time is bigger then the frame time advance one frame
        if (m_currentTime >= m_frameTime)
        {
            // reset time, but keep the remainder
            m_currentTime = sf::microseconds(m_currentTime.asMicroseconds() % m_frameTime.asMicroseconds());
            
            // get next Frame index
            if (++m_currentFrame < m_currentAnimation -> getEnd())
                m_currentFrame++;
            else
            {
                // animation has ended
                m_currentFrame = m_currentAnimation -> getFirstFrame(); // reset to start
                
                if (!m_isLooped)
                {
                    m_isPaused = true;
                }
                
            }
            
            // set the current frame, not reseting the time
            setFrame(m_currentFrame, false);
        }
    }
}

void AnimatedSprite::draw(sf::RenderWindow & window)
{
    m_sprite.setTexture(*m_spriteMap);
    window.draw(m_sprite);
}
