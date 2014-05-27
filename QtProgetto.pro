HEADERS += \
    gameengine.h \
    sky.h \
    camera.h \
    checkpoint.h \
    player.h \
    engineobject.h \
    gameminecrisis.h \
    meteorite.h \
    opengl.h \
    earth.h \
    obstacle.h \
    model.h


SOURCES += \
    gameengine.cpp \
    sky.cpp \
    main.cpp \
    checkpoint.cpp \
    player.cpp \
    engineobject.cpp \
    gameminecrisis.cpp \
    meteorite.cpp \
    camera.cpp \
    earth.cpp \
    obstacle.cpp \
    model.cpp

LIBS += -L"./libObj/lib" -lobj -lGLU -lglut

QT += opengl

OTHER_FILES +=

