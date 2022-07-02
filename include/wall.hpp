/*
** EPITECH PROJECT, 2022
** wall
** File description:
** wall
*/

#pragma once

#include "raylib.h"
#include "Texture.hpp"
#include "Drawing.hpp"
#include "Model.hpp"

namespace WallObj {
static const unsigned short UNBREAKABLE_WALL_NB = 92;
static const Vector3 WallPositions[UNBREAKABLE_WALL_NB] = {
    { -7, 0.0, -7 },
    { -7, 0.0, -6 },
    { -7, 0.0, -5 },
    { -7, 0.0, -4 },
    { -7, 0.0, -3 },
    { -7, 0.0, -2 },
    { -7, 0.0, -1 },
    { -7, 0.0, 0 },
    { -7, 0.0, 1 },
    { -7, 0.0, 2 },
    { -7, 0.0, 3 },
    { -7, 0.0, 4 },
    { -7, 0.0, 5 },
    { -7, 0.0, 6 },
    { -7, 0.0, 7 },
    { -6, 0.0, 7 },
    { -5, 0.0, 7 },
    { -4, 0.0, 7 },
    { -3, 0.0, 7 },
    { -2, 0.0, 7 },
    { -1, 0.0, 7 },
    { 0, 0.0, 7 },
    { 1, 0.0, 7 },
    { 2, 0.0, 7 },
    { 3, 0.0, 7 },
    { 4, 0.0, 7 },
    { 5, 0.0, 7 },
    { 6, 0.0, 7 },
    { 7, 0.0, 7 },
    { 7, 0.0, 6 },
    { 7, 0.0, 5 },
    { 7, 0.0, 4 },
    { 7, 0.0, 3 },
    { 7, 0.0, 2 },
    { 7, 0.0, 1 },
    { 7, 0.0, 0 },
    { 7, 0.0, -1 },
    { 7, 0.0, -2 },
    { 7, 0.0, -3 },
    { 7, 0.0, -4 },
    { 7, 0.0, -5 },
    { 7, 0.0, -6 },
    { 7, 0.0, -7 },
    { 6, 0.0, -7 },
    { 5, 0.0, -7 },
    { 4, 0.0, -7 },
    { 3, 0.0, -7 },
    { 2, 0.0, -7 },
    { 1, 0.0, -7 },
    { 0, 0.0, -7 },
    { -1, 0.0, -7 },
    { -2, 0.0, -7 },
    { -3, 0.0, -7 },
    { -4, 0.0, -7 },
    { -5, 0.0, -7 },
    { -6, 0.0, -7 },
    { -5, 0.0, -5 },
    { -3, 0.0, -5 },
    { -1, 0.0, -5 },
    { 1, 0.0, -5 },
    { 3, 0.0, -5 },
    { 5, 0.0, -5 },
    { -5, 0.0, -3 },
    { -3, 0.0, -3 },
    { -1, 0.0, -3 },
    { 1, 0.0, -3 },
    { 3, 0.0, -3 },
    { 5, 0.0, -3 },
    { -5, 0.0, -1 },
    { -3, 0.0, -1 },
    { -1, 0.0, -1 },
    { 1, 0.0, -1 },
    { 3, 0.0, -1 },
    { 5, 0.0, -1 },
    { -5, 0.0, 1 },
    { -3, 0.0, 1 },
    { -1, 0.0, 1 },
    { 1, 0.0, 1 },
    { 3, 0.0, 1 },
    { 5, 0.0, 1 },
    { -5, 0.0, 3 },
    { -3, 0.0, 3 },
    { -1, 0.0, 3 },
    { 1, 0.0, 3 },
    { 3, 0.0, 3 },
    { 5, 0.0, 3 },
    { -5, 0.0, 5 },
    { -3, 0.0, 5 },
    { -1, 0.0, 5 },
    { 1, 0.0, 5 },
    { 3, 0.0, 5 },
    { 5, 0.0, 5 },
};

class Wall {
private:
    ModelClass Awall;
    ImgTexture textureWall;
    DrawingProcess drawEvent;
    Vector3 positionWall = { 0.0f, 0.0f, 0.0f };
    bool isBreakable = false;

public:
    Wall();
    Wall(const bool &isBreakable);
    ~Wall();
    void setObject(Vector3 pos);
    void DrawWall(void) const;
    void setPosition(const Vector3 &pos);
    void setBreakable(const bool &breakable);
    bool getBreakable(void) const;
    const Vector3 &getPosition() const;
};
}
