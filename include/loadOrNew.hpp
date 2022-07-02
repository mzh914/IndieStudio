/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** loadOrNew
*/

#ifndef LOADORNEW_HPP_
#define LOADORNEW_HPP_

#pragma once

#include <vector>

bool remove_isplaying(const std::string &filename);

class loadOrNew : public IScene {
private:
    std::unique_ptr<SceneMusic> menuMusic;
    std::unique_ptr<SceneSound> clickOn;
    ImgTexture background;
    DrawingProcess drawEvent;
    int currentProcess;
    int NUM_PROCESSES = 3;
    RectangleClass toggleRecs[3];
    int mouseHoverRec = -1;
    bool changeScene = false;
    SceneProcess CurrentScene = LOAD_OR_NEW;
    const std::string processText[3] = {
        "LOAD GAME",
        "NEW GAME",
        "MAIN MENU",
    };
    std::vector<std::string> loadFile;

public:
    loadOrNew(/* args */);
    SceneProcess getScene();
    void writeInFile(std::vector<std::string> v);
    void Loop(SceneProcess &CurrentScene);
    void init();
    void draw();
    void free();
    ~loadOrNew() {};
};

#endif /* !LOADORNEW_HPP_ */
