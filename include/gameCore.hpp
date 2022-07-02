/*
** EPITECH PROJECT, 2022
** gamecore
** File description:
** core
*/

#pragma once
#include <memory>
#include "IScene.hpp"
#include "menu.hpp"

class Core {
private:
public:
    std::unique_ptr<IScene> current = std::make_unique<menu>();
    Core(/* args */) {};
    ~Core() {};
};
