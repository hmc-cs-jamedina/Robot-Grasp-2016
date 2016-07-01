
QT       += core gui opengl

TARGET = 07-core-profile
TEMPLATE = app

SOURCES +=  \
            main.cpp \
            glwidget.cpp

HEADERS  += \
            glwidget.h

OTHER_FILES +=  \
                simple.vert \
                simple.frag

RESOURCES +=    \
                core-profile.qrc

unix:!macx|win32: LIBS += -L$$PWD/../../../../../Qt/5.2.1/mingw48_32/lib/ -lglfw3

INCLUDEPATH += $$PWD/../../../../../Qt/5.2.1/mingw48_32/include
DEPENDPATH += $$PWD/../../../../../Qt/5.2.1/mingw48_32/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../Qt/5.2.1/mingw48_32/lib/glfw3.lib
else:unix:!macx|win32-g++: PRE_TARGETDEPS += $$PWD/../../../../../Qt/5.2.1/mingw48_32/lib/libglfw3.a
