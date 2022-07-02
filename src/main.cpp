/*
** EPITECH PROJECT, 2022
** main
** File description:
** main
*/

#include <iostream>
#include "gameloop.hpp"
#include "error.hpp"
#include "const.hpp"

int main(int ac, char **av)
{
    std::srand(time(NULL));

    try {
        game_loop();
    } catch (const Errors &e) {
        std::cerr << "Error(s): " << e.what() << std::endl;
        return ERROR;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return ERROR;
    }
    return EXIT_SUCCESS;
}
