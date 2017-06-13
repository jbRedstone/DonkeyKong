//
//  Board.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <vector>
#include <memory>
#include "Sprite.hpp"
#include "Ladder.hpp"
#include "Platform.hpp"
#include "Player.hpp"
#include "types.hpp"

class Board
{
public:
    Board(const sf::Texture & spriteMap);
    void draw(sf::RenderWindow & window);
    const std::shared_ptr<Player> getPlayer();
    
private:
    sf::RectangleShape m_backRect;
    sf::Sprite m_background;
    std::vector<std::shared_ptr<Platform>> m_platforms;
    std::vector<std::shared_ptr<Ladder>> m_ladders;
    std::shared_ptr<Player> m_player;
};

#endif /* Board_hpp */
