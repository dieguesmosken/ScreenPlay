#include "basewindow.h"

BaseWindow::BaseWindow(QObject* parent)
    : QObject(parent)
{
}

BaseWindow::BaseWindow(QString projectFilePath, const QVector<int> activeScreensList, const bool checkWallpaperVisible)
    : QObject(nullptr)
    , m_checkWallpaperVisible(checkWallpaperVisible)
    , m_activeScreensList(activeScreensList)
{
    QApplication::instance()->installEventFilter(this);
    qRegisterMetaType<BaseWindow::WallpaperType>();
    qmlRegisterType<BaseWindow>("ScreenPlay.Wallpaper", 1, 0, "Wallpaper");

    setOSVersion(QSysInfo::productVersion());

    if (projectFilePath == "test") {
        setType(BaseWindow::WallpaperType::Qml);
        setFullContentPath("qrc:/test.qml");
        return;
    }

    QFile projectFile;
    QJsonDocument configJsonDocument;
    QJsonParseError parseError;

    if (projectFilePath.contains("file:\\\\\\"))
        projectFilePath = projectFilePath.remove("file:\\\\\\");

    projectFile.setFileName(projectFilePath + "/project.json");
    projectFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString projectConfig = projectFile.readAll();
    configJsonDocument = QJsonDocument::fromJson(projectConfig.toUtf8(), &parseError);

    /* project.json example:
    *{
    *    "title": "example title",
    *    "description": "",
    *    "file": "example.webm",
    *    "preview": "preview.png",
    *    "previewGIF": "preview.gif",
    *    "previewWEBM": "preview.webm",
    *    "type": "videoWallpaper"
    *}
    */

    if (!(parseError.error == QJsonParseError::NoError)) {
        qDebug() << projectConfig << "\n"
                 << parseError.errorString();
        qFatal("Settings Json Parse Error. Exiting now!");
    }

    QJsonObject projectObject = configJsonDocument.object();

    if (!projectObject.contains("file")) {
        qFatal("No file was specified inside the json object!");
    }

    if (!projectObject.contains("type")) {
        qFatal("No type was specified inside the json object!");
    }

    setBasePath(projectFilePath);
    setFullContentPath("file:///" + projectFilePath + "/" + projectObject.value("file").toString());

    QObject::connect(&m_fileSystemWatcher, &QFileSystemWatcher::directoryChanged, this, &BaseWindow::reloadQML);
    QObject::connect(&m_fileSystemWatcher, &QFileSystemWatcher::fileChanged, this, &BaseWindow::reloadQML);
    m_fileSystemWatcher.addPaths({ projectFilePath, projectFilePath + "/" + projectObject.value("file").toString() });

    if (projectObject.value("type") == "videoWallpaper") {
        setType(BaseWindow::WallpaperType::Video);
        return;
    }

    if (projectObject.value("type") == "threeJSWallpaper") {
        setType(BaseWindow::WallpaperType::ThreeJSScene);
        return;
    }

    if (projectObject.value("type") == "qmlWallpaper") {
        setType(BaseWindow::WallpaperType::Qml);
        return;
    }

    if (projectObject.value("type") == "htmlWallpaper") {
        setType(BaseWindow::WallpaperType::Html);
        return;
    }
}

void BaseWindow::messageReceived(QString key, QString value)
{
    if (key == "volume") {
        bool ok;
        float tmp = value.toFloat(&ok);
        if (ok) {
            setVolume(tmp);
        }
        return;
    }

    if (key == "playbackRate") {
        bool ok;
        float tmp = value.toFloat(&ok);
        if (ok) {
            setPlaybackRate(tmp);
        }
        return;
    }

    if (key == "loops") {
        bool tmp = QVariant(value).toBool();
        setLoops(tmp);
        return;
    }

    if (key == "isPlaying") {
        bool tmp = QVariant(value).toBool();
        setIsPlaying(tmp);
        return;
    }

    if (key == "muted") {
        bool tmp = QVariant(value).toBool();
        setMuted(tmp);
        return;
    }

    if (key == "fillmode") {
        // HTML5 Video uses - that c++ enums cannot
        if(QVariant(value).toString() == "Scale_Down"){
            setFillMode("Scale-Down");
        } else {
            setFillMode(QVariant(value).toString());
        }
        return;
    }

    if (key == "currentTime") {
        bool ok;
        float tmp = value.toFloat(&ok);
        if (ok) {
            setCurrentTime(tmp);
        }
        return;
    }

    emit qmlSceneValueReceived(key, value);
}

QString BaseWindow::loadFromFile(const QString& filename)
{
    QFile file;
    file.setFileName(basePath() + "/" + filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return file.readAll();
    }
    return "";
}
