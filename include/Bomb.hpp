/*
** EPITECH PROJECT, 2022
** player
** File description:
** player
*/

#pragma once

#include <memory>
#include <string>
#include "sound.hpp"
#include "Texture.hpp"
#include "Model.hpp"
#include "Drawing.hpp"

typedef enum IdPlayer_e {
    UNKNOWN_P = -1,
    BLUE_P,
    GREEN_P,
    RED_P,
    YELLOW_P,
    NB_PLAYER
} IdPlayer;

typedef enum BombType_e {
    NORMAL_BOMB = 0,
    FIRE_BOMB,
    PLASMA_BOMB,
    SEXY_BOMB,
    WATER_BOMB,
} BombType;

namespace BombObj {
class Bomb {
public:
    Bomb(const IdPlayer &id, const BombType_e &type);
    ~Bomb();

    bool Active = false;
    Vector3 positions = { 0.0f, 0.0f, 0.0f };
    const IdPlayer &getOwner() const;
    void setOwner(const IdPlayer &id);
    bool putBomb(const Vector3 &positions, const IdPlayer &id, float sizeExplo);
    void operator=(const Vector3 &positions);
    void DrawBomb();
    float sizeExplo = 2;

private:
    float Counter = 4.0f;
    ModelClass model;
    ModelClass Explosion;
    DrawingProcess drawEvent;
    std::unique_ptr<SceneSound> bombExplosion;
    const std::string PathBombPng[5] = {
        "../resources/bombs/bomb_normal.png",
        "../resources/bombs/bomb_fire.png",
        "../resources/bombs/bomb_plasma.png",
        "../resources/bombs/bomb_sexy.png",
        "../resources/bombs/bomb_water.png",
    };
    ImgTexture ExploTexture;
    ImgTexture texture;
    IdPlayer owner;
};
}
