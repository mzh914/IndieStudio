/*
** EPITECH PROJECT, 2022
** End
** File description:
** End
*/

#include "raylib.h"
#include "end.hpp"
#include "const.hpp"

End::End()
    : background()
    , drawEvent()
    , toggleRecs()
{
    changeScene = false;
    currentProcess = REPLAY;
    mouseHoverRec = -1;
    background.loadImage("../resources/end/game_over.png");
    toggleRecs[REPLAY].setRect(80, (20), 300.0f, 80.0f);
    toggleRecs[BACK_TO_MENU].setRect(1200.0f, (20), 300.0f, 80.0f);
}

void End::draw()
{
    DrawTextureEx(background.getTexture(), { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < 4; ++i) {
        cards[i].setCard(player[i], i);
        cards[i].drawCard();
    }
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        DrawRectangleRec(toggleRecs[i].getRect(), ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY); // can remove
        DrawRectangleLines(toggleRecs[i].getRect().x, toggleRecs[i].getRect().y, toggleRecs[i].getRect().width, toggleRecs[i].getRect().height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        DrawText(processText[i].c_str(), (toggleRecs[i].getRect().x + toggleRecs[i].getRect().width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 30, toggleRecs[i].getRect().y + 11, 30, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
}

size_t End::Loop()
{
    mouseHoverRec = -1;
    changeScene = false;
    currentProcess = -1;
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i].getRect())) {
            mouseHoverRec = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) {
                currentProcess = i;
                changeScene = true;
            }
            break;
        } else
            mouseHoverRec = -1;
    }
    if (changeScene) {
        switch (currentProcess) {
        case BACK_TO_MENU:
            return BACK_TO_MENU;
            break;
        case REPLAY:
            return REPLAY;
            break;
        default:
            break;
        }
    }
    return NULL_KEY;
}

bool End::getChangeScene() const
{
    return changeScene;
}

void End::setChangeScene(const bool &changeScene)
{
    this->changeScene = changeScene;
}

int End::getCurrentProcess() const
{
    return currentProcess;
}

void End::setCurrentProcess(const int &changeScene)
{
    this->currentProcess = changeScene;
}

End::~End()
{
}
