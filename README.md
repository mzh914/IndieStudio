<h1 align="center">
    Indie Studio
    <div>
        <a><img src="https://github.com/EpitechPromo2025/B-YEP-400-PAR-4-1-indiestudio-wassini.bouzidi/blob/master/resources/player/icons/blue.png"
       title="Bomberman" alt="Bomberman"></a>
    </div>
    Bomberman
</h1>

![Cpp](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![raylib](https://img.shields.io/badge/Raylib-black?style=for-the-badge&logo=GNU&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)

> The goal of Indie Studio is to implement a cross-platform 3D video game with real-world tools.
> The game implemented is a Bomberman referencing the [Neo Bomberman](https://fr.wikipedia.org/wiki/Neo_Bomberman).

You can play in multiplayer or against AI using keyboard

We used the [raylib](https://www.raylib.com/) (C graphical library) encapsuled to create our own game engine in C++.

## Requirements

### You must have Cmake >= 3.17 to compile the project

If you don't have it, please install. [Download Cmake (Windows, Linux, MacOS)](https://cmake.org/download/)

## Build project and run it

Linux :

From root project

```sh
./compile.sh
```

Windows :

```sh
./compile.bat
```

or
Double click on compile.bat file

## Documentation

### All scenes are inherited from IScene

```cpp
class IScene {
public:
    virtual ~IScene() = default;
    virtual void Loop(SceneProcess &scene) = 0;
    virtual void draw() = 0;

protected:
private:
};
```

### Following class's are used to encapsulate raylib

- DrawingProcess (./include/Drawing.hpp)
- ModelClass (./include/Model.hpp)
- SceneMusic (./include/music.hpp)
- RectangleClass (./include/Rectangle.hpp)
- SceneSound (./include/sound.hpp)
- ImgTexture (./include/Texture.hpp)

### Change scene using an enum

```cpp
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

SceneProcess CurrentScene;
```

CurrentScene is using to change the _unique_ptr_ the _gamecore.current_ is pointing.
It enable the program to create scene when you're using it and free when scene changed.

### Database

To save and load game we use a simple text file located in build/save.txt

## Authors

- [Wassini Bouzidi](https://github.com/wassb92) - wassini.bouzidi@epitech.eu (Team leader)
- [Tao Weijie](https://github.com/taovc) - tao.weijie@epitech.eu
- Brice Bougha - brice.bougha@epitech.eu
- Julien De-Waele - julien.de-waele@epitech.eu
- Manuela Moussango - manuela.moussango-@epitech.eu
- Marc Zhou - marc.zhou@epitech.eu
