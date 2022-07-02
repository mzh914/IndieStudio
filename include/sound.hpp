/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** sound
*/

#pragma once

#include "const.hpp"

class SceneSound {
private:
    Sound sound;

public:
    SceneSound() = default;
    SceneSound(const std::string &fileName);
    void setSound(const std::string &fileName);
    Sound getSound();
    void playSound();
    void playSoundMulti();
    ~SceneSound();
};