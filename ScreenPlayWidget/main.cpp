#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringList>

#include "src/widgetwindow.h"
#include "../ScreenPlaySDK/screenplaysdk.h"

int main(int argc, char* argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    ScreenPlaySDK sdk;
    QGuiApplication app(argc, argv);

    QStringList argumentList = app.arguments();

    // If we start with only one argument (app, path, type),
    // it means we want to test a single widget
    if (argumentList.length() == 1) {
        WidgetWindow spwmw("test","appid", "qmlWidget");
        return app.exec();
    }

    if (argumentList.length() != 4) {
        return -3;
    }

    WidgetWindow spwmw(argumentList.at(1), argumentList.at(2), argumentList.at(3));

    QObject::connect(&sdk, &ScreenPlaySDK::sdkDisconnected, &spwmw, &WidgetWindow::destroyThis);
    QObject::connect(&sdk, &ScreenPlaySDK::incommingMessage, &spwmw, &WidgetWindow::messageReceived);

    return app.exec();
}
