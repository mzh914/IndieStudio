/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** select
*/

#ifndef SELECT_HPP_
#define SELECT_HPP_

#include "IScene.hpp"
#include "music.hpp"
#include "string"
#include "memory"

class selectPlayer : public IScene {
private:
    std::unique_ptr<SceneMusic> menuMusic;
    bool changeScene = false;
    SceneProcess CurrentScene = SELECT_SCENE;
    int framesCounter = 0;
    Rectangle aiRect[5];
    Rectangle playerRect[5];
    const std::string boxText[5] = { "0", "1", "2", "3", "4" };
    short nb_ai;
    short nb_player;
    Rectangle confirmButton = { 620.0f, 732.0f, 300.0f, 100.0f };
    const std::string confirmButtonText = "CONFIRM";
    bool enterExceed = false;
    bool enterUnsufficent = false;
    Vector2 exceptionPos = { 350.0f, 700.0f };
    Vector2 aiboxPos = { 420.0f, 282.0f };
    Vector2 playerboxPos = { 420.0f, 482.0f };
    const std::string exceed = "THERE CAN'T BE MORE THAN 4 PLAYER (IA includeD)";
    const std::string below = "THERE MUST HAVE EXACTLY 4 PLAYER (IA includeD)";

public:
    selectPlayer(/* args */);
    SceneProcess getScene();
    void Loop(SceneProcess &CurrentScene);
    void init();
    void draw();
    void free();
    ~selectPlayer();

    void writeInfoInFile();
};

#endif /* !SELECT_HPP_ */
