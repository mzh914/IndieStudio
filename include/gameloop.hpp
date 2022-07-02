/*
** EPITECH PROJECT, 2022
** gameloop
** File description:
** gameloop
*/

#pragma once

#include "pause.hpp"
#include "end.hpp"
#include "map.hpp"
#include "music.hpp"
#include "Drawing.hpp"

void game_loop(void);

class GameLoop : public IScene {

private:
    size_t button = NULL_KEY;
    size_t buttonpause = NULL_KEY;
    Camera camera;
    std::unique_ptr<SceneMusic> gameMusic;
    std::unique_ptr<PauseMenu> pause;
    std::unique_ptr<End> endGame;
    std::unique_ptr<Map> map;
    bool end = false;
    bool ispause = false;
    DrawingProcess drawEvent;

public:
    GameLoop();
    SceneProcess getScene();
    void Loop(SceneProcess &scene);
    void draw();
    ~GameLoop();
};