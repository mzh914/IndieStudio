/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** pause
*/

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "IScene.hpp"
#include "Texture.hpp"
#include "Drawing.hpp"
#include "Rectangle.hpp"
#include <string>

class PauseMenu {
private:
    ImgTexture background;
    DrawingProcess drawEvent;
    int currentProcess;
    int NUM_PROCESSES = 3;
    RectangleClass toggleRecs[3];
    int mouseHoverRec = -1;
    bool changeScene = false;
    const std::string processText[3] = {
        "CONTINUE",
        "RESTART",
        "HOME",
    };
    enum PauseProcess_e {
        RESUME = 0,
        RESTART,
        SCREEN,
    };

public:
    PauseMenu();
    ~PauseMenu();
    size_t Loop();
    void init();
    void draw();
};

#endif /* !PAUSE_HPP_ */
