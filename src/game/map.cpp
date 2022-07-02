/*
** EPITECH PROJECT, 2022
** map
** File description:
** map
*/

#include <fstream>
#include <algorithm>
#include <cmath>
#include "const.hpp"
#include "error.hpp"
#include "map.hpp"
#include "pause.hpp"
#include "lib.hpp"
#include "raylib.h"

static bool is_spawn(const float &i, const float &t)
{
    if (i == -6 || i == 6)
        if (t == -6 || t == -5 || t == 6 || t == 5)
            return true;
    if (i == -5 || i == 5)
        if (t == -6 || t == 6)
            return true;
    return false;
}

void Map::RandomBreakableWall(void)
{
    bool has_found = false;

    for (float i = -6; i < 7; ++i) {
        for (float t = -6; t < 7; ++t) {
            has_found = false;
            if (is_spawn(i, t))
                continue;
            Vector3 pos = { i, 0, t };
            for (int k = 0; k < WallObj::UNBREAKABLE_WALL_NB; ++k)
                if (pos == WallObj::WallPositions[k])
                    has_found = true;
            if (!has_found && (std::rand() % 10) >= 6) // (10 - 3 = 7, so 70% luck)
                PutWallBreakable({ i, 0, t });
        }
    }
}

Map::Map()
    : background()
    , drawEvent()
{
    std::unique_ptr<SceneSound> sound(new SceneSound("failing.wav"));
    playerDeath = std::move(sound);
    background.loadImage("../resources/map/background.png");
    PlayerCreate();
    BombCreate();
    for (size_t i = 0; i < WallObj::UNBREAKABLE_WALL_NB; ++i) {
        wallUnbreakable[i].setBreakable(false);
        wallUnbreakable[i].setPosition(WallObj::WallPositions[i]);
    }
    RandomBreakableWall();
}

void Map::doBonus(const Bonus &bonusType, Player &player)
{
    switch (bonusType) {
    case BombUp:
        player.MaxBomb += 1;
        break;
    case SpeedUp:
        player.speed += 0.01;
        break;
    case FireUp:
        player.bombSize += 1.0f;
        break;
    case WallPass:
        player.WallPass = true;
        player.wallPassTimer = getTimer();
        break;
    };
}

bool Map::CheckPlayerCollision(const KeyboardKey &inp, const size_t &id)
{
    auto player = AllPlayer[id].get();
    Vector3 tmp = player->position;
    KeyboardKey key[4] = {};

    for (size_t i = 0; i < 4; ++i)
        key[i] = allkeys[id][i];
    if (inp == key[0]) {
        tmp.x += 1.0f;
    } else if (inp == key[1]) {
        tmp.x -= 1.0f;
    } else if (inp == key[2]) {
        tmp.z += 1.0f;
    } else if (inp == key[3]) {
        tmp.z -= 1.0f;
    }
    for (size_t i = 0; i < WallObj::UNBREAKABLE_WALL_NB; ++i) {
        if (wallUnbreakable[i].getPosition() == tmp)
            return false;
    }
    for (size_t i = 0; i < AllBomb.size(); ++i) {
        if (AllBomb[i].get()->positions == tmp)
            return false;
    }
    for (size_t i = 0; i < bonusMap.size(); ++i) {
        if (bonusMap[i].get()->getPosition() == tmp) {
            doBonus(bonusMap[i].get()->getBonusType(), *player);
            bonusMap.erase(bonusMap.begin() + i);
        }
    }
    if (player->WallPass == true)
        return true;
    for (size_t i = 0; i < wallBreakable.size(); ++i) {
        if (wallBreakable[i].get()->getPosition() == tmp)
            return false;
    }
    return true;
}

KeyboardKey Map::GetInput(KeyboardKey &input, const KeyboardKey key[5], const int &i)
{
    auto player = AllPlayer[i].get();

    input = KEY_NULL;
    if (IsKeyDown(key[0]) && CheckPlayerCollision(key[0], i)) {
        input = key[0];
    } else if (IsKeyDown(key[1]) && CheckPlayerCollision(key[1], i)) {
        input = key[1];
    } else if (IsKeyDown(key[2]) && CheckPlayerCollision(key[2], i)) {
        input = key[2];
    } else if (IsKeyDown(key[3]) && CheckPlayerCollision(key[3], i)) {
        input = key[3];
    } else if (IsKeyReleased(key[4]))
        input = key[4];
    return input;
}

bool Map::CheckExplosion(const Vector3 &pos1, const Vector3 &pos2, const float &size)
{
    float tmprange = size - 0.75;

    if ((pos2.x < pos1.x + tmprange && pos2.x > pos1.x - tmprange && pos1.z == pos2.z)
        || (pos2.z < pos1.z + tmprange && pos2.z > pos1.z - tmprange && pos1.x == pos2.x))
        return false;
    return true;
}

KeyboardKey Map::CheckInputAI(const KeyboardKey &input, const size_t &id)
{
    auto pos = AllPlayer[id].get()->position;

    for (size_t i = 0; i < 4; ++i) {
        if (CheckPlayerCollision(input, id))
            return input;
    }
    return KEY_NULL;
}

KeyboardKey Map::GetAIkey(const size_t &id, std::vector<KeyboardKey> &aikey)
{
    // bomb handling
    auto player = AllPlayer[id].get();
    if (player->dead)
        return KEY_NULL;
    auto tmpPosition = player->position;
    // algo for dodge bombs
    if (aikey.size() == 0) {
        for (size_t i = 0; i < AllBomb.size(); ++i) {
            auto bomb = AllBomb[i].get()->positions;
            if (bomb == NULL_Position)
                continue;
            auto posX = tmpPosition.x - bomb.x;
            auto posZ = tmpPosition.z - bomb.z;
            // negative is bomb at rigth the AI
            if (posZ == 0 && (posX <= 2.5 && posX >= -2.5)) {
                check_ai_bomb[id] = true;
                if (CheckPlayerCollision(KEY_UP, id)) {
                    aikey.emplace_back(KEY_UP);
                    break;
                } else if (CheckPlayerCollision(KEY_DOWN, id)) {
                    aikey.emplace_back(KEY_DOWN);
                    break;
                }
                if (CheckPlayerCollision(KEY_RIGHT, id)) {
                    tmpPosition.x += 1.0f;
                    aikey.emplace_back(KEY_RIGHT);
                } else if (CheckPlayerCollision(KEY_LEFT, id)) {
                    tmpPosition.x -= 1.0f;
                    aikey.emplace_back(KEY_LEFT);
                }
            } else if (posX == 0 && (posZ <= 2.5 && posZ >= -2.5)) {
                check_ai_bomb[id] = true;
                if (CheckPlayerCollision(KEY_RIGHT, id)) {
                    aikey.emplace_back(KEY_RIGHT);
                    break;
                } else if (CheckPlayerCollision(KEY_LEFT, id)) {
                    aikey.emplace_back(KEY_LEFT);
                    break;
                }
                if (CheckPlayerCollision(KEY_UP, id)) {
                    tmpPosition.z -= 1.0f;
                    aikey.emplace_back(KEY_UP);
                } else if (CheckPlayerCollision(KEY_DOWN, id)) {
                    tmpPosition.z += 1.0f;
                    aikey.emplace_back(KEY_DOWN);
                }
            }
        }
    }
    if (check_ai_bomb[id] == true)
        aibombCounter[id] += 0.025f;
    if (aibombCounter[id] > 4.5f) {
        aibombCounter[id] = 0;
        check_ai_bomb[id] = false;
    }
    if (check_ai_bomb[id] == true && aikey.size() == 0)
        return KEY_NULL;
    if (aikey.size() == 0) {
        return allkeys[id][std::rand() % 5];
    }
    KeyboardKey tmp = aikey[0];
    aikey.erase(aikey.begin());
    return tmp;
}

static const Bonus randomBonusType(void)
{
    int random = std::rand() % 4;
    Bonus bonus = None;

    switch (random) {
    case 0:
        bonus = BombUp;
        break;
    case 1:
        bonus = SpeedUp;
        break;
    case 2:
        bonus = FireUp;
        break;
    case 3:
        bonus = WallPass;
        break;
    }
    return bonus;
}

void Map::Update(SceneProcess &scene)
{
    KeyboardKey inputList[nmPlayer];
    // get input and send to player
    for (size_t i = 0; i < nmPlayer; ++i) {
        if (isAi[i] == true) {
            if (i == 0)
                inputList[i] = CheckInputAI(GetAIkey(i, aikey1), i);
            else if (i == 1)
                inputList[i] = CheckInputAI(GetAIkey(i, aikey2), i);
            else if (i == 2)
                inputList[i] = CheckInputAI(GetAIkey(i, aikey3), i);
            else if (i == 3)
                inputList[i] = CheckInputAI(GetAIkey(i, aikey4), i);
        } else {
            inputList[i] = GetInput(inputList[i], allkeys[i], i);
        }
    }
    // check the bomb explotion, if player touch explotion set player->dead = true
    for (size_t i = 0; i < AllBomb.size(); ++i) {
        // for all player , if touch bomb fire , set player dead
        for (size_t j = 0; j < AllPlayer.size(); ++j) {
            if (AllPlayer[j].get()->dead)
                continue;
            if (AllBomb[i].get()->Active && !CheckExplosion(AllBomb[i].get()->positions, AllPlayer[j].get()->position, AllBomb[i].get()->sizeExplo)) {
                AllPlayer[j].get()->dead = true;
                deads[death_count++] = AllPlayer[j].get()->Id;
                playerDeath->playSoundMulti();
                break;
            }
        }
        // for all wall breakable, if touch bomb fire, delete wall
        for (size_t j = 0; j < wallBreakable.size(); ++j) {
            auto bomb = AllBomb[i].get();
            if (bomb->Active && !CheckExplosion(bomb->positions, wallBreakable[j].get()->getPosition(), bomb->sizeExplo)) {
                if (std::rand() % 2 == 0)
                    bonusMap.emplace_back(new BonusMap(randomBonusType(), wallBreakable[j]->getPosition()));
                wallBreakable.erase(wallBreakable.begin() + j);
            }
        }
    }

    // update animation player if player not dead
    for (size_t i = 0; i < AllPlayer.size(); ++i) {
        auto player = AllPlayer[i].get();
        if (player->dead == true)
            continue;
        player->UpdataAnimation(inputList[i]);
        // set bomb for all player
        if (player->CanSetBomb && i < 4) {
            for (size_t j = 0; j < AllBomb.size(); ++j) {
                if (!(AllBomb[j].get()->positions != NULL_Position)
                    && AllBomb[j].get()->getOwner() == player->Id) {
                    AllBomb[j]->putBomb(player->position, player->Id, player->bombSize);
                    break;
                }
            }
        }
    }
    // update scene
    EndGame(scene);
}

void Map::EndGame(SceneProcess &scene)
{
    IdPlayer winner = UNKNOWN_P;
    const IdPlayer players[NB_PLAYER + 1] = { UNKNOWN_P, BLUE_P, GREEN_P, RED_P, YELLOW_P };

    if (death_count == 3) {
        for (int i = 0; i < NB_PLAYER + 1; ++i) {
            if (players[i] == UNKNOWN_P)
                continue;
            for (int t = 0; t < NB_PLAYER; ++t)
                std::find(deads, deads + NB_PLAYER, players[i]) == deads + NB_PLAYER
                    ? winner = players[i]
                    : 0;
        }
        deads[death_count] = winner;
    }
}

static float my_atof(std::string const &str)
{
    return std::atof(str.c_str());
}

void Map::setPlayer()
{
    std::vector<std::string> saveFile;
    int i = 0;

    readFromFile(saveFile);
    for (; saveFile[i].substr((saveFile[i].find(':') + 1), saveFile[i].find_last_of('g')) != ":isplaying"; ++i) { }
    i++;
    for (int t = i; t < i + 3; t++) {
        std::vector<float> nb;
        nb.push_back(my_atof(saveFile[t].substr(0, saveFile[t].find(':'))));
        nb.push_back(my_atof(saveFile[t].substr(saveFile[t].find(':') + 1, (saveFile[t].find(':', saveFile[t].find(':') + 1) + 1) - saveFile[t].find(':') - 2)));
        nb.push_back(my_atof(saveFile[t].substr(saveFile[t].find(':', saveFile[t].find(':') + 1) + 1, saveFile[t].find_last_of(':') - (saveFile[t].find(':', saveFile[t].find(':') + 1) + 1))));
        nb.push_back(my_atof(saveFile[t].substr(saveFile[t].find_last_of(':') + 1, saveFile[t].size())));
        for (int z = 0; i - t == 0 && z < 4; ++z)
            setPlayerBombSize(nb[z], z);
        for (int z = 0; i - t == -1 && z < 4; ++z)
            setPlayerSpeed(nb[z], z);
        for (int z = 0; i - t == -2 && z < 4; ++z)
            setPlayerMaxBomb(nb[z], z);
    }
    std::string wallPass[4] = {
        saveFile[i + 3].substr(0, saveFile[i + 3].find(':')),
        saveFile[i + 3].substr(saveFile[i + 3].find(':') + 1, saveFile[i + 3].find(':', 2)),
        saveFile[i + 3].substr(saveFile[i + 3].find(':', saveFile[i + 3].find(':') + 1) + 1, saveFile[i + 3].find_last_of(':') - (saveFile[i + 3].find(':', saveFile[i + 3].find(':') + 1) + 1)),
        saveFile[i + 3].substr(saveFile[i + 3].find_last_of(':') + 1, saveFile[i + 3].size())
    };
    for (int z = 0; z < 4; ++z)
        setPlayerWallPass(wallPass[z][0] == 't' ? true : false, z);
}

void Map::reset()
{
    std::vector<std::unique_ptr<BombObj::Bomb>>().swap(AllBomb);
    std::vector<std::unique_ptr<Player>>().swap(AllPlayer);
    std::vector<std::unique_ptr<WallObj::Wall>>().swap(wallBreakable);
    std::vector<std::unique_ptr<BonusMap>>().swap(bonusMap);

    death_count = 0;
    PlayerCreate();
    BombCreate();
    RandomBreakableWall();
    getTimer(1);
}

std::string Map::getPlayerBombSize()
{
    std::string playerStats;

    for (int i = 0; i < AllPlayer.size(); ++i) {
        playerStats += std::to_string(AllPlayer[i].get()->bombSize).c_str();
        if (i != AllPlayer.size() - 1)
            playerStats += ":";
    }
    return playerStats;
}

std::string Map::getPlayerSpeed()
{
    std::string playerStats;
    for (int i = 0; i < AllPlayer.size(); ++i) {
        playerStats += std::to_string(AllPlayer[i].get()->speed).c_str();
        if (i != AllPlayer.size() - 1)
            playerStats += ":";
    }
    return playerStats;
}

std::string Map::getPlayerMaxBomb()
{
    std::string playerStats;
    for (int i = 0; i < AllPlayer.size(); ++i) {
        playerStats += std::to_string(AllPlayer[i].get()->MaxBomb).c_str();
        if (i != AllPlayer.size() - 1)
            playerStats += ":";
    }
    return playerStats;
}

std::string Map::getPlayerWallPass()
{
    std::string playerStats;
    for (int i = 0; i < AllPlayer.size(); ++i) {
        playerStats += AllPlayer[i].get()->WallPass ? "true" : "false";
        if (i != AllPlayer.size() - 1)
            playerStats += ":";
    }
    return playerStats;
}

void Map::writeInFile(std::vector<std::string> v)
{
    std::ofstream file;
    file.open("save.txt");
    for (int i = 0; i < v.size(); ++i) {
        file << v[i] << std::endl;
    }
    file.close();
}

void Map::setPlayerBombSize(float nb, int id)
{
    AllPlayer[id].get()->bombSize = nb;
}

void Map::setPlayerSpeed(float nb, int id)
{
    AllPlayer[id].get()->speed = nb;
}

void Map::setPlayerMaxBomb(size_t nb, int id)
{
    AllPlayer[id].get()->MaxBomb = nb;
}

void Map::setPlayerWallPass(bool b, int id)
{
    AllPlayer[id].get()->WallPass = b;
}

void Map::readFromFile(std::vector<std::string> &v)
{
    std::ifstream file;
    file.open("save.txt");
    std::string line;
    while (getline(file, line))
        v.push_back(line);
    file.close();
}

void Map::addPlayerInSave()
{
    std::vector<std::string> saveFile;

    readFromFile(saveFile);
    for (int i = 0; i < saveFile.size(); ++i) {
        if (saveFile[i].substr((saveFile[i].find(':') + 1), saveFile[i].find_last_of('g')) == ":isplaying") {
            saveFile[i].erase(saveFile[i].find(':') + 1);
            saveFile[i + 1] = getPlayerBombSize();
            saveFile[i + 2] = getPlayerSpeed();
            saveFile[i + 3] = getPlayerMaxBomb();
            saveFile[i + 4] = getPlayerWallPass();
            writeInFile(saveFile);
            return;
        }
    }
    saveFile.emplace_back(getPlayerBombSize());
    saveFile.emplace_back(getPlayerSpeed());
    saveFile.emplace_back(getPlayerMaxBomb());
    saveFile.emplace_back(getPlayerWallPass());
    writeInFile(saveFile);
}

std::string Map::getTimer(int mode)
{
    static int timer = 0;
    static float clock = 0;
    std::string time;

    if (mode == 1) {
        timer = 0;
        clock = 0;
    } else if (mode == 0) {
        clock += GetFrameTime() * 1000;
        if (clock >= 1000.0) {
            timer += 1;
            clock = 0;
        }
    }
    if (timer / 60 < 10)
        time.push_back('0');
    time.append(std::to_string(timer / 60) + ":");
    if (timer % 60 < 10)
        time.push_back('0');
    time.append(std::to_string(timer % 60));
    return time;
}

void Map::DrawTimer()
{
    int posX = SCREEN_WIDTH / 2 - TIMER_SIZE - TIMER_SIZE / 5;

    drawEvent.drawText(getTimer(), posX, 0, TIMER_SIZE, WHITE);
}

void Map::DrawMap()
{

    for (size_t i = 0; i < AllPlayer.size(); ++i) {
        AllPlayer[i]->DrawAnimation();
    }
    for (size_t j = 0; j < AllBomb.size(); ++j) {
        AllBomb[j]->DrawBomb();
    }
    for (size_t i = 0; i < WallObj::UNBREAKABLE_WALL_NB; ++i) {
        wallUnbreakable[i].DrawWall();
    }
    for (size_t i = 0; i < wallBreakable.size(); ++i) {
        wallBreakable[i]->DrawWall();
    }
    for (size_t i = 0; i < bonusMap.size(); ++i) {
        bonusMap[i]->DrawBonus();
    }
}

void Map::BombCreate()
{
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::RED_P, BombType::NORMAL_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::RED_P, BombType::NORMAL_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::RED_P, BombType::NORMAL_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::BLUE_P, BombType::WATER_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::BLUE_P, BombType::WATER_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::BLUE_P, BombType::WATER_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::YELLOW_P, BombType::SEXY_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::YELLOW_P, BombType::SEXY_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::YELLOW_P, BombType::SEXY_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::GREEN_P, BombType::PLASMA_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::GREEN_P, BombType::PLASMA_BOMB));
    AllBomb.emplace_back(new BombObj::Bomb(IdPlayer::GREEN_P, BombType::PLASMA_BOMB));
}

void Map::PutWallBreakable(const Vector3 &pos)
{
    std::unique_ptr<WallObj::Wall> wall(new WallObj::Wall(true));
    wall->setPosition(pos);
    wallBreakable.emplace_back(std::move(wall));
}

