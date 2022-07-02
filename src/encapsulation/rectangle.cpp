/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** rectangle
*/

#include "Rectangle.hpp"

RectangleClass::RectangleClass()
{
}

void RectangleClass::setRect(float x, float y, float width, float height)
{
    rectItems = { x, y, width, height };
}

Rectangle RectangleClass::getRect()
{
    return rectItems;
}
