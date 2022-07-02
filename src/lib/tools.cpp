/*
** EPITECH PROJECT, 2022
** outils
** File description:
** outils
*/

#include <algorithm>
#include <fstream>
#include "libOutils.hpp"
#include "error.hpp"

template <typename T>

bool Libtools<T>::CheckCollision(T v1, T v2)
{
    if ((v1.x < v2.x - 0.25f || v1.x > v2.x + 0.25f)
        || (v1.z < v2.z - 0.25f || v1.z > v2.z + 0.25f))
        return false;
    return true;
}

template <typename T>
void Libtools<T>::printVect(T v)
{
    std::cout << v.x << v.z << std::endl;
}

std::string getFile(const std::string &filepath)
{
    std::ifstream file(filepath);
    std::string line;

    if (!file.is_open())
        throw Errors(std::cerr, "file failed");
    while (std::getline(file, line)) {
    }
    file.close();
    return line;
}

bool special_char_in_str(std::string const &game_name)
{
    return std::find_if(game_name.begin(), game_name.end(),
               [](unsigned char curr_char) { return !(isalnum(curr_char) || curr_char == '_'); })
        != game_name.end();
}
