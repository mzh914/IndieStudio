/*
** EPITECH PROJECT, 2022
** bomb
** File description:
** bomb
*/

#include "Bomb.hpp"
#include "lib.hpp"
#include "const.hpp"

using namespace BombObj;

Bomb::Bomb(const IdPlayer &id, const BombType_e &type)
    : ExploTexture()
    , texture()
    , model()
    , Explosion()
    , drawEvent()
{
    ExploTexture.loadImage("../resources/bombs/explosion/blast.png");
    texture.loadImage(PathBombPng[type]);
    positions = NULL_Position;
    std::unique_ptr<SceneSound> sound(new SceneSound("explosion.wav"));
    bombExplosion = std::move(sound);
    Active = false;
    model.loadModel("../resources/bombs/bomb.obj");
    SetMaterialTexture(&model.getModel().materials[0], MATERIAL_MAP_DIFFUSE, texture.getTexture());
    // set explotion
    Explosion.loadModel("../resources/bombs/explosion/explosion.mtl");
    SetMaterialTexture(&Explosion.getModel().materials[0], MATERIAL_MAP_DIFFUSE, ExploTexture.getTexture());
    this->owner = id;
}

const IdPlayer &Bomb::getOwner() const
{
    return owner;
}

void Bomb::setOwner(const IdPlayer &id)
{
    this->owner = owner;
}

void Bomb::DrawBomb()
{
    if (Counter <= 0.0f && Active == false)
        Active = true;
    if (Counter <= -0.5f && Active == true) { // after exploration reset all
        Active = false;
        positions = NULL_Position;
    }
    if (positions != NULL_Position)
        Counter -= 0.025f;
    if (!Active)
        drawEvent.drawModel(model.getModel(), positions, 1.0f, WHITE);
    if (Active) {
        // sound for bomb explotion
        bombExplosion->playSound();
        for (size_t i = 0; i < sizeExplo; i++) {
            drawEvent.drawModel(Explosion.getModel(), { positions.x, 0.0f, positions.z - i }, 1.0f, WHITE);
            drawEvent.drawModel(Explosion.getModel(), { positions.x, 0.0f, positions.z + i }, 1.0f, WHITE);
            drawEvent.drawModel(Explosion.getModel(), { positions.x + i, 0.0f, positions.z }, 1.0f, WHITE);
            drawEvent.drawModel(Explosion.getModel(), { positions.x - i, 0.0f, positions.z }, 1.0f, WHITE);
        }
    }
}

void Bomb::operator=(const Vector3 &positions)
{
    this->positions.x = positions.x;
    this->positions.y = positions.y;
    this->positions.z = positions.z;
}

bool Bomb::putBomb(const Vector3 &positions, const IdPlayer &id, float size)
{
    Active = false;
    Counter = 4.0f;
    this->sizeExplo = size;
    this->owner = id;
    operator=(positions);
    return true;
}

Bomb::~Bomb()
{
}