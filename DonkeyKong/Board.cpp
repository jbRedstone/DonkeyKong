//
//  Board.cpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#include "Board.hpp"

#include <iostream>

Board::Board(const sf::Texture & spriteMap, const sf::Font & font, int highScore) : m_spriteMap(spriteMap), m_font(font), m_highScoreNum(highScore)
{
    
    m_backRect.setSize(Consts::BOARD_SIZE);
    m_backRect.setFillColor(Consts::BACKGROUND_BLACK);
    
    m_lives = std::make_shared<InanimateSprite>(m_spriteMap, "Life");
    
    m_inactiveSprites.emplace_back(std::make_shared<InanimateSprite>(m_spriteMap, "Level")); //Background
    m_inactiveSprites.emplace_back(std::make_shared<InanimateSprite>(m_spriteMap, "FourBarrels")); //four Barrels
    
    m_player = std::make_shared<Player>(m_spriteMap);
    m_fireBarrel = std::make_shared<AnimatedSprite>(m_spriteMap, "FireBarrel", std::vector<NumOfFrameType>{NumOfFrameType(2, "FireBarrel")});
    m_DK = std::make_shared<AnimatedSprite>(m_spriteMap, "DK",
                                            std::vector<NumOfFrameType>{NumOfFrameType(1, "DKStand"), NumOfFrameType(6, "DKThrow")});
    m_mario = std::make_shared<AnimatedSprite>(m_spriteMap, "Mario",
                                               std::vector<NumOfFrameType>{NumOfFrameType(1, "MarioStand"), NumOfFrameType(2, "MarioCry")});
    
    m_DK -> play("DKStand");
    
    m_activeSprites.push_back(m_player);
    m_activeSprites.push_back(m_fireBarrel);
    m_activeSprites.push_back(m_DK);
    m_activeSprites.push_back(m_mario);
    
    m_score = std::make_shared<Text>(m_font, "ScoreNum");
    m_highScore = std::make_shared<Text>(m_font, "HighScoreNum", m_highScoreNum);
    
    m_texts.emplace_back(std::make_shared<Text>(m_font, "HighScore"));
    m_texts.emplace_back(std::make_shared<Text>(m_font, "Score"));
    m_texts.emplace_back(std::make_shared<Text>(m_font, "Lives"));
    m_texts.emplace_back(m_score);
    m_texts.emplace_back(m_highScore);

}

void Board::barrelThrow()
{
    if (m_isThrow)
        return;
    
    m_isThrow = true;
    m_throwClock.restart();
    m_DK -> play("DKThrow");
    m_DK -> setLooped(false);
    m_alreadyBarrel = false;
}

void Board::marioCry()
{
    m_marioCry = true;
    m_mario -> play("MarioCry");
    m_cryClock.restart();
}

void Board::draw(sf::RenderWindow & window)
{
    window.draw(m_backRect);
    
    for (std::vector<std::shared_ptr<InanimateSprite>>::const_iterator i = m_inactiveSprites.begin();
         i != m_inactiveSprites.end(); ++i)
    {
        (*i) -> draw(window);
    }
    
    for (std::vector<std::shared_ptr<AnimatedSprite>>::const_iterator i = m_activeSprites.begin();
         i != m_activeSprites.end(); ++i)
    {
        (*i) -> draw(window);
    }
    
    //Draw texts
    for (std::vector<std::shared_ptr<Text>>::const_iterator i = m_texts.begin();
         i != m_texts.end(); ++i)
    {
        window.draw(*(*i));
    }

    
    for (int i = 0; i < m_livesLeft; i++)
    {
        m_lives -> drawRight(window, i * 1.5 * (Maps::SIZE_MAP.find("Life") -> second.x));
    }
    
}

const std::shared_ptr<Player> Board::getPlayer()
{
    return m_player;
}

void Board::update()
{
    if (!m_alreadyBarrel && m_isThrow && m_throwClock.getElapsedTime() > Consts::BARREL_TIME)
    {
        m_alreadyBarrel = true;
        m_activeSprites.emplace_back(std::make_shared<Barrel>(m_spriteMap));
    }
    
    if (m_throwClock.getElapsedTime() > Consts::THROW_TIME)
    {
        m_DK -> play("DKStand");
        m_throwClock.restart();
        m_isThrow = false;
        m_alreadyBarrel = false;
    }
    
    if (m_marioCry && m_cryClock.getElapsedTime() >= Consts::MARIO_CRY_TIME)
    {
        m_mario -> play("MarioStand");
        m_cryClock.restart();
        m_marioCry = false;
    }
    
    if (!(m_mario -> getPaused()) && !m_marioCry && m_cryClock.getElapsedTime() >= Consts::MARIO_STAND_TIME)
    {
        marioCry();
    }
    
    for (std::vector<std::shared_ptr<AnimatedSprite>>::const_iterator i = m_activeSprites.begin();
         i != m_activeSprites.end(); ++i)
    {
        (*i) -> update();
        
    }
    
    if (m_fireBarrel -> meet(m_player))
    {
        m_player -> move(Movement(Consts::WALK_SPEED,0));
    }
    
    for (std::vector<std::shared_ptr<Text>>::iterator i = m_texts.begin();
         i != m_texts.end(); ++i)
    {
        
        (*i)->fade();
        if ((*i) -> getDelete())
        {
//            m_texts.erase(i);
            //FIXME: erase text object
        }
    }
    
    
    //Barrel interactions
    for (std::vector<std::shared_ptr<AnimatedSprite>>::const_iterator i = m_activeSprites.begin();
         i != m_activeSprites.end(); ++i)

    {
        if ((*i) -> getType() == "Barrel" && m_fireBarrel -> meet(*i))
        {
            m_activeSprites.erase(i);
        }
        
        if ((*i) -> getType() == "Barrel" && m_player -> meet(*i))
        {
            looseLife();
        }
        
        if ((*i) -> getType() == "Mario" && m_player -> meet(*i))
        {
            win();
        }
        
        if ((*i) -> getType() == "Barrel" && m_player -> overBarrel(*i))
        {
            m_score -> addScore(100);
            m_scoreNum += 100;
            m_texts.emplace_back(std::make_shared<Text>(m_font, "SmallScoreNum", 100, (*i) -> getLocation()));
            
            if (m_scoreNum > m_highScoreNum)
            {
                m_highScore -> addScore(m_scoreNum - m_highScoreNum);
                m_highScoreNum = m_scoreNum;
            }
        }

    }
    
    if (m_winWait && m_endClock.getElapsedTime() >= Consts::WIN_TIME)
    {
        m_gameWon = true;
    }
    
    if (m_looseWait && m_endClock.getElapsedTime() >= Consts::DEATH_TIME)
    {
        m_gameOver = true;
    }

    
}

void Board::win()
{
    m_inactiveSprites.emplace_back(std::make_shared<InanimateSprite>(m_spriteMap, "Heart"));
    
    m_player -> move(Movement(Maps::LOC_MAP.find("WinSpot") -> second.first - m_player -> getLocation().first,
                              m_player -> getLocation().second));
    m_player -> stop();
    m_player -> setLastDirection("StandLeft");
    m_player -> setCurrentAnimation("StandLeft");
    m_player -> setFreeze(true);
    
    m_mario -> setCurrentAnimation("MarioStand");
    m_mario -> pause();
    
    m_endClock.restart();
    m_winWait = true;
}

void Board::looseLife()
{
    if (getPlayer() -> getDying())
        return;
    
    if (m_livesLeft == 1)
    {
        m_livesLeft --;
        getPlayer() -> looseLife();
        loose();
    }
    else
    {
        m_livesLeft --;
        getPlayer() -> looseLife();
    }
}

void Board::loose()
{
    m_player -> setFreeze(true);
    
    m_endClock.restart();
    m_looseWait = true;
}

int Board::getHighScore()
{
    return m_highScoreNum;
}

bool Board::getGameOver()
{
    return m_gameOver;
}

bool Board::getGameWon()
{
    return m_gameWon;
}

//void Board::remove(std::vector<std::unique_ptr<Text>>::iterator i)
//{
//    Text * temp = (*i).release();
//    if ((*i).get() != nullptr)
//        throw Utilities::Exception("Error: faulty smallText removal.");
//    delete temp;
//}
