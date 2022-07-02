/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** card
*/

#pragma once

#include "Bomb.hpp"
#include "Drawing.hpp"
class Card {
private:
    int _x_start = 0;
    int _y_start = 0;
    int pos = 0;
    IdPlayer player;
    const std::string PathPlayer[NB_PLAYER] = {
        "../resources/player/icons/blue.png",
        "../resources/player/icons/green.png",
        "../resources/player/icons/red.png",
        "../resources/player/icons/yellow.png",
    };

public:
    Card();
    ~Card();
    bool isWinner() const;
    void setCard(const IdPlayer &deads, int i);
    void drawCard();
    ImgTexture texture[NB_PLAYER];
    DrawingProcess drawEvent;
};