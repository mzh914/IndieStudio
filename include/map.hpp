/*
** EPITECH PROJECT, 2022
** map
** File description:
** map
*/

#pragma once

#include <vector>
#include <memory>
#include "wall.hpp"
#include "Player.hpp"
#include "libOutils.hpp"
#include "BonusMap.hpp"

class Text {
public:
    Text();
    ~Text();

private:
    std::string text;
    int pos;
};

class Map {
private:
    Libtools<Vector3> tool;
    ImgTexture background;
    DrawingProcess drawEvent;
    std::vector<std::unique_ptr<BombObj::Bomb>> AllBomb;
    std::vector<std::unique_ptr<Player>> AllPlayer;
    std::vector<std::unique_ptr<WallObj::Wall>> wallBreakable;
    std::vector<std::unique_ptr<BonusMap>> bonusMap;
    std::vector<KeyboardKey> aikey1;
    std::vector<KeyboardKey> aikey2;
    std::vector<KeyboardKey> aikey3;
    std::vector<KeyboardKey> aikey4;
    size_t nmPlayer;
    bool isAi[4] = {false};
    float aibombCounter[4] = {0.0};
    bool check_ai_bomb[4] = {false};
    Vector3 allposspwan[4] = {
        { -5.0, 0.0, -6.0 },
        { -6.0, 0.0, 5.0 },
        { 6.0, 0.0, -5.0 },
        { 5.0, 0.0, 6.0 }
    };
    ImgTexture allui[4]; // init
    Vector2 alluiPos[4];
    WallObj::Wall wallUnbreakable[WallObj::UNBREAKABLE_WALL_NB];
    KeyboardKey allkeys[4][5] = {
        { KEY_RIGHT, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_ENTER },
        { KEY_D, KEY_A, KEY_S, KEY_W, KEY_E },
        { KEY_H, KEY_F, KEY_G, KEY_T, KEY_Y },
        { KEY_L, KEY_J, KEY_K, KEY_I, KEY_O },
    };
    bool CheckPlayerCollision(const KeyboardKey &inp, const size_t &id);
    KeyboardKey GetInput(KeyboardKey &input, const KeyboardKey key[5], const int &i);
    bool CheckExplosion(const Vector3 &pos, const Vector3 &pos2, const float &size);
    KeyboardKey GetAIkey(const size_t &id, std::vector<KeyboardKey> &aikey);
    KeyboardKey CheckInputAI(const KeyboardKey &input, const size_t &id);
    void PlayerCreate();
    void BombCreate();
    void PutWallBreakable(const Vector3 &pos);
    void RandomBreakableWall(void);
    void EndGame(SceneProcess &scene);

    float aicounter = 0.0f;
    std::unique_ptr<SceneSound> bombDropping;
    std::unique_ptr<SceneSound> playerDeath;
    void doBonus(const Bonus &bonusType, Player &player);

public:
    Map();
    void reset();
    IdPlayer deads[4] = { UNKNOWN_P, UNKNOWN_P, UNKNOWN_P, UNKNOWN_P };
    int death_count = 0;
    void DrawMap();
    std::string getTimer(int mode = 0);
    void DrawTimer();
    void Update(SceneProcess &scene);
    void DrawBackground(void);
    bool isGameOver(void) const;
    void addPlayerInSave();
    std::string getPlayerBombSize();
    std::string getPlayerSpeed();
    std::string getPlayerMaxBomb();
    std::string getPlayerWallPass();
    void setPlayerBombSize(float nb, int id);
    void setPlayerSpeed(float nb, int id);
    void setPlayerMaxBomb(size_t nb, int id);
    void setPlayerWallPass(bool b, int id);
    void writeInFile(std::vector<std::string> v);
    void readFromFile(std::vector<std::string> &v);
    void setPlayer();
    ~Map();
};
