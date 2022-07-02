/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** playerUI.hpp
*/

#pragma once
#include "Bomb.hpp"

class PlayerUI {
public:
    PlayerUI(IdPlayer player);
    ~PlayerUI();
    void draw(float bombSize, float speed, size_t maxBomb, bool wallPass) const;

private:
    ImgTexture playerPic;
    IdPlayer _player;
};