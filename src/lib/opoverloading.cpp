/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** opoverloading
*/

#include "raylib.h"

const bool operator==(Vector3 v1, Vector3 v2)
{
    if ((v1.x < v2.x - 0.25f || v1.x > v2.x + 0.25f)
        || (v1.z < v2.z - 0.25f || v1.z > v2.z + 0.25f))
        return false;
    return true;
}

const bool operator!=(Vector3 v1, Vector3 v2)
{
    return !operator==(v1, v2);
}

const bool operator==(Color c1, Color c2)
{
    return (c1.a == c2.a && c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
}
