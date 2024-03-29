QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    form.cpp \
    harta.cpp \
    intermediaryscreen.cpp \
    intrebarigrila.cpp \
    intrebarinumerice.cpp \
    main.cpp \
    mainscreen.cpp \
    startscreen.cpp

HEADERS += \
    form.h \
    harta.h \
    intermediaryscreen.h \
    intrebarigrila.h \
    intrebarinumerice.h \
    mainscreen.h \
    startscreen.h

FORMS += \
    form.ui \
    harta.ui \
    intermediaryscreen.ui \
    intrebarigrila.ui \
    intrebarinumerice.ui \
    mainscreen.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
