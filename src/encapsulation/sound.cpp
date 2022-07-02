/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** sound
*/

#include "sound.hpp"

SceneSound::SceneSound(const std::string &fileName)
{
    std::string filePath;

    filePath.assign(SOUND_PATH);
    filePath.append(fileName.c_str());
    sound = LoadSound(filePath.c_str());
}

void SceneSound::setSound(const std::string &fileName)
{
    std::string filePath;

    filePath.assign(SOUND_PATH);
    filePath.append(fileName.c_str());
    sound = LoadSound(filePath.c_str());
}

Sound SceneSound::getSound()
{
    return sound;
}

void SceneSound::playSound()
{
    PlaySound(sound);
}

void SceneSound::playSoundMulti()
{
    PlaySoundMulti(sound);
}

SceneSound::~SceneSound()
{
    StopSound(sound);
    UnloadSound(sound);
}