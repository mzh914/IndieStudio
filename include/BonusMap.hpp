/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** Bonus
*/

#pragma once

#include "const.hpp"
#include "Texture.hpp"
#include "Drawing.hpp"
#include "Model.hpp"

class BonusMap {
private:
    ModelClass Abonus;
    DrawingProcess drawEvent;
    ImgTexture textureBonus;
    Vector3 positionBonus = { 0.0f, 0.0f, 0.0f };
    Bonus bonusType = None;

public:
    BonusMap(const Bonus &bonusType, const Vector3 &wallPos);
    ~BonusMap();
    void setObject(Vector3 pos);
    void DrawBonus(void) const;
    void setPosition(const Vector3 &pos);
    void setBonusType(const Bonus &bonusType);
    Bonus getBonusType(void) const;
    const Vector3 &getPosition(void) const;
};
