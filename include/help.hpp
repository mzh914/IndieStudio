/*
** EPITECH PROJECT, 2022
** help
** File description:
** help
*/

#pragma once

#include "IScene.hpp"
#include "music.hpp"
#include "sound.hpp"
#include <memory>
#include "Rectangle.hpp"

class help : public IScene {
private:
    typedef enum HelpPage_e {
        ABOUT,
        COMMANDS,
        HELP_PAGE_NB
    } HelpPage_t;
    enum HelpProcess_e {
        BACK = 0,
        NEXT,
        PREVIOUS,
    };
    Texture2D background[HELP_PAGE_NB];
    int currentProcess;
    int NUM_PROCESSES = 3;
    RectangleClass toggleRecs[3];
    int mouseHoverRec = -1;
    bool changeScene = false;
    SceneProcess CurrentScene = HELP_SCENE;
    std::unique_ptr<SceneMusic> helpMusic;
    std::unique_ptr<SceneSound> clickOn;
    const std::string processText[3] = { "BACK", "NEXT", "PREVIOUS" };
    HelpPage_t CurrentPage = ABOUT;

public:
    help();
    SceneProcess getScene();
    void Loop(SceneProcess &scene);
    void draw();
    ~help();
};
