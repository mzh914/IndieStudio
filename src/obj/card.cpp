/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** card
*/

#include "card.hpp"

Card::Card()
    : texture()
    , drawEvent()
{
    for (int i = 0; i < NB_PLAYER; ++i)
        texture[i].loadImage(PathPlayer[i].c_str());
}

Card::~Card()
{
    for (int i = 0; i < NB_PLAYER; ++i)
        UnloadTexture(texture[i].getTexture());
}

bool Card::isWinner() const
{
    return pos == 3;
}

void Card::setCard(const IdPlayer &deads, int i)
{
    pos = i;
    player = deads;
    if (i == 0) {
        _x_start = 1230;
        _y_start = 600;
    }
    if (i == 1) {
        _x_start = 730;
        _y_start = 600;
    }
    if (i == 2) {
        _x_start = 280;
        _y_start = 600;
    }
    if (i == 3) {
        _x_start = 730;
        _y_start = 100;
    }
}

void Card::drawCard()
{
    DrawText(isWinner()
            ? "Winner"
            : ((std::string) "Looser ").append(std::to_string(pos)).c_str(),
        _x_start, _y_start, isWinner() ? 50 : 30, isWinner() ? GREEN : RED);
    DrawTextureEx(texture[player].getTexture(),
        { static_cast<float>(_x_start), static_cast<float>(_y_start + 40) }, 0.0f, 1.0f, WHITE);
}
