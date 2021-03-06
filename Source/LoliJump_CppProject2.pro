#-------------------------------------------------
#
# Project created by QtCreator 2014-06-09T11:01:30
#
#-------------------------------------------------

QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoliJump_CppProject2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    hp_bar.cpp \
    character.cpp \
    platform.cpp \
    normal_platform.cpp \
    laser_platform.cpp \
    temporary_platform.cpp \
    left_platform.cpp \
    right_platform.cpp \
    spring_platform.cpp \
    intro.cpp \
    leaderboard.cpp

HEADERS  += mainwindow.h \
    game.h \
    hp_bar.h \
    character.h \
    platform.h \
    normal_platform.h \
    laser_platform.h \
    temporary_platform.h \
    left_platform.h \
    right_platform.h \
    spring_platform.h \
    intro.h \
    leaderboard.h

FORMS    += mainwindow.ui \
    intro.ui \
    leaderboard.ui

RESOURCES += \
    Resourses.qrc

OTHER_FILES += \
    Resources/Background.png \
    Resources/ClearButton.png \
    Resources/Laser_Platform.png \
    Resources/Left.png \
    Resources/Left_Platform.png \
    Resources/lolita.png \
    Resources/Normal_Platform.png \
    Resources/PauseButton.png \
    Resources/Right_Platform.png \
    Resources/Spring_Platform.png \
    Resources/StartButton.png \
    Resources/Temporary_Platform.png \
    Resources/TopLaser.png \
    Resources/lolita/icon.png \
    Resources/Black_HP.png \
    Resources/Red_HP.png \
