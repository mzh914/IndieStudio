/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** music
*/

#include "music.hpp"

SceneMusic::SceneMusic(const std::string &fileName)
{
    std::string filePath;

    filePath.assign(MUSIC_PATH);
    filePath.append(fileName.c_str());
    music = LoadMusicStream(filePath.c_str());
}

void SceneMusic::setMusic(const std::string &fileName)
{
    std::string filePath;

    filePath.assign(MUSIC_PATH);
    filePath.append(fileName.c_str());
    music = LoadMusicStream(filePath.c_str());
}

Music SceneMusic::getMusic()
{
    return music;
}

void SceneMusic::playMusic()
{
    PlayMusicStream(music);
}

void SceneMusic::updateMusic()
{
    UpdateMusicStream(music);
}

SceneMusic::~SceneMusic()
{
    StopMusicStream(music);
    UnloadMusicStream(music);
}