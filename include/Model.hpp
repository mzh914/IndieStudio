/*
** EPITECH PROJECT, 2021
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** Model.hpp
*/

#pragma once

#include "raylib.h"
#include <string>

class ModelClass {
public:
    ModelClass();
    ~ModelClass();
    void loadModel(std::string filename);
    Model getModel() const;

private:
    Model model;
};