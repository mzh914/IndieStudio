/*
** EPITECH PROJECT, 2022
** help
** File description:
** help
*/

#include "help.hpp"

help::help()
    : toggleRecs()
{
    mouseHoverRec = -1;
    background[ABOUT] = LoadTexture("../resources/about.png");
    background[COMMANDS] = LoadTexture("../resources/commands.png");
    std::unique_ptr<SceneMusic> music(new SceneMusic("game_music.wav"));
    std::unique_ptr<SceneSound> sound(new SceneSound("click.ogg"));
    helpMusic = std::move(music);
    clickOn = std::move(sound);
    currentProcess = BACK;
    toggleRecs[BACK].setRect(80, (20), 300.0f, 80.0f);
    toggleRecs[NEXT].setRect(1200.0f, (800), 300.0f, 80.0f);
    toggleRecs[PREVIOUS].setRect(80, (800), 300.0f, 80.0f);
}

void help::draw()
{
    BeginDrawing();
    ClearBackground(GetColor(0x052c46ff));
    DrawTextureEx(background[CurrentPage], { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        DrawRectangleRec(toggleRecs[i].getRect(), ((i == currentProcess) || (i == mouseHoverRec)) ? SKYBLUE : LIGHTGRAY); // can remove
        DrawRectangleLines(toggleRecs[i].getRect().x, toggleRecs[i].getRect().y, toggleRecs[i].getRect().width, toggleRecs[i].getRect().height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        DrawText(processText[i].c_str(), (toggleRecs[i].getRect().x + toggleRecs[i].getRect().width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 30, toggleRecs[i].getRect().y + 11, 30, ((i == currentProcess) || (i == mouseHoverRec)) ? DARKBLUE : DARKGRAY);
    }
    EndDrawing();
}

void help::Loop(SceneProcess &CurrentScene)
{
    mouseHoverRec = -1;
    changeScene = false;
    helpMusic->playMusic();
    helpMusic->updateMusic();
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i].getRect())) {
            mouseHoverRec = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_ENTER)) {
                clickOn->playSound();
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
        case BACK:
            CurrentScene = MENU_SCENE;
            break;
        case NEXT:
            CurrentPage = COMMANDS;
            break;
        case PREVIOUS:
            CurrentPage = ABOUT;
            break;
        default:
            break;
        }
    }
}

help::~help()
{
    for (unsigned short i = 0; i < HELP_PAGE_NB; ++i)
        UnloadTexture(background[i]);
}
