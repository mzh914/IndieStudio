/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** newGame
*/

#include <fstream>
#include "newGame.hpp"
#include "libOutils.hpp"

newGame::newGame()
    : background()
    , drawEvent()
    , textBox()
    , startButton()
{
    std::unique_ptr<SceneMusic> music(new SceneMusic("music_title.ogg"));
    menuMusic = std::move(music);
    background.loadImage("../resources/menu1.png");
    currentProcess = LOAD_OR_NEW;
    textBox.setRect(620.0f, 502.0f, 380.0f, 80.0f);
    startButton.setRect(1020.0f, 502.0f, 120.0f, 80.0f);
    mainMenuButton.setRect(10.0f, 10.0f, 300.0f, 80.0f);
}

void newGame::draw()
{
    drawEvent.startDrawing();
    drawEvent.clearBackground(RAYWHITE);
    // Draw rectangles
    drawEvent.drawRectangleRec(textBox.getRect(), LIGHTGRAY);
    if (onText)
        drawEvent.drawRectLines(textBox.getRect().x, textBox.getRect().y, textBox.getRect().width, textBox.getRect().height, RED);
    else
        drawEvent.drawRectLines(textBox.getRect().x, textBox.getRect().y, textBox.getRect().width, textBox.getRect().height, DARKGRAY);
    drawEvent.drawText(name, textBox.getRect().x + 12, textBox.getRect().y + 15, 40, MAROON);
    drawEvent.drawText(TextFormat("ENTER GAME NAME", letterCount, MAX_INPUT_CHARS), 580, 400, 50, BLACK);
    drawEvent.drawText(TextFormat("INPUT CHARS: %i/%i", letterCount, MAX_INPUT_CHARS), 670, 600, 30, BLACK);
    drawEvent.drawRectangleRec(startButton.getRect(), CheckCollisionPointRec(GetMousePosition(), startButton.getRect()) ? SKYBLUE : LIGHTGRAY);
    drawEvent.drawRectLines(startButton.getRect().x, startButton.getRect().y, startButton.getRect().width, startButton.getRect().height, CheckCollisionPointRec(GetMousePosition(), startButton.getRect()) ? BLUE : GRAY);
    drawEvent.drawText(startButtonText, (startButton.getRect().x + startButton.getRect().width / 2 - MeasureText(startButtonText.c_str(), 10) / 2) - 30, startButton.getRect().y + 15, 30, CheckCollisionPointRec(GetMousePosition(), startButton.getRect()) ? DARKBLUE : DARKGRAY);
    drawEvent.drawRectangleRec(mainMenuButton.getRect(), CheckCollisionPointRec(GetMousePosition(), mainMenuButton.getRect()) ? SKYBLUE : LIGHTGRAY);
    drawEvent.drawRectLines(mainMenuButton.getRect().x, mainMenuButton.getRect().y, mainMenuButton.getRect().width, mainMenuButton.getRect().height, CheckCollisionPointRec(GetMousePosition(), mainMenuButton.getRect()) ? BLUE : GRAY);
    drawEvent.drawText(mainMenuButtonText, (mainMenuButton.getRect().x + mainMenuButton.getRect().width / 2 - MeasureText(mainMenuButtonText.c_str(), 10) / 2) - 50, mainMenuButton.getRect().y + 15, 30, CheckCollisionPointRec(GetMousePosition(), mainMenuButton.getRect()) ? DARKBLUE : DARKGRAY);
    if (enterValid)
        drawEvent.drawText(TextFormat("ENTER A VALID NAME", MAX_INPUT_CHARS), 650, 650, 30, MAROON);
    drawEvent.endDrawing();
}

void newGame::putKeyInName()
{
    int key = GetCharPressed();

    while (key > 0) {
        if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_CHARS)) {
            name[letterCount] = static_cast<char>(key);
            name[letterCount + 1] = '\0';
            letterCount++;
        }
        key = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE)) {
        letterCount--;
        if (letterCount < 0)
            letterCount = 0;
        name[letterCount] = '\0';
    }
}

void newGame::writeNameInFile()
{
    std::ofstream out;

    out.open("save.txt", std::ios::app);
    out << name;
    out << "::isplaying\n";
    out << "2.000000:2.000000:2.000000:2.000000\n";
    out << "0.050000:0.050000:0.050000:0.050000\n";
    out << "1:1:1:1\n";
    out << "false:false:false:false\n";
}

void newGame::Loop(SceneProcess &CurrentScene)
{
    changeScene = false;
    menuMusic->playMusic();
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        if (CheckCollisionPointRec(GetMousePosition(), textBox.getRect()))
            onText = true;
        else
            onText = false;
    }
    if (onText)
        putKeyInName();
    // Keyboard toggle group logic
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), startButton.getRect())) {
        if (std::string(name).size() == 0 || special_char_in_str(name)) {
            enterValid = true;
            return;
        }
        writeNameInFile();
        changeScene = true;
        CurrentScene = SELECT_SCENE;
    } else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), mainMenuButton.getRect())) {
        changeScene = true;
        CurrentScene = MENU_SCENE;
    }
}

void newGame::free()
{
}