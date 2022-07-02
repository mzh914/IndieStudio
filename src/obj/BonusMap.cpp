/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** BonusMap
*/

#include "BonusMap.hpp"

static const std::string getBonusModel(const Bonus &type)
{
    switch (type) {
    case BombUp:
        return "../resources/items/bombup.mtl";
    case SpeedUp:
        return "../resources/items/speedup.mtl";
    case FireUp:
        return "../resources/items/fireup.mtl";
    case WallPass:
        return "../resources/items/wallpass.mtl";
    }
    return "../resources/items/bombup.mtl";
}

BonusMap::BonusMap(const Bonus &bonusType, const Vector3 &wallPos)
    : textureBonus()
    , Abonus()
    , drawEvent()
{
    this->bonusType = bonusType;
    if (bonusType == BombUp)
        textureBonus.loadImage("../resources/items/BombUp.png");
    else if (bonusType == SpeedUp)
        textureBonus.loadImage("../resources/items/SpeedUp.png");
    else if (bonusType == FireUp)
        textureBonus.loadImage("../resources/items/FireUp.png");
    else
        textureBonus.loadImage("../resources/items/WallPass.png");
    Abonus.loadModel(getBonusModel(bonusType).c_str());
    SetMaterialTexture(&Abonus.getModel().materials[0], MATERIAL_MAP_DIFFUSE, textureBonus.getTexture());
    setPosition(wallPos);
}

BonusMap::~BonusMap()
{
}

const Vector3 &BonusMap::getPosition() const
{
    return positionBonus;
}

void BonusMap::DrawBonus(void) const
{
    drawEvent.drawModel(Abonus.getModel(), positionBonus, 1.0f, WHITE);
}

void BonusMap::setPosition(const Vector3 &pos)
{
    positionBonus = pos;
}

void BonusMap::setBonusType(const Bonus &type)
{
    bonusType = type;
}

Bonus BonusMap::getBonusType(void) const
{
    return bonusType;
}
