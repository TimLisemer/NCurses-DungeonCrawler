TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/share/licenses/ncurses
LIBS += -L/usr/share/licenses/ncurses -lncurses

SOURCES += \
        character.cpp \
        dungeoncrawler.cpp \
        level.cpp \
        logger.cpp \
        main.cpp \
        node.cpp \
        tile.cpp \
        item.cpp \
        userinterface.cpp

HEADERS += \
    character.h \
    dungeoncrawler.h \
    level.h \
    logger.h \
    node.h \
    tile.h \
    item.h \
    userinterface.h
