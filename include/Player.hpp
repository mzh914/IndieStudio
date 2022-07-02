/*
** EPITECH PROJECT, 2022
** player
** File description:
** player
*/

#pragma once
#include <cstddef>
#include "Bomb.hpp"
#include "Drawing.hpp"
#include "playerUI.hpp"
#include "Model.hpp"

class Player {
public:
    Player(const IdPlayer &Id, const Vector3 &pos, const KeyboardKey key[5]);
    ~Player();
    void UpdataAnimation(KeyboardKey &inp);
    void DrawAnimation(); // call the draw ui function here
    bool CheckPlayerCollision() const;

    bool CanSetBomb;
    Vector3 position = { 0.0f, 0.0f, 0.0f };
    IdPlayer Id;
    bool dead;
    float speed;
    float bombSize = 2.0f;
    size_t MaxBomb; // for marking the number of the max bomb
    KeyboardKey input = KEY_NULL;
    bool WallPass = false;
    std::string wallPassTimer;

private:
    Vector3 animaitonposition = { 0.0f, 0.0f, 0.0f };
    float CdBomb = 5.0f;
    size_t CurrentBomb; // for marking the number of the bomb on the map
    KeyboardKey allKey[5];
    const std::string PathPlayer[NB_PLAYER] = {
        "../resources/player/textures/blue.png",
        "../resources/player/textures/green.png",
        "../resources/player/textures/red.png",
        "../resources/player/textures/yellow.png",
    };
    std::unique_ptr<SceneSound> playerMove;
    bool IsbuttonPressed = false;
    float moveCounter = 0.0f;
    ModelAnimation *anims;
    ModelClass model;
    ImgTexture texture;
    DrawingProcess drawEvent;
    size_t animFrameCounter = 0;
    size_t animCounter = 0;
    unsigned int animsCount = 0;
    bool PlayerAction = true; // the animation when player not move
    float rotationAngle = 0.0f;
};
