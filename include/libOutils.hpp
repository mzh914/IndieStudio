/*
** EPITECH PROJECT, 2022
** object
** File description:
** object
*/

#pragma once

template <typename T>
class Libtools {
public:
    bool CheckCollision(T p1, T p2); // check collision with type vector3 and vector2
    void printVect(T v);
};

std::string getFile(const std::string &filepath);
bool special_char_in_str(std::string const &game_name);
