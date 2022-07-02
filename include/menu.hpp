/*
** EPITECH PROJECT, 2022
** menu
** File description:
** menu
*/

#pragma once

#include "IScene.hpp"
#include "music.hpp"
#include "sound.hpp"
#include <memory>
#include <string>
#include "Texture.hpp"
#include "Drawing.hpp"
#include "Rectangle.hpp"
class menu : public IScene {
private:
    std::unique_ptr<SceneMusic> menuMusic;
    std::unique_ptr<SceneSound> clickOn;
    ImgTexture background;
    int currentProcess;
    int NUM_PROCESSES = 3;
    RectangleClass toggleRecs[3];
    int mouseHoverRec = -1;
    bool changeScene = false;
    SceneProcess CurrentScene = MENU_SCENE;
    const std::string processText[3] = {
        "START",
        "HELP",
        "EXIT",
    };
    DrawingProcess drawEvent;

public:
    menu(/* args */);
    SceneProcess getScene();
    void Loop(SceneProcess &CurrentScene);
    void init();
    void draw();
    void free();
    ~menu() {};
};
