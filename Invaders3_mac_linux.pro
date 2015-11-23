QT -=gui
TARGET=Invaders3_mac_linux
DESTDIR=./
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.c
HEADERS += invader.h

cache()



macx{ ## Libs for mac
    LIBS += -F/Library/Frameworks -framework SDL2
    LIBS += -F/Library/Frameworks -framework SDL2_image
    INCLUDEPATH += /Library/Frameworks/SDL.framework/Headers
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += /usr/local/include/SDL2
    INCLUDEPATH += /Library/Frameworks/SDL2_image.framework/Headers
    QMAKE_LFLAGS += -F/Library/Frameworks
     }

unix:!macx{ ## Libs for unix
    INCLUDEPATH+=/usr/local/include/SDL2
    LIBS+=$$system(sdl2-config  --libs)
    message(output from sdl2-config --libs added to LIB=$$LIBS)
    LIBS+=-lSDL2_image
    QMAKE_CFLAGS+=$$system(sdl2-config  --cflags)
   }

QMAKE_CFLAGS+=-std=c99
message(output from sdl2-config --cflags added to CXXFLAGS= $$QMAKE_CFLAGS)

