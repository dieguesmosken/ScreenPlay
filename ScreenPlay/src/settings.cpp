#include "settings.h"

Settings::Settings(ProfileListModel* plm, MonitorListModel* mlm, InstalledListModel* ilm, SDKConnector* sdkc, AppId_t steamID, QObject* parent)
    : QObject(parent)
{

    m_plm = plm;
    m_mlm = mlm;
    m_ilm = ilm;
    m_sdkc = sdkc;
    m_steamID = steamID;

    QFile configTmp;
    QString appConfigLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    m_localSettingsPath = QUrl(appConfigLocation);
    if (!QDir(appConfigLocation).exists()) {
        if (!QDir().mkdir(appConfigLocation)) {
            qWarning("ERROR: Cloud not create install dir");
            return;
        }
    }

    configTmp.setFileName(appConfigLocation + "/settings.json");

    // App Settings
    if (!configTmp.exists()) {
        qWarning("No Settings found, creating default settings");
        createDefaultConfig();
    }

    QJsonDocument configJsonDocument;
    QJsonParseError parseError;
    QJsonObject configObj;

    configTmp.open(QIODevice::ReadOnly | QIODevice::Text);
    QString config = configTmp.readAll();
    configJsonDocument = QJsonDocument::fromJson(config.toUtf8(), &parseError);

    if (!(parseError.error == QJsonParseError::NoError)) {
        qWarning("Settings Json Parse Error ");
        return;
    }

    configObj = configJsonDocument.object();
    QString tmp(configObj.value("version").toVariant().toString());
    int major, minor, patch;
    major = QString(tmp.at(0)).toInt();
    minor = QString(tmp.at(2)).toInt();
    patch = QString(tmp.at(4)).toInt();

    //Checks if the settings file has the same version as ScreeenPlay
    if (!(major == m_version.major && minor == m_version.minor && patch == m_version.patch)) {
        //TODO Display error message
        qWarning("Version missmatch");
        return;
    }

    //If empty use steam workshop location
    if (QString(configObj.value("absoluteStoragePath").toString()).isEmpty()) {
        const uint32 size = 5000;
        char folder[size];
        SteamApps()->GetAppInstallDir(m_steamID, folder, 5000);
        QDir steamTmpUrl = QDir(QString(QByteArray(folder).data()));
        steamTmpUrl.cdUp();
        steamTmpUrl.cdUp();
        steamTmpUrl.cd("workshop");
        steamTmpUrl.cd("content");
        steamTmpUrl.cd("672870");

        m_localStoragePath = steamTmpUrl.path();
    } else {
        m_localStoragePath = configObj.value("absoluteStoragePath").toString();
    }

    m_ilm->setabsoluteStoragePath(m_localStoragePath);
    m_plm->m_localStoragePath = m_localStoragePath;

    m_autostart = configObj.value("autostart").toBool();
    m_highPriorityStart = configObj.value("highPriorityStart").toBool();
    m_sendStatistics = configObj.value("sendStatistics").toBool();
    int renderer = static_cast<int>(configObj.value("renderer-value").toInt());
}

Settings::~Settings()
{
}

void Settings::setWallpaper(int monitorIndex, QUrl absoluteStoragePath)
{

    ProjectFile project;
    Monitor monitor;

    if (!m_mlm->getMonitorListItemAt(monitorIndex, &monitor)) {
        return;
    }

    if (!m_ilm->getProjectByAbsoluteStoragePath(&absoluteStoragePath, &project)) {
        return;
    }

    for (int i = 0; i < m_wallpapers.length(); ++i) {
        if (m_wallpapers.at(i).data()->monitor().m_id == monitor.m_id) {
            m_wallpapers.removeAt(i);
            decreaseActiveWallpaperCounter();
        }
    }
    increaseActiveWallpaperCounter();
    auto pro = new QProcess();
    QStringList proArgs;
    proArgs.append(absoluteStoragePath.toString());

    m_windows.append(pro);
    m_windows.last()->start(m_screenPlayWindowPath.toString());
}

void Settings::setWidget(QUrl absoluteStoragePath)
{
    ProjectFile project;
    if (!m_ilm->getProjectByAbsoluteStoragePath(&absoluteStoragePath, &project)) {
        return;
    }
    QProcess* pro = new QProcess(this);
    m_widgets.append(pro);
    QString fullPath = absoluteStoragePath.toString() + "/" + project.m_file.toString();

    m_widgets.last()->setProgram(fullPath);
    m_widgets.last()->start();
}

QString Settings::loadProject(QString file)
{
    QFile configTmp;
    file = file.replace("file:///", "");
    configTmp.setFileName(file);
    configTmp.open(QIODevice::ReadOnly | QIODevice::Text);
    return configTmp.readAll();
}

void Settings::loadActiveProfiles()
{
    QJsonDocument configJsonDocument;
    QJsonObject configObj;
    QJsonArray activeProfilesTmp;
    QFile configTmp;
    configTmp.setFileName(m_localSettingsPath.toString() + "/settings.json");

    configTmp.open(QIODevice::ReadOnly | QIODevice::Text);
    QString config = configTmp.readAll();
    configJsonDocument = QJsonDocument::fromJson(config.toUtf8());
    configObj = configJsonDocument.object();

    activeProfilesTmp = configObj.value("profiles").toArray();
    int size = activeProfilesTmp.size();

    // Only load profiles if we have any
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            QString profileName = activeProfilesTmp.at(i).toObject().value("profile").toString();
            QString monitorID = activeProfilesTmp.at(i).toObject().value("monitorID").toString();
            Profile profile;
            //            auto spf = new QSharedPointer<ProjectFile>(new ProjectFile());

            //            if (!m_plm->getProfileByName(profileName, &profile))
            //                continue;

            //            if (!m_ilm->getProjectByAbsoluteStoragePath(&profile.m_absolutePath, spf))
            //                continue;

            //            constructWallpaper(profile, monitorID, spf);
        }
    }
}

void Settings::destroyWallpaper(QObject* ref)
{
    for (int i = 0; i < m_wallpapers.count(); ++i) {
        if (m_wallpapers.at(i) == ref) {
            m_wallpapers.at(i).data()->deleteLater();
            //m_wallpapers.remove(i);
            return;
        }
    }
}

void Settings::setGlobalVolume(float volume)
{
    for (int i = 0; i < m_wallpapers.size(); ++i) {
        m_wallpapers.at(i).data()->setVolume(volume);
    }
}

void Settings::setGlobalFillMode(QString fillMode)
{
    for (int i = 0; i < m_wallpapers.size(); ++i) {
        m_wallpapers.at(i).data()->setFillMode(fillMode);
    }
}

void Settings::writeSingleSettingConfig(QString name, QVariant value)
{

    QJsonDocument configJsonDocument;
    QJsonParseError parseError;
    QJsonObject configObj;
    QFile configTmp;

    configTmp.setFileName(m_localSettingsPath.toString() + "/settings.json");
    configTmp.open(QIODevice::ReadOnly | QIODevice::Text);
    QString config = configTmp.readAll();
    configJsonDocument = QJsonDocument::fromJson(config.toUtf8(), &parseError);

    if (!(parseError.error == QJsonParseError::NoError)) {
        qWarning("Settings Json Parse Error ");
        return;
    }
    configObj = configJsonDocument.object();
    configObj.insert(name, value.toJsonValue());

    configTmp.close();
    // Reopen to empty the file via Truncate
    configTmp.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream out(&configTmp);
    out << QJsonDocument(configObj).toJson();

    configTmp.close();
}

void Settings::removeAll()
{
    for (int i = 0; i < m_wallpapers.size(); ++i) {
        m_wallpapers.at(i).data()->destroyWallpaper();
    }
    for (int i = 0; i < m_windows.size(); ++i) {

    }
    setActiveWallpaperCounter(0);
}

void Settings::setMuteAll(bool isMuted)
{

    if (isMuted) {
        for (int i = 0; i < m_wallpapers.size(); ++i) {
            m_wallpapers.at(i).data()->setVolume(0.0f);
        }
    } else {
        for (int i = 0; i < m_wallpapers.size(); ++i) {
            m_wallpapers.at(i).data()->setVolume(1.0f);
        }
    }
}

void Settings::setPlayAll(bool isPlaying)
{
    if (isPlaying) {
        for (int i = 0; i < m_wallpapers.size(); ++i) {
            m_wallpapers.at(i).data()->setIsPlaying(true);
        }
    } else {
        for (int i = 0; i < m_wallpapers.size(); ++i) {
            m_wallpapers.at(i).data()->setIsPlaying(false);
        }
    }
}

QUrl Settings::getPreviewImageByMonitorID(QString id)
{
    //    for (int i = 0; i < m_mlm->m_monitorList.size(); ++i) {
    //        if(m_mlm->m_monitorList.at(i).m_id == id){
    //            //return m_mlm->m_monitorList.at(i).m_
    //        }
    //    }
    return QUrl();
}

QString Settings::fixWindowsPath(QString url)
{
    return url.replace("/", "\\\\");
}

void Settings::removeWallpaperAt(int pos)
{
    if (pos > 0 && pos > m_wallpapers.size())
        m_wallpapers.removeAt(pos);
}

void Settings::createDefaultConfig()
{

    QFile file(QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation) + "/settings.json");
    QFile defaultSettings(":/settings.json");

    file.open(QIODevice::WriteOnly | QIODevice::Text);
    defaultSettings.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream out(&file);
    QTextStream defaultOut(&defaultSettings);

    out << defaultOut.readAll();

    file.close();
    defaultSettings.close();
}

QUrl Settings::getScreenPlayWindowPath() const
{
    return m_screenPlayWindowPath;
}

void Settings::setScreenPlayWindowPath(const QUrl& screenPlayWindowPath)
{
    m_screenPlayWindowPath = screenPlayWindowPath;
}

ActiveProfiles::ActiveProfiles()
{
}

ActiveProfiles::ActiveProfiles(QString wallpaperId, Profile profile)
{
    m_monitorId = wallpaperId;
    m_profile = profile;
}

QString ActiveProfiles::monitorId() const
{
    return m_monitorId;
}