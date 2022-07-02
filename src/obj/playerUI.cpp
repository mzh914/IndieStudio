/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** playerUI.cpp
*/

#include "playerUI.hpp"

PlayerUI::PlayerUI(IdPlayer player)
{
    if (player == BLUE_P)
        playerPic = LoadTexture("../resources/player/ui/blue.png");
    if (player == RED_P)
        playerPic = LoadTexture("../resources/player/ui/red.png");
    if (player == GREEN_P)
        playerPic = LoadTexture("../resources/player/ui/green.png");
    if (player == YELLOW_P)
        playerPic = LoadTexture("../resources/player/ui/yellow.png");
    _player = player;
}

void PlayerUI::draw(float bombSize, float speed, size_t maxBomb, bool wallPass) const
{
    if (_player == BLUE_P) {
        DrawTextureEx(playerPic, { 0.0f, 0.0f }, 1.0f, 1.0f, WHITE);
        DrawText(std::to_string(bombSize).c_str(), 350, 500, 100, WHITE);
    }
    if (_player == RED_P) {
        DrawTextureEx(playerPic, { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
        DrawText(std::to_string(bombSize).c_str(), 350, 500, 10, WHITE);
    }

    if (_player == GREEN_P) {
        DrawTextureEx(playerPic, { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
        DrawText(std::to_string(bombSize).c_str(), 350, 500, 10, WHITE);
    }

    if (_player == YELLOW_P) {
        DrawTextureEx(playerPic, { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
        DrawText(std::to_string(bombSize).c_str(), 350, 500, 10, WHITE);
    }
}

PlayerUI::~PlayerUI()
{
    UnloadTexture(playerPic);
}