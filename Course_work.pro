QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

MOC_DIR = moc
RCC_DIR = rcc
UI_DIR = ui
unix:OBJECTS_DIR = unix
win32:OBJECTS_DIR = win32
macx:OBJECTS_DIR = mac
CONFIG(release, debug|release) {
    win32:QMAKE_POST_LINK = $$(QTDIR)/bin/windeployqt $$OUT_PWD/release
}
SOURCES += \
    addcarwindow.cpp \
    addcustomerwindow.cpp \
    adddealwindow.cpp \
    admin.cpp \
    car.cpp \
    carswindow.cpp \
    customer.cpp \
    customerswindow.cpp \
    deal.cpp \
    dealwindow.cpp \
    forgotpasswordwindow.cpp \
    homeadmin.cpp \
    homemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    managerswindow.cpp \
    paymentwindow.cpp \
    person.cpp \
    signinwindow.cpp \
    signupwindow.cpp \
    sqlitedbmanager.cpp \
    userwindow.cpp

HEADERS += \
    addcarwindow.h \
    addcustomerwindow.h \
    adddealwindow.h \
    admin.h \
    car.h \
    carswindow.h \
    customer.h \
    customerswindow.h \
    dbmanager.h \
    deal.h \
    dealwindow.h \
    forgotpasswordwindow.h \
    homeadmin.h \
    homemanager.h \
    mainwindow.h \
    manager.h \
    managerswindow.h \
    paymentwindow.h \
    person.h \
    signinwindow.h \
    signupwindow.h \
    sqlitedbmanager.h \
    userwindow.h

FORMS += \
    addcarwindow.ui \
    addcustomerwindow.ui \
    adddealwindow.ui \
    carswindow.ui \
    customerswindow.ui \
    dealwindow.ui \
    forgotpasswordwindow.ui \
    homeadmin.ui \
    homemanager.ui \
    mainwindow.ui \
    managerswindow.ui \
    paymentwindow.ui \
    signinwindow.ui \
    signupwindow.ui \
    userwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
