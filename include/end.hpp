/*
** EPITECH PROJECT, 2022
** End
** File description:
** End
*/

#pragma once
#include "IScene.hpp"
#include "card.hpp"
#include "Drawing.hpp"
#include "Rectangle.hpp"

class End {
private:
    ImgTexture background;
    DrawingProcess drawEvent;
    static const int NUM_PROCESSES = 2;
    bool changeScene = false;
    int currentProcess = -1;
    RectangleClass toggleRecs[NUM_PROCESSES];
    int mouseHoverRec = -1;
    const std::string processText[NUM_PROCESSES] = { "Play Again", "Back to menu" };
    Card cards[NB_PLAYER];

public:
    End(/* args */);
    IdPlayer player[4] = { UNKNOWN_P, UNKNOWN_P, UNKNOWN_P, UNKNOWN_P };
    SceneProcess getScene();
    size_t Loop();
    void draw();
    bool getChangeScene() const;
    void setChangeScene(const bool &changeScene);
    int getCurrentProcess() const;
    void setCurrentProcess(const int &changeScene);

    ~End();
};
