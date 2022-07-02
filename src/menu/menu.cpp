/*
** EPITECH PROJECT, 2022
** menu
** File description:
** menu
*/

#include "menu.hpp"

menu::menu()
    : background()
    , drawEvent()
    , toggleRecs()
{
    std::unique_ptr<SceneMusic> music(new SceneMusic("music_title.ogg"));
    std::unique_ptr<SceneSound> sound(new SceneSound("click.ogg"));
    menuMusic = std::move(music);
    clickOn = std::move(sound);
    background.loadImage("../resources/menu1.png");
    currentProcess = START;
    mouseHoverRec = -1;
    for (int i = 0; i < NUM_PROCESSES; ++i)
        toggleRecs[i].setRect(120.0f, (200 + 102 * i), 300.0f, 80.0f);
}

void menu::draw()
{
    drawEvent.startDrawing();
    drawEvent.clearBackground(GetColor(0x052c46ff));
    drawEvent.drawTextureEx(background.getTexture(), { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        drawEvent.drawRectangleRec(toggleRecs[i].getRect(), ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY); // can remove
        drawEvent.drawRectLines(toggleRecs[i].getRect().x, toggleRecs[i].getRect().y, toggleRecs[i].getRect().width, toggleRecs[i].getRect().height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        drawEvent.drawText(processText[i], (toggleRecs[i].getRect().x + toggleRecs[i].getRect().width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 30, toggleRecs[i].getRect().y + 11, 30, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
    drawEvent.endDrawing();
}

void menu::Loop(SceneProcess &CurrentScene)
{
    changeScene = false;
    mouseHoverRec = -1;
    menuMusic->playMusic();
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        menuMusic->updateMusic();
        if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i].getRect())) {
            mouseHoverRec = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) {
                currentProcess = i;
                changeScene = true;
                clickOn->playSound();
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
        case START:
            CurrentScene = LOAD_OR_NEW;
            break;
        case HELP:
            CurrentScene = HELP_SCENE;
            break;
        case EXIT:
            CurrentScene = EXIT_SCENE;
        default:
            break;
        }
    }
}

void menu::free()
{
}
