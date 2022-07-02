/*
** EPITECH PROJECT, 2022
** B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi
** File description:
** const
*/

#pragma once
#include <string>
#include "raylib.h"

static const unsigned char GOOD = 0;
static const unsigned char ERROR = 84;
static const char FAIL = -1;
static const unsigned short SCREEN_WIDTH = 1600;
static const unsigned short SCREEN_HEIGHT = 900;
static const unsigned short FPS = 60;
static const unsigned short SCENE_LENGTH = 7;
static const unsigned short TIMER_SIZE = 70;
static const char MUSIC_PATH[] = "../resources/musics/";
static const char SOUND_PATH[] = "../resources/sounds/";
static const unsigned short MAX_PLAYER = 4;
static const unsigned short NB_SLOT = 5;
static const char IMG_NB[5][21] = { "../resources/nb0.png", "../resources/nb1.png", "../resources/nb2.png", "../resources/nb3.png", "../resources/nb4.png" };

typedef enum SceneProcess_e {
    EXIT_SCENE = -2,
    NULL_SCENE = -1,
    MENU_SCENE = 0,
    LOAD_OR_NEW,
    LOAD_GAME,
    NEW_GAME,
    SELECT_SCENE,
    HELP_SCENE,
    GAME_SCENE,
} SceneProcess;

typedef enum ImageProcess_e {
    START = 0,
    HELP,
    EXIT,
} ImageProcess;

typedef enum Bonus_e {
    None,
    BombUp,
    SpeedUp,
    FireUp,
    WallPass,
} Bonus;

typedef enum GameKeys_e {
    NULL_KEY = -1,
    REPLAY,
    BACK_TO_MENU,
    CONTINUE,
} GameKeys;

static const Vector3 NULL_Position = { -999.0f, -999.0f, -999.0f };
