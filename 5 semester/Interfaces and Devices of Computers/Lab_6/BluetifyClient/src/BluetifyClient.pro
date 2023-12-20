QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += kernel

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../../Common/

LIBS += -lws2_32 -lBthprops

SOURCES += \
    ../../Common/Device.cpp \
    ../../Common/Radio.cpp \
    ../../Common/BluetoothMonitor.cpp \
    BTHClient.cpp \
    main.cpp \
    MainWindow.cpp \

HEADERS += \
    ../../Common/SystemLibs.h \
    ../../Common/Config.h \
    ../../Common/Device.h \
    ../../Common/Radio.h \
    ../../Common/BluetoothMonitor.h \
    BTHClient.h \
    MainWindow.h \

FORMS += \
    MainWindow.ui


win32:RC_FILE = .\..\img\BluetifyClientAppIcon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
