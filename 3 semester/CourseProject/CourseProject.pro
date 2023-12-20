QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Account.cpp \
    ActiveMoney.cpp \
    Administrator.cpp \
    BinaryTree.cpp \
    Calculator.cpp \
    ChangeMenu.cpp \
    Exception.cpp \
    Functions.cpp \
    Human.cpp \
    Sign.cpp \
    TransferMoney.cpp \
    main.cpp \
    mainwindow.cpp \
    Money.cpp \
    Service.cpp \
    TxtFile.cpp \
    User.cpp \   

HEADERS += \
    Account.h \
    ActiveMoney.h \
    Administrator.h \
    BinaryTree.h \
    Calculator.h \
    ChangeMenu.h \
    Exception.h \
    Functions.h \
    Human.h \
    Sign.h \
    TransferMoney.h \
    mainwindow.h \
    Money.h \
    Service.h \
    TxtFile.h \
    User.h \

FORMS += \
    Calculator.ui \
    ChangeMenu.ui \
    Sign.ui \
    mainwindow.ui \

win32:RC_FILE = icon_bank_connect.txt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Files/Cash.txt \
    Files/CurrencyExchangeRate.txt \
    Files/Users.txt \

RESOURCES += \
    Pictures.qrc
