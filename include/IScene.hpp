/*
** EPITECH PROJECT, 2022
** scene
** File description:
** scene
*/

#pragma once

#include "const.hpp"

class IScene { // DISPLAY
public:
    virtual ~IScene() = default;
    virtual void Loop(SceneProcess &scene) = 0;
    virtual void draw() = 0;

protected:
private:
};
