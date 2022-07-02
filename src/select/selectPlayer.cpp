/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** selectPlayer
*/

#include <fstream>
#include "selectPlayer.hpp"
#include "raylib.h"
#include "const.hpp"

selectPlayer::selectPlayer()
{
    std::unique_ptr<SceneMusic> music(new SceneMusic("music_title.ogg"));
    menuMusic = std::move(music);
    changeScene = false;
    for (size_t i = 0; i < NB_SLOT; ++i) {
        aiRect[i].width = 100.0f;
        aiRect[i].height = 100.0f;
        playerRect[i].width = 100.0f;
        playerRect[i].height = 100.0f;
        aiRect[i].x = aiboxPos.x + i * (aiRect[i].width + 40.0f);
        aiRect[i].y = aiboxPos.y;
        playerRect[i].x = playerboxPos.x + i * (playerRect[i].width + 40.0f);
        playerRect[i].y = playerboxPos.y;
    }
    nb_ai = -1;
    nb_player = -1;
}

void selectPlayer::writeInfoInFile()
{
    std::ofstream out;

    out.open("../resources/select.txt", std::ofstream::out | std::ofstream::trunc);
    out << nb_player;
    out << ";";
    out << nb_ai;
    out.close();
}

void selectPlayer::Loop(SceneProcess &scene)
{
    if (nb_ai != -1 && nb_player != -1 && nb_ai + nb_player > MAX_PLAYER)
        enterExceed = true;
    else
        enterExceed = false;
    if (nb_ai != -1 && nb_player != -1 && nb_ai + nb_player < MAX_PLAYER)
        enterUnsufficent = true;
    else
        enterUnsufficent = false;
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        for (short i = 0; i < NB_SLOT; ++i) {
            if (CheckCollisionPointRec(GetMousePosition(), aiRect[i]))
                nb_ai = nb_ai != i ? i : -1;
            if (CheckCollisionPointRec(GetMousePosition(), playerRect[i]))
                nb_player = nb_player != i ? i : -1;
        }
        if (nb_player != -1 && nb_ai != -1 && CheckCollisionPointRec(GetMousePosition(), confirmButton) && !enterExceed && !enterUnsufficent)
            changeScene = true;
    }
    if (changeScene) {
        writeInfoInFile();
        scene = GAME_SCENE;
    }
}

void selectPlayer::draw()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText(TextFormat("SELECT NUMBER OF AI :"), aiboxPos.x * 1.1, aiboxPos.y - 50, 40, BLACK);
    DrawText(TextFormat("SELECT NUMBER OF PLAYER :"), playerboxPos.x * 1.2, playerboxPos.y - 50, 40, BLACK);
    for (size_t i = 0; i < NB_SLOT; ++i) {
        DrawRectangleRec(aiRect[i], i == nb_ai ? Fade(GRAY, 0.30) : BLACK);
        DrawRectangleRec(playerRect[i], i == nb_player ? Fade(GRAY, 0.30) : BLACK);
        DrawText(boxText[i].c_str(), (aiRect[i].x + aiRect[i].width / 2 - MeasureText(boxText[i].c_str(), 50) / 2), aiRect[i].y + 25, 50, (i == nb_ai) ? Fade(BLACK, 0.60) : WHITE);
        DrawText(boxText[i].c_str(), (playerRect[i].x + playerRect[i].width / 2 - MeasureText(boxText[i].c_str(), 50) / 2), playerRect[i].y + 25, 50, (i == nb_player) ? Fade(BLACK, 0.60) : WHITE);
    }
    if (nb_ai != -1 && nb_player != -1 && enterExceed == false && enterUnsufficent == false) {
        DrawRectangleRec(confirmButton, CheckCollisionPointRec(GetMousePosition(), confirmButton) ? LIGHTGRAY : GRAY);
        DrawText(confirmButtonText.c_str(), (confirmButton.x + confirmButton.width / 2 - MeasureText(confirmButtonText.c_str(), 40) / 2), confirmButton.y + 25, 40, CheckCollisionPointRec(GetMousePosition(), confirmButton) ? Fade(BLACK, 0.60) : WHITE);
    } else {
        DrawRectangleRec(confirmButton, Fade(BLACK, 0.6f));
        DrawText(confirmButtonText.c_str(), (confirmButton.x + confirmButton.width / 2 - MeasureText(confirmButtonText.c_str(), 40) / 2), confirmButton.y + 25, 40, Fade(BLACK, 0.60f));
    }
    if (enterExceed)
        DrawText(exceed.c_str(), exceptionPos.x, exceptionPos.y, 30, RED);
    if (enterUnsufficent)
        DrawText(below.c_str(), exceptionPos.x, exceptionPos.y, 30, RED);
    EndDrawing();
}

void selectPlayer::free()
{
    // std::ofstream out;

    // out.open("../resources/select.txt", std::ofstream::out | std::ofstream::trunc);
    // out.close();
}

selectPlayer::~selectPlayer()
{
    this->free();
}