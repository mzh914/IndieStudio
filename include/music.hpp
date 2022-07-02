/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** music
*/

#pragma once

#include "const.hpp"

class SceneMusic {
private:
    Music music;

public:
    SceneMusic() = default;
    SceneMusic(const std::string &fileName);
    void setMusic(const std::string &fileName);
    Music getMusic();
    void playMusic();
    void updateMusic();
    ~SceneMusic();
};