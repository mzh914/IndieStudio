/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** drawing
*/

#include <string>
#include "Drawing.hpp"

DrawingProcess::DrawingProcess()
{
}

void DrawingProcess::startDrawing()
{
    BeginDrawing();
}

void DrawingProcess::endDrawing()
{
    EndDrawing();
}

void DrawingProcess::drawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint) const
{

    DrawTextureEx(texture, position, rotation, scale, tint);
}

void DrawingProcess::drawRectangleRec(Rectangle rec, Color color) const
{
    DrawRectangleRec(rec, color);
}

void DrawingProcess::drawRectLines(int posX, int posY, int width, int height, Color color) const
{

    DrawRectangleLines(posX, posY, width, height, color);
}

void DrawingProcess::drawText(const std::string text, int posX, int posY, int fontSize, Color color) const
{

    DrawText(text.c_str(), posX, posY, fontSize, color);
}

void DrawingProcess::clearBackground(Color color)
{
    ClearBackground(color);
}

void DrawingProcess::drawModel(Model model, Vector3 position, float scale, Color tint) const
{

    DrawModel(model, position, scale, tint);
}
