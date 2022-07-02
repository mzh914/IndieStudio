/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** loadGame
*/

#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include "IScene.hpp"
#include "music.hpp"
#include "sound.hpp"
#include "Texture.hpp"
#include "Drawing.hpp"
#include "loadGame.hpp"
#include <iostream>

void loadGame::writeInFile(std::vector<std::string> v, std::string str)
{
    std::ofstream file;
    file.open(str);
    for (int i = 0; i < v.size(); ++i) {
        file << v[i] << std::endl;
    }
    file.close();
}

void loadGame::readFromFile(std::vector<std::string> &v, std::string str)
{
    std::ifstream file;
    file.open(str);
    std::string line;
    while (getline(file, line))
        v.push_back(line);
    file.close();
}

loadGame::loadGame()
    : background()
    , drawEvent()
{
    std::unique_ptr<SceneMusic> music(new SceneMusic("music_title.ogg"));
    std::unique_ptr<SceneSound> sound(new SceneSound("click.ogg"));
    menuMusic = std::move(music);
    clickOn = std::move(sound);
    background.loadImage("../resources/menu1.png");
    mouseHoverRec = -1;
    nullFile.push_back("not loading");
}

void loadGame::initLoad()
{
    readFromFile(saveFile, "save.txt");
    std::string tmp;

    if (saveFile.size() == 0) {
        processText.push_back("NO SAVES");
        ++NUM_PROCESSES;
        newGame = true;
    } else
        for (int i = 0; i < saveFile.size(); i += 5, ++NUM_PROCESSES) {
            tmp = saveFile[i].substr(0, saveFile[i].size() - 1);
            processText.push_back(tmp);
        }
    for (int i = 0; i < NUM_PROCESSES; ++i)
        toggleRecs.push_back({ 650.0f, static_cast<float>(400 + 102 * i), 300.0f, 80.0f });
    mainMenuButton = { 10.0f, 10.0f, 300.0f, 80.0f };
}

void loadGame::draw()
{
    drawEvent.startDrawing();
    drawEvent.clearBackground(GetColor(0x052c46ff));
    drawEvent.drawTextureEx(background.getTexture(), { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    // Draw rectangles
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        drawEvent.drawRectangleRec(toggleRecs[i], (i == mouseHoverRec) ? SKYBLUE : LIGHTGRAY); // can remove
        drawEvent.drawRectLines(toggleRecs[i].x, toggleRecs[i].y, toggleRecs[i].width, toggleRecs[i].height, (i == mouseHoverRec) ? BLUE : GRAY);
        drawEvent.drawText(processText[i], (toggleRecs[i].x + toggleRecs[i].width / 2 - MeasureText(processText[i].c_str(), 10) / 2) - 50, toggleRecs[i].y + 11, 30, (i == mouseHoverRec) ? DARKBLUE : DARKGRAY);
    }
    drawEvent.drawRectangleRec(mainMenuButton, (NUM_PROCESSES == mouseHoverRec) ? SKYBLUE : LIGHTGRAY); // can remove
    drawEvent.drawRectLines(mainMenuButton.x, mainMenuButton.y, mainMenuButton.width, mainMenuButton.height, (NUM_PROCESSES == mouseHoverRec) ? BLUE : GRAY);
    drawEvent.drawText("MAIN MENU", (mainMenuButton.x + mainMenuButton.width / 2 - MeasureText("MAIN MENU", 10) / 2) - 50, mainMenuButton.y + 11, 30, (NUM_PROCESSES == mouseHoverRec) ? DARKBLUE : DARKGRAY);
    drawEvent.endDrawing();
}

void loadGame::Loop(SceneProcess &CurrentScene)
{
    readFromFile(loadFile, "load.txt");
    if (loadFile.size() != 0 && loadFile[0] == "load") {
        saveFile.clear();
        processText.clear();
        toggleRecs.clear();
        NUM_PROCESSES = 0;
        newGame = false;
        backToMenu = false;
        writeInFile(nullFile, "load.txt");
        initLoad();
    }
    changeScene = false;
    mouseHoverRec = -1;
    menuMusic->playMusic();
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        menuMusic->updateMusic();
        if (CheckCollisionPointRec(GetMousePosition(), toggleRecs[i])) {
            mouseHoverRec = i;
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                loader = i;
                changeScene = true;
                clickOn->playSound();
            }
            break;
        }
    }
    if (CheckCollisionPointRec(GetMousePosition(), mainMenuButton)) {
        mouseHoverRec = NUM_PROCESSES;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            backToMenu = true;
            changeScene = true;
            clickOn->playSound();
        }
    }
    // Keyboard toggle group logic
    if (changeScene) {
        if (backToMenu)
            CurrentScene = MENU_SCENE;
        else if (newGame)
            CurrentScene = NEW_GAME;
        else {
            int t = 0;
            std::string cmp = processText[loader] += ":";
            for (; saveFile[t] != cmp; ++t) {}
            std::string st = ":isplaying";
            for (int i = 0; i < st.length(); ++i)
                saveFile[t].push_back(st[i]);
            writeInFile(saveFile, "save.txt");
            CurrentScene = GAME_SCENE;
        }
    }
    loadFile.clear();
}

void loadGame::free()
{
}