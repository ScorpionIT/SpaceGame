HEADERS += \
    gameengine.h \
    sky.h \
    keymanager.h \
    camera.h \
    checkpoint.h \
    player.h \
    engineobject.h \
    glm/glm.h \
    modelloader.h

SOURCES += \
    gameengine.cpp \
    sky.cpp \
    main.cpp \
    keymanager.cpp \
    camera.cpp \
    checkpoint.cpp \
    player.cpp \
    engineobject.cpp \
    modelloader.cpp

LIBS += -L./glm -lGLU -lglut -lglm

QT += opengl

