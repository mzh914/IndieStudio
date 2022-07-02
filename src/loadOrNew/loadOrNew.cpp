/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** loadOrNew
*/

#include <fstream>
#include "IScene.hpp"
#include <memory>
#include "music.hpp"
#include "sound.hpp"
#include "Texture.hpp"
#include "Drawing.hpp"
#include "Rectangle.hpp"
#include "loadOrNew.hpp"

void loadOrNew::writeInFile(std::vector<std::string> v)
{
    std::ofstream file;
    file.open("load.txt");
    for (int i = 0; i < v.size(); ++i) {
        file << v[i] << std::endl;
    }
    file.close();
}

loadOrNew::loadOrNew()
    : background()
    , drawEvent()
    , toggleRecs()
{
    std::unique_ptr<SceneMusic> music(new SceneMusic("music_title.ogg"));
    std::unique_ptr<SceneSound> sound(new SceneSound("click.ogg"));
    menuMusic = std::move(music);
    clickOn = std::move(sound);
    background.loadImage("../resources/menu1.png");
    currentProcess = LOAD_OR_NEW;
    mouseHoverRec = -1;
    for (int i = 0; i < NUM_PROCESSES; ++i)
        toggleRecs[i].setRect(650.0f, (400 + 102 * i), 300.0f, 80.0f);
    loadFile.push_back("load");
}

void loadOrNew::draw()
{
    drawEvent.startDrawing();
    ClearBackground(GetColor(0x052c46ff));
    drawEvent.drawTextureEx(background.getTexture(), { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        drawEvent.drawRectangleRec(toggleRecs[i].getRect(), (i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY); // can remove
        drawEvent.drawRectLines(toggleRecs[i].getRect().x, toggleRecs[i].getRect().y, toggleRecs[i].getRect().width, toggleRecs[i].getRect().height, ((i == currentProcess) || (i == mouseHoverRec)) ? BLUE : GRAY);
        drawEvent.drawText(processText[i], (toggleRecs[i].getRect().x + toggleRecs[i].getRect().width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 50, toggleRecs[i].getRect().y + 11, 30, (i == mouseHoverRec) ? DARKBLUE : DARKGRAY);
    }
    drawEvent.endDrawing();
}

void loadOrNew::Loop(SceneProcess &CurrentScene)
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
    if (changeScene) {
        switch (currentProcess) {
        case START:
            CurrentScene = LOAD_GAME;
            writeInFile(loadFile);
            break;
        case HELP:
            CurrentScene = NEW_GAME;
            break;
        case EXIT:
            CurrentScene = MENU_SCENE;
            break;
        default:
            break;
        }
    }
}

void loadOrNew::free()
{
}