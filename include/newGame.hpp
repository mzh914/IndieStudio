/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** newGame
*/

#ifndef NEWGAME_HPP_
#define NEWGAME_HPP_

#pragma once
#include "IScene.hpp"
#include "music.hpp"
#include "Texture.hpp"
#include "Drawing.hpp"
#include "Rectangle.hpp"
#include <memory>
#include <string>

#define MAX_INPUT_CHARS 16

class newGame : public IScene {
private:
    std::unique_ptr<SceneMusic> menuMusic;
    ImgTexture background;
    DrawingProcess drawEvent;
    int currentProcess;
    bool changeScene = false;
    bool onText = false;
    SceneProcess CurrentScene = NEW_GAME;
    int framesCounter = 0;
    char name[MAX_INPUT_CHARS + 1] = "\0";
    int letterCount = 0;
    RectangleClass textBox;
    RectangleClass startButton;
    RectangleClass mainMenuButton;
    const std::string startButtonText = "START";
    const std::string mainMenuButtonText = "MAIN MENU";
    bool enterValid = false;
    int len = 0;

public:
    newGame(/* args */);
    SceneProcess getScene();
    void Loop(SceneProcess &CurrentScene);
    void init();
    void draw();
    void free();
    ~newGame() {};

    void putKeyInName();
    void writeNameInFile();
};

#endif /* !NEWGAME_HPP_ */
