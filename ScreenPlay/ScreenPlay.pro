TEMPLATE = app
QT += qml quick widgets quickcontrols2 core
CONFIG += c++17
#CONFIG += qtquickcompiler
#DEFINES  += QT_NO_DEBUG_OUTPUT QT_NO_WARNING_OUTPUT
msvc: LIBS += -luser32
TARGETPATH = ScreenPlay

ICON = favicon.ico

SOURCES += main.cpp \
    src/steamworkshop.cpp \
    src/installedlistmodel.cpp \
    src/monitorlistmodel.cpp \
    src/settings.cpp \
    src/profilelistmodel.cpp \
    src/profile.cpp \
    src/projectfile.cpp \
    src/steamworkshoplistmodel.cpp \
    src/workshopitem.cpp \
    src/installedlistfilter.cpp \
    src/sdkconnector.cpp \
    src/projectsettingslistitem.cpp \
    src/projectsettingslistmodel.cpp \
    src/startuperror.cpp \
    src/screenplay.cpp \
    src/qmlutilities.cpp \
    src/create.cpp

RESOURCES += Resources.qrc

TRANSLATIONS =  translations/ScreenPlay_en.ts   \
                translations/ScreenPlay_de.ts

HEADERS += \
    src/steamworkshop.h \
    src/installedlistmodel.h \
    src/monitorlistmodel.h \
    src/settings.h \
    src/profilelistmodel.h \
    src/profile.h \
    src/projectfile.h \
    src/steamworkshoplistmodel.h \
    src/workshopitem.h \
    src/installedlistfilter.h \
    src/sdkconnector.h \
    src/projectsettingslistitem.h \
    src/projectsettingslistmodel.h \
    src/startuperror.h \
    src/screenplay.h \
    src/qmlutilities.h \
    src/create.h

INCLUDEPATH += \
    $$PWD/ThirdParty/ \
    $$PWD/src/


CONFIG(debug, debug|release) {
    install_it.path = $${OUT_PWD}/debug/
 } else {
    install_it.path = $${OUT_PWD}/release/
 }
installOut.path =  $${OUT_PWD}/

install_it.files += assets/templates/config.json \
                    assets/icons/favicon.ico \
                    settings.json \
                    steam_appid.txt \

installOut.files += steam_appid.txt \

INSTALLS += install_it
INSTALLS += installOut

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
# QML_DESIGNER_IMPORT_PATH =
QT_QUICK_CONTROLS_STYLE = "Material"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

debug {
  DEFINES += SP_DEBUG
}
release {
  DEFINES += SP_RELEASE
}

win32 {
    win32: LIBS += -L$$PWD/ThirdParty/Steam/redistributable_bin/win64/ -lsteam_api64
    DEPENDPATH += $$PWD/ThirdParty/Steam/redistributable_bin/win64
}

unix {
    LIBS += -L$$PWD/ThirdParty/steam/redistributable_bin/linux64/ -lsteam_api
    DEPENDPATH += $$PWD/ThirdParty/steam/redistributable_bin/linux64

    INCLUDEPATH += $$PWD/ThirdParty/steam/lib/linux64
    DEPENDPATH += $$PWD/ThirdParty/steam/lib/linux64s

    LIBS += -L$$PWD/ThirdParty/steam/lib/linux64/ -lsdkencryptedappticket
}