void Map::PlayerCreate()
{
    std::string selectmode = getFile("../resources/select.txt");
    size_t playernb = selectmode[0] - 48;
    size_t ainb = selectmode[2] - 48;
    nmPlayer = ainb + playernb;

    if (nmPlayer > 4 || nmPlayer < 1)
        throw Errors(std::cerr, "number ai is out of range");
    for (size_t i = 0; i < ainb; ++i) {
        isAi[i] = true;
    }
    for (size_t i = 0; i < nmPlayer; ++i) {
        if (isAi[i] == true) {
            allkeys[i][0] = KEY_RIGHT;
            allkeys[i][1] = KEY_LEFT;
            allkeys[i][2] = KEY_DOWN;
            allkeys[i][3] = KEY_UP;
            allkeys[i][4] = KEY_ENTER;
            AllPlayer.emplace_back(new Player(static_cast<IdPlayer>(i), allposspwan[i], allkeys[0]));
        } else
            AllPlayer.emplace_back(new Player(static_cast<IdPlayer>(i), allposspwan[i], allkeys[i]));
    }
    allui[BLUE_P].loadImage("../resources/player/ui/blue.png");
    allui[GREEN_P].loadImage("../resources/player/ui/green.png");
    allui[YELLOW_P].loadImage("../resources/player/ui/yellow.png");
    allui[RED_P].loadImage("../resources/player/ui/red.png");
    alluiPos[BLUE_P].x = 10;
    alluiPos[BLUE_P].y = 8;
    alluiPos[RED_P].x = 1300;
    alluiPos[RED_P].y = 8;
    alluiPos[YELLOW_P].x = 1300;
    alluiPos[YELLOW_P].y = 540;
    alluiPos[GREEN_P].x = 10;
    alluiPos[GREEN_P].y = 540;
}

static int TimerStringToInt(std::string timerToConvert)
{
    int timer = 0;

    if (timerToConvert.empty())
        return timer;
    timer = std::stoi(timerToConvert.substr(0, 2)) * 60;
    timer += std::stoi(timerToConvert.substr(3, 2));
    return timer;
}

static int DrawWallPassTimer(Player *player, std::string currentTimer)
{
    int begin = 0;
    int current = 0;

    if (player->WallPass) {
        begin = TimerStringToInt(player->wallPassTimer) + 10;
        current = TimerStringToInt(currentTimer);
        if (begin <= current) {
            player->WallPass = false;
            player->wallPassTimer.clear();
        } else {
            return (-1 * (current - begin));
        }
    }
    return -1;
}

void Map::DrawBackground(void)
{
    int timeRemaining;

    drawEvent.drawTextureEx(background.getTexture(), { 0.0f, 0.0f }, 0.0f, 1.0f, WHITE);
    for (size_t i = 0; i < AllPlayer.size(); ++i) {
        auto id = AllPlayer[i].get()->Id;
        drawEvent.drawTextureEx(allui[id].getTexture(), alluiPos[id], 0.0f, 1.0f, WHITE);
        drawEvent.drawText(std::to_string(AllPlayer[i].get()->bombSize), alluiPos[id].x + 220, alluiPos[id].y + 45, 17.5f, WHITE);
        drawEvent.drawText(std::to_string(AllPlayer[i].get()->speed), alluiPos[id].x + 220, alluiPos[id].y + 130, 17.5f, WHITE);
        drawEvent.drawText(std::to_string(AllPlayer[i].get()->MaxBomb), alluiPos[id].x + 220, alluiPos[id].y + 85, 17.5f, WHITE);
        timeRemaining = DrawWallPassTimer(AllPlayer[i].get(), getTimer(2));
        if (timeRemaining == -1)
            drawEvent.drawText("Disable", alluiPos[id].x + 220, alluiPos[id].y + 172, 17.5f, WHITE);
        else
            drawEvent.drawText(std::to_string(timeRemaining).append(" sec"), alluiPos[id].x + 220, alluiPos[id].y + 172, 17.5f, timeRemaining % 2 == 0 ? WHITE : RED);
    }
}

bool Map::isGameOver(void) const
{
    return (death_count == NB_PLAYER - 1);
}

Map::~Map()
{
}
