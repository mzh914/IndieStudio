/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** Drawing.hpp
*/

#pragma once

#include "raylib.h"

class DrawingProcess {
public:
    DrawingProcess();
    ~DrawingProcess() = default;
    void startDrawing();
    void endDrawing();
    void drawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint) const;
    void drawRectangleRec(Rectangle rec, Color color) const;
    void drawRectLines(int posX, int posY, int width, int height, Color color) const;
    void drawText(const std::string text, int posX, int posY, int fontSize, Color color) const;
    void clearBackground(Color color);
    void drawModel(Model model, Vector3 position, float scale, Color tint) const;

private:
};