/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** Texture.hpp
*/

#pragma once

#include "raylib.h"
#include <string>

class ImgTexture {
public:
    ImgTexture();
    ~ImgTexture();
    void loadImage(std::string filename);
    void drawImage(int posX, int posY, Color tint);
    Texture2D getTexture() const;

private:
    Texture2D _image;
};