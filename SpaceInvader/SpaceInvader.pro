QT += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

CONFIG += c++17

HEADERS = game.h \
            button.h \
            slidersgroup.h
	
SOURCES += main.cpp \
            game.cpp \
            button.cpp \
            slidersgroup.cpp

QMAKE_PROJECT_NAME = widgets_SpaceInvader

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/SpaceInvader
# INSTALLS += target

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
