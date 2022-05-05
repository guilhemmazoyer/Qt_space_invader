QT += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

HEADERS = game.h \
			button.h
	
SOURCES += main.cpp \
			button.cpp \
			game.cpp

QMAKE_PROJECT_NAME = widgets_SpaceInvader

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/SpaceInvader
# INSTALLS += target

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
