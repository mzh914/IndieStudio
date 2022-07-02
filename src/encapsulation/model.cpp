/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** model
*/

#include "Model.hpp"

ModelClass::ModelClass()
{
}

ModelClass::~ModelClass()
{
    UnloadModel(model);
}

void ModelClass::loadModel(std::string filename)
{
    model = LoadModel(filename.c_str());
}

Model ModelClass::getModel() const
{
    return model;
}
