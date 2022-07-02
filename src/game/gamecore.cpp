/*
** EPITECH PROJECT, 2022
** menu
** File description:
** menu
*/

#include "gameCore.hpp"
#include "loadOrNew.hpp"
#include "loadGame.hpp"
#include "newGame.hpp"
#include "help.hpp"
#include "gameloop.hpp"
#include "wall.hpp"
#include "selectPlayer.hpp"

static void change_current(Core &gamecore, SceneProcess const &PreScene, SceneProcess const &CurrentScene)
{
    if (PreScene != CurrentScene) {
        switch (CurrentScene) {
        case LOAD_OR_NEW:
            gamecore.current = std::make_unique<loadOrNew>();
            break;
        case MENU_SCENE:
            gamecore.current = std::make_unique<menu>();
            break;
        case LOAD_GAME:
            gamecore.current = std::make_unique<loadGame>();
            break;
        case NEW_GAME:
            gamecore.current = std::make_unique<newGame>();
            break;
        case SELECT_SCENE:
            gamecore.current = std::make_unique<selectPlayer>();
            break;
        case HELP_SCENE:
            gamecore.current = std::make_unique<help>();
            break;
        case GAME_SCENE:
            gamecore.current = std::make_unique<GameLoop>();
            break;
        }
    }
}

void game_loop(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Super Bomberman");
    InitAudioDevice();
    SetExitKey(0);
    Core gamecore;
    SceneProcess CurrentScene = MENU_SCENE;
    SceneProcess PreScene = MENU_SCENE;

    SetTargetFPS(FPS);
    auto scene = gamecore.current.get();
    while (true) {
        PreScene = CurrentScene;
        scene->Loop(CurrentScene);
        change_current(gamecore, PreScene, CurrentScene);
        if (WindowShouldClose() || CurrentScene == EXIT_SCENE || IsKeyDown(KEY_ESCAPE))
            break;
        scene = gamecore.current.get();
        scene->draw();
    }
    remove_isplaying("save.txt");
    gamecore.~Core();
    CloseWindow();
}
