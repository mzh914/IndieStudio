SET(ROOT_DIR ${CMAKE_SOURCE_DIR})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

include_directories(${ROOT_DIR}/include/)

ADD_EXECUTABLE(bomberman main.cpp
    error/error.cpp
    game/gamecore.cpp
    game/gameloop.cpp
    game/map.cpp
    game/end.cpp
    menu/menu.cpp
    loadOrNew/loadOrNew.cpp
    loadOrNew/loadGame.cpp
    loadOrNew/newGame.cpp
    loadOrNew/cleanFile.cpp
    menu/help.cpp
    obj/Player.cpp
    obj/Bomb.cpp
    obj/wall.cpp
    obj/card.cpp
    obj/BonusMap.cpp
    pause/pause.cpp
    lib/opoverloading.cpp
    lib/tools.cpp
    encapsulation/music.cpp
    encapsulation/sound.cpp
    encapsulation/texture.cpp
    encapsulation/rectangle.cpp
    encapsulation/model.cpp
    encapsulation/drawing.cpp
    select/selectPlayer.cpp
)

TARGET_LINK_LIBRARIES(bomberman raylib ${CMAKE_DL_LIBS})
