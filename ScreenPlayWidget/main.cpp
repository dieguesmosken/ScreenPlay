#include <QApplication>
#include <QQmlApplicationEngine>
#include <QStringList>

#include "../ScreenPlaySDK/screenplaysdk.h"
#include "src/widgetwindow.h"

int main(int argc, char* argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_ShareOpenGLContexts);

    QApplication app(argc, argv);

    QStringList argumentList = app.arguments();

    // If we start with only one argument (path, appID, type),
    // it means we want to test a single widget
    if (argumentList.length() == 1) {
        WidgetWindow spwmw("test", "appid", "qmlWidget");
        return app.exec();
    }

    if (argumentList.length() != 4) {
        return -3;
    }

    ScreenPlaySDK sdk(argumentList.at(2), argumentList.at(3));
    // 1. Project path, 2. AppID, 3. Type
    WidgetWindow spwmw(argumentList.at(1), argumentList.at(2), argumentList.at(3));

    QObject::connect(&sdk, &ScreenPlaySDK::sdkDisconnected, &spwmw, &WidgetWindow::qmlExit);
    QObject::connect(&sdk, &ScreenPlaySDK::incommingMessage, &spwmw, &WidgetWindow::messageReceived);

    return app.exec();
}
