/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** texture
*/

#include "Texture.hpp"

ImgTexture::ImgTexture()
{
}

ImgTexture::~ImgTexture()
{
    UnloadTexture(_image);
}

void ImgTexture::loadImage(std::string filename)
{
    _image = LoadTexture(filename.c_str());
}

void ImgTexture::drawImage(int posX, int posY, Color tint)
{
    DrawTexture(_image, posX, posY, tint);
}

Texture2D ImgTexture::getTexture() const
{
    return _image;
}
