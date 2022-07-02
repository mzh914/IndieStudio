/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** Rectangle.hpp
*/

#pragma once

#include "raylib.h"

class RectangleClass {
public:
    RectangleClass();
    ~RectangleClass() = default;
    void setRect(float x, float y, float width, float height);
    Rectangle getRect();

private:
    Rectangle rectItems;
};