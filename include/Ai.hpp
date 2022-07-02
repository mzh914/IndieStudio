/*
** EPITECH PROJECT, 2022
** ai
** File description:
** ai
*/

#pragma once
#include <memory>
#include <vector>
#include "raylib.h"

class Ai {
public:
    Ai();
    size_t id;
    KeyboardKey GetAIkey();
    ~Ai();

protected:
    std::vector<KeyboardKey> aikey;

private:
};
