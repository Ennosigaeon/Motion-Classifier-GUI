#-------------------------------------------------
#
# Project created by QtCreator 2014-07-02T10:47:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Motion-Classifier-GUI
TEMPLATE = app

CONFIG += debug

SOURCES +=\
    cpp/gui/EMGChannel.cpp \
    cpp/gui/EMGGraph.cpp \
    cpp/gui/MainWindow.cpp \
    cpp/Main.cpp \
    cpp/RealTimeProvider.cpp \
    cpp/gui/ClassifierSettings.cpp \
    cpp/gui/ConfigurationWindow.cpp \
    cpp/gui/PropertiesLayout.cpp \
    cpp/training/Movement.cpp \
    cpp/training/AddTraining.cpp \
    cpp/training/TrainingsController.cpp \
    cpp/training/TrainingsProcedure.cpp \
    cpp/training/TrainingsPainter.cpp

HEADERS  += \
    h/gui/EMGChannel.h \
    h/gui/EMGGraph.h \
    h/gui/MainWindow.h \
    h/RealTimeProvider.h \
    h/gui/ClassifierSettings.h \
    h/gui/ConfigurationWindow.h \
    h/gui/PropertiesLayout.h \
    h/training/Movement.h \
    h/training/AddTraining.h \
    h/training/TrainingsProcedure.h \
    h/training/TrainingsController.h \
    h/training/TrainingsPainter.h

FORMS    += ui/mainwindow.ui


#qwt
win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += C:/Develop/qwt/qwt-6.1.0/build/lib/libqwt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += C:/Develop/qwt/qwt-6.1.0/build/lib/libqwtd.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += C:/Develop/qwt/qwt-6.1.0/build/lib/qwt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += C:/Develop/qwt/qwt-6.1.0/build/lib/qwtd.lib

win32:CONFIG(release, debug|release): LIBS += -LC:/Develop/qwt/qwt-6.1.0/build/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -LC:/Develop/qwt/qwt-6.1.0/build/lib/ -lqwtd

INCLUDEPATH += C:/Develop/qwt/qwt-6.1.0/build/include
DEPENDPATH += C:/Develop/qwt/qwt-6.1.0/build/include


#Motion-Classifier
win32: LIBS += -L$$PWD/../../Motion-Classifier/Debug/ -lMotion-Classifier

INCLUDEPATH += $$PWD/../../Motion-Classifier/Motion-Classifier/h
DEPENDPATH += $$PWD/../../Motion-Classifier/Motion-Classifier/h

#Boost log
win32: LIBS += -LC:/Develop/boost_1_55_0/stage/lib/ -llibboost_log-vc120-mt-gd-1_55

INCLUDEPATH += C:/Develop/boost_1_55_0
DEPENDPATH += C:/Develop/boost_1_55_0

