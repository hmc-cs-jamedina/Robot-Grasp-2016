
QT       += core gui opengl

TARGET = 07-core-profile
TEMPLATE = app

SOURCES +=  \
            main.cpp \
            glwidget.cpp \
    objloader.cpp \
   # texture.cpp

HEADERS  += \
            glwidget.h \
    objloader.hpp \
  #  texture.hpp

OTHER_FILES +=  \
                simple.vert \
                simple.frag

#RESOURCES +=    \
 #              core-profile.qrc

unix:!macx: LIBS += -L$$PWD/../../glfw-3.2/build/src/ -lglfw3

INCLUDEPATH += $$PWD/../../glfw-3.2/build/src
DEPENDPATH += $$PWD/../../glfw-3.2/build/src

unix:!macx: PRE_TARGETDEPS += $$PWD/../../glfw-3.2/build/src/libglfw3.a

unix:!macx: LIBS += -lX11 -ldl -lXxf86vm -lGLEW -lXrandr -lXcursor -lXinerama
