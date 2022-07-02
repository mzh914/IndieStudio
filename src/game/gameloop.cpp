/*
** EPITECH PROJECT, 2022
** game
** File description:
** game
*/

#include <fstream>
#include "gameloop.hpp"

GameLoop::GameLoop()
    : drawEvent()
{
    camera = { { 0.0f, 20.0f, 10.0f }, { 0.0, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 40.0f, 0 };
    std::unique_ptr<SceneMusic> music(new SceneMusic("music_battle.ogg"));
    std::unique_ptr<Map> tmp(new Map());
    std::unique_ptr<PauseMenu> pausemenu(new PauseMenu());
    std::unique_ptr<End> endg(new End());
    endGame = std::move(endg);
    map = std::move(tmp);
    pause = std::move(pausemenu);
    gameMusic = std::move(music);
}

void GameLoop::Loop(SceneProcess &scene)
{
    static bool loaded = false;

    if (IsKeyDown(KEY_ESCAPE))
        map.get()->addPlayerInSave();
    // update
    if (map.get()->isGameOver()) { // if game over do end page
        this->end = true; // set end
        for (size_t i = 0; i < NB_PLAYER; ++i)
            endGame.get()->player[i] = map.get()->deads[i];
        button = endGame.get()->Loop();
    } else { // if game continue
        if (IsKeyDown(KEY_P)) // if pause game
            this->ispause = true;
        if (!ispause) {
            map->Update(scene);
            gameMusic->playMusic();
            gameMusic->updateMusic();
        } else {
            buttonpause = pause.get()->Loop();
        }
    }
    // game end loop
    if (button == BACK_TO_MENU || buttonpause == BACK_TO_MENU) {
        map.get()->addPlayerInSave();
        map.get()->reset();
        scene = MENU_SCENE;
        button = NULL_KEY;
        buttonpause = NULL_KEY;
        ispause = false;
        end = false;
    } else if (button == REPLAY || buttonpause == REPLAY) {
        map.get()->reset();
        scene = GAME_SCENE;
        button = NULL_KEY;
        buttonpause = NULL_KEY;
        ispause = false;
        end = false;
    }
    if (buttonpause == CONTINUE) {
        ispause = false;
        buttonpause = NULL_KEY;
    }
    if (!loaded) {
        map.get()->setPlayer();
        loaded = true;
    }
}

void GameLoop::draw()
{
    drawEvent.startDrawing();
    if (end) {
        drawEvent.clearBackground(BLACK);
        endGame.get()->draw();
    } else {
        if (ispause == false) {
            drawEvent.clearBackground(BLACK);
            map.get()->DrawBackground();
            BeginMode3D(camera);
            map->DrawMap();
            EndMode3D();
            DrawFPS(10, 10);
            map->DrawTimer();
        } else {
            drawEvent.clearBackground(BLACK);
            pause.get()->draw();
        }
    }
    drawEvent.endDrawing();
}

GameLoop::~GameLoop()
{
}
