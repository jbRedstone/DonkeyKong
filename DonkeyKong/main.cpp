//
//  main.hpp
//  DonkeyKong
//
//  Created by Joshua Rubin on 13/06/2017.
//  Copyright © 2017 Joshua Rubin. All rights reserved.
//
#include "GamePlay.hpp"
#include <iostream>

using::Utilities::Exception;

int main(int, char const**)
{
    try
    {
        GamePlay game;
    }
    catch (Exception exception)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
