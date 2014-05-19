HEADERS += \
    gameengine.h \
    sky.h \
    abstractengineobject.h \
    keymanager.h \
    camera.h \
    checkpoint.h \
    meteorite.h \
    gameminecrisis.h

SOURCES += \
    gameengine.cpp \
    sky.cpp \
    abstractengineobject.cpp \
    main.cpp \
    keymanager.cpp \
    camera.cpp \
    checkpoint.cpp \
    meteorite.cpp \
    gameminecrisis.cpp

LIBS += -lGLU -lglut

QT += opengl

OTHER_FILES += /home/alessandro/Desktop/Unical/Informatica Grafica/QtProgetto/sky.bmp
