//
//  Text.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 27/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Text.hpp"

Text::Text(const sf::Font & font, std::string type, int num, Location barrelLocation)
: m_font(std::make_shared<sf::Font>(font)) , m_type(type), m_printNum(num)
{
    if (m_type.compare("HighScoreNum") == 0)
    {
        m_printNum = 0;
    }
    
    setCharacterSize(100);
    
    setFont(*m_font);
    
    
    if (m_type.compare("Score") == 0 || m_type.compare("HighScore") == 0)
    {
        setFillColor(sf::Color::Red);
        setString(Maps::TEXT_MAP.find(m_type)->second.first);

    }
    else if (m_type.compare("Lives") == 0)
    {
        setFillColor(sf::Color::Blue);
        setString(Maps::TEXT_MAP.find(m_type)->second.first);
    }
    else if (Maps::TEXT_MAP.find(m_type) == Maps::TEXT_MAP.end())
    {
        throw Utilities::Exception("Error: Invalid text type.");
    }
    else if (m_type.compare("EnterPlay") == 0 || m_type.compare("EnterEnd") == 0)
    {
        setFillColor(sf::Color::White);
        setString(Maps::TEXT_MAP.find(m_type)->second.first);
    }
    else if (m_type.compare("GameOver") == 0 || m_type.compare("WellDone") == 0)
    {
        setCharacterSize(200);
        setFillColor(sf::Color::White);
        setString(Maps::TEXT_MAP.find(m_type)->second.first);
    }
    else
    {
        setFillColor(sf::Color::White);
        setString(std::to_string(m_printNum));
    }
    
    setScale(Maps::TEXT_MAP.find(m_type)->second.second.second.x / getGlobalBounds().width,
             Maps::TEXT_MAP.find(m_type)->second.second.second.y / getGlobalBounds().height);
    
    setOrigin(getGlobalBounds().width / 2, 0);
    setPosition(Maps::TEXT_MAP.find(m_type)->second.second.first.first, Maps::TEXT_MAP.find(m_type)->second.second.first.second);

    if (m_type.compare("HighScoreNum") == 0)
    {
        addScore(num);
    }
    
    if (m_type.compare("SmallScoreNum") == 0)
    {
        setPosition(barrelLocation.first, barrelLocation.second);
        m_fadeClock.restart();
        fade();
    }
    
}

void Text::addScore(int num)
{
    if (!(m_type.compare("ScoreNum") == 0 || m_type.compare("HighScoreNum") == 0))
    {
        throw Utilities::Exception("Error: tried to addScore to non-score text");
    }
        
    m_printNum += num;
    setString(std::to_string(m_printNum));
    
    setOrigin(getGlobalBounds().width / 2, 0);
    setPosition(Maps::TEXT_MAP.find(m_type)->second.second.first.first, Maps::TEXT_MAP.find(m_type)->second.second.first.second);
}

void Text::fade()
{
    if (m_type.compare("SmallScoreNum") != 0)
    {
        return;
    }
    
    if (m_fade <= 0)
    {
        m_deleteMe = true;
        return;
    }
    
    if (m_fadeClock.getElapsedTime() >= Consts::SCORE_FADE_TIME)
    {
        setFillColor(sf::Color(255,255,255,m_fade));
        m_fade -= 3;
    }
}

bool Text::getDelete()
{
    return m_deleteMe;
}

