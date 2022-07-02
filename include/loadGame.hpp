/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** loadGame
*/

#ifndef LOADGAME_HPP_
#define LOADGAME_HPP_

#pragma once

class loadGame : public IScene {
private:
    std::unique_ptr<SceneSound> clickOn;
    std::unique_ptr<SceneMusic> menuMusic;
    ImgTexture background;
    DrawingProcess drawEvent;
    int loader;
    int NUM_PROCESSES = 0;
    std::vector<Rectangle> toggleRecs;
    Rectangle mainMenuButton;
    int mouseHoverRec = -1;
    bool changeScene = false;
    bool newGame = false;
    bool backToMenu = false;
    std::vector<std::string> saveFile;
    SceneProcess CurrentScene = LOAD_GAME;
    std::vector<std::string> processText;
    std::vector<std::string> loadFile;
    std::vector<std::string> nullFile;

public:
    loadGame(/* args */);
    void initLoad();
    SceneProcess getScene();
    void Loop(SceneProcess &CurrentScene);
    void init();
    void draw();
    void free();
    void writeInFile(std::vector<std::string> v, std::string str);
    void readFromFile(std::vector<std::string> &v, std::string str);

    ~loadGame() {};
};

#endif /* !LOADGAME_HPP_ */
