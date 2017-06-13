//
//  AnimatedSprite.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 12/06/2017.
//

#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "Sprite.hpp"
#include "types.hpp"

using Utilities::Animation;

class AnimatedSprite : public Sprite, public sf::Drawable, public sf::Transformable
{
public:
    
    AnimatedSprite(const sf::Texture & spriteMap, Size size, Location location, std::vector<NumOfFrameType>);
    
    void update(sf::Time deltaTime);
    void play();
    void play(std::string action);
    void pause();
    void stop();
    
    void setCurrentAnimation(std::string action);
    void setFrameTime(sf::Time time);
    void setLooped(bool looped);
    void setFrame(FrameVector::const_iterator newFrame, bool resetTime = true);

    std::shared_ptr<Animation> getCurrentAnimation() const;
    sf::FloatRect getLocalBounds() const;
    sf::FloatRect getGlobalBounds() const;
    bool isLooped() const;
    bool isPlaying() const;
    sf::Time getFrameTime() const;
    
    void draw(sf::RenderWindow & window) ;

private:
    
    std::map<std::string, std::shared_ptr<Animation>> m_animations;
    std::shared_ptr<Animation> m_currentAnimation;
    
    sf::Time m_frameTime = sf::seconds(0.2);
    sf::Time m_currentTime;
    
    FrameVector::const_iterator m_currentFrame;
    
    bool m_isPaused = false;
    bool m_isLooped = true;
    
    sf::Sprite m_sprite;

//    sf::Vertex m_vertices[4];
};


#endif /* AnimatedSprite_hpp */
