/*
** EPITECH PROJECT, 2022
** indie_studio
** File description:
** pause
*/

#include "pause.hpp"

PauseMenu::PauseMenu()
    : background()
    , drawEvent()
    , toggleRecs()
{
    background.loadImage("../resources/pause_bg.png");
    currentProcess = RESUME;
    mouseHoverRec = -1;
    for (int i = 0; i < NUM_PROCESSES; ++i)
        toggleRecs[i].setRect(120.0f, (200 + 102 * i), 300.0f, 80.0f);
}

void PauseMenu::draw()
{
    drawEvent.clearBackground(GetColor(0x052c46ff));
    drawEvent.drawTextureEx(background.getTexture(), { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        drawEvent.drawRectangleRec(toggleRecs[i].getRect(), ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY); // can remove
        drawEvent.drawRectLines(toggleRecs[i].getRect().x, toggleRecs[i].getRect().y, toggleRecs[i].getRect().width, toggleRecs[i].getRect().height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        drawEvent.drawText(processText[i], (toggleRecs[i].getRect().x + toggleRecs[i].getRect().width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 30, toggleRecs[i].getRect().y + 11, 30, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
}

size_t PauseMenu::Loop()
{
    changeScene = false;
    mouseHoverRec = -1;
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
    // Keyboard toggle group logic
    if (IsKeyPressed(KEY_DOWN)) {
        currentProcess++;
        if (currentProcess > (NUM_PROCESSES - 1))
            currentProcess = 0;
    } else if (IsKeyPressed(KEY_UP)) {
        currentProcess--;
        if (currentProcess < 0)
            currentProcess = 2;
    }
    if (changeScene) {
        switch (currentProcess) {
        case RESUME:
            return CONTINUE;
            break;
        case RESTART:
            return REPLAY;
            break;
        case SCREEN:
            return BACK_TO_MENU;
            break;
        default:
            break;
        }
    }
    return NULL_KEY;
}

PauseMenu::~PauseMenu()
{
}
