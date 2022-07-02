/*
** EPITECH PROJECT, 2022
** wall
** File description:
** wall
*/

#include "wall.hpp"
#include "const.hpp"

WallObj::Wall::Wall(const bool &isBreakable)
    : textureWall()
    , drawEvent()
    , Awall()
{
    this->isBreakable = isBreakable;
    textureWall.loadImage(
        this->isBreakable ? "../resources/map/breakable_wall.png"
                          : "../resources/map/unbreakable_wall.png");
    Awall.loadModel("../resources/map/breakable_wall.mtl");
    SetMaterialTexture(&Awall.getModel().materials[0], MATERIAL_MAP_DIFFUSE, textureWall.getTexture());
}

WallObj::Wall::Wall()
{
    textureWall.loadImage("../resources/map/unbreakable_wall.png");
    Awall.loadModel("../resources/map/breakable_wall.mtl");
    SetMaterialTexture(&Awall.getModel().materials[0], MATERIAL_MAP_DIFFUSE, textureWall.getTexture());
}

WallObj::Wall::~Wall()
{
}

const Vector3 &WallObj::Wall::getPosition() const
{
    return positionWall;
}

void WallObj::Wall::DrawWall(void) const
{
    drawEvent.drawModel(Awall.getModel(), positionWall, 1.0f, WHITE);
}

void WallObj::Wall::setPosition(const Vector3 &pos)
{
    positionWall = pos;
}

void WallObj::Wall::setBreakable(const bool &breakable)
{
    isBreakable = breakable;
}

bool WallObj::Wall::getBreakable(void) const
{
    return isBreakable;
}
