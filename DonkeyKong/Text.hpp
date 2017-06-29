//
//  Text.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 27/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Text_hpp
#define Text_hpp

#include "types.hpp"

class Text : public sf::Text
{
public:
    
//    Text(const sf::Font & font, std::string type);
//    Text(const sf::Font & font, std::string type, int num = 0);
    Text(const sf::Font & font, std::string type, int num = 0, Location barrelLocation = Location(0,0));

    
//    void draw(const sf::RenderWindow & window);
    
    void addScore(int num);
    void fade();
    
    bool getDelete();
    
private:
    
    std::shared_ptr<sf::Font> m_font;
    
    int m_printNum;
    Size m_textSize;
    std::string m_type;
    sf::Clock m_fadeClock;
    int m_fade = 255;
    bool m_deleteMe = false;

};
#endif /* Text_hpp */
