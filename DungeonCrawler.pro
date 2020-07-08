TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/share/licenses/ncurses
LIBS += -L/usr/share/licenses/ncurses -lncurses

SOURCES += \
        active.cpp \
        armor.cpp \
        attackcontroller.cpp \
        character.cpp \
        consolecontroller.cpp \
        consumable.cpp \
        controller.cpp \
        door.cpp \
        dungeoncrawler.cpp \
        elixir.cpp \
        floor.cpp \
        guardcontroller.cpp \
        item.cpp \
        level.cpp \
        lever.cpp \
        list.cpp \
        logger.cpp \
        main.cpp \
        node.cpp \
        passive.cpp \
        portal.cpp \
        potion.cpp \
        stationarycontroller.cpp \
        switch.cpp \
        tile.cpp \
        trap.cpp \
        userinterface.cpp \
        wall.cpp \
        weapon.cpp

HEADERS += \
    active.h \
    armor.h \
    attackcontroller.h \
    character.h \
    consolecontroller.h \
    consumable.h \
    controller.h \
    door.h \
    dungeoncrawler.h \
    elixir.h \
    floor.h \
    guardcontroller.h \
    item.h \
    level.h \
    lever.h \
    list.h \
    logger.h \
    loglevel.h \
    node.h \
    passive.h \
    portal.h \
    potion.h \
    stationarycontroller.h \
    switch.h \
    tile.h \
    trap.h \
    userinterface.h \
    wall.h \
    weapon.h
