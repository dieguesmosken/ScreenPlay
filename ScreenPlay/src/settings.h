#pragma once

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QGuiApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QPair>
#include <QProcess>
#include <QProcessEnvironment>
#include <QQmlPropertyMap>
#include <QSettings>
#include <QSharedPointer>
#include <QStandardPaths>
#include <QString>
#include <QTextStream>
#include <QThread>
#include <QUrl>
#include <QVariant>
#include <QVector>
#include <QVersionNumber>
#include <QtConcurrent/QtConcurrent>
#include <QtGlobal>

#include "installedlistmodel.h"
#include "monitorlistmodel.h"
#include "profile.h"
#include "profilelistmodel.h"
#include "projectsettingslistmodel.h"
#include "sdkconnector.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#endif

/*!
    \class Settings
    \brief Used for:
    \list
        \i User configuration
        \i Communication via the SDK Connector
    \endlist

*/

class ActiveProfile;

class Settings : public QObject {
    Q_OBJECT

    Q_PROPERTY(QVersionNumber version READ version)
    Q_PROPERTY(bool hasWorkshopBannerSeen READ hasWorkshopBannerSeen WRITE setHasWorkshopBannerSeen NOTIFY hasWorkshopBannerSeenChanged)
    Q_PROPERTY(bool autostart READ autostart WRITE setAutostart NOTIFY autostartChanged)
    Q_PROPERTY(bool highPriorityStart READ highPriorityStart WRITE setHighPriorityStart NOTIFY highPriorityStartChanged)
    Q_PROPERTY(bool sendStatistics READ sendStatistics WRITE setSendStatistics NOTIFY sendStatisticsChanged)
    Q_PROPERTY(bool pauseWallpaperWhenIngame READ pauseWallpaperWhenIngame WRITE setPauseWallpaperWhenIngame NOTIFY pauseWallpaperWhenIngameChanged)
    Q_PROPERTY(bool offlineMode READ offlineMode WRITE setOfflineMode NOTIFY offlineModeChanged)
    Q_PROPERTY(QUrl localStoragePath READ localStoragePath WRITE setLocalStoragePath NOTIFY localStoragePathChanged)
    Q_PROPERTY(QString decoder READ decoder WRITE setDecoder NOTIFY decoderChanged)
    Q_PROPERTY(int activeWallpaperCounter READ activeWallpaperCounter WRITE setActiveWallpaperCounter NOTIFY activeWallpaperCounterChanged)

public:
    explicit Settings(ProfileListModel* plm, MonitorListModel* mlm, InstalledListModel* ilm, SDKConnector* sdkc, QObject* parent = nullptr);
    ~Settings();

    enum LocalCopyResult {
        NoError,
        CopyError,
        NotEnoughDiskSpace,
        NameCollision,
    };
    Q_ENUM(LocalCopyResult)

    QVersionNumber version() const
    {
        return m_version;
    }

    QUrl screenPlayWindowPath() const
    {
        return m_screenPlayWindowPath;
    }

    QUrl localStoragePath() const
    {
        return m_localStoragePath;
    }

    bool hasWorkshopBannerSeen() const
    {
        return m_hasWorkshopBannerSeen;
    }

    int activeWallpaperCounter() const
    {
        return m_activeWallpaperCounter;
    }

    bool pauseWallpaperWhenIngame() const
    {
        return m_pauseWallpaperWhenIngame;
    }

    bool offlineMode() const
    {
        return m_offlineMode;
    }

    QUrl getScreenPlayWindowPath() const;
    void setScreenPlayWindowPath(const QUrl& screenPlayWindowPath);

    QUrl getScreenPlayBasePath() const;
    void setScreenPlayBasePath(QUrl screenPlayBasePath);

    QUrl getScreenPlayWidgetPath() const;
    void setScreenPlayWidgetPath(const QUrl& screenPlayWidgetPath);

    bool getOfflineMode() const;
    void loadActiveProfiles();

signals:
    void autostartChanged(bool autostart);
    void highPriorityStartChanged(bool highPriorityStart);
    void sendStatisticsChanged(bool status);
    void localStoragePathChanged(QUrl localStoragePath);
    void hasWorkshopBannerSeenChanged(bool hasWorkshopBannerSeen);
    void decoderChanged(QString decoder);
    void setMainWindowVisible(bool visible);
    void activeWallpaperCounterChanged(int activeWallpaperCounter);
    void pauseWallpaperWhenIngameChanged(bool pauseWallpaperWhenIngame);
    void offlineModeChanged(bool offlineMode);
    void allLicenseLoaded(QString licensesText);
    void allDataProtectionLoaded(QString dataProtectionText);

public slots:
    void setMuteAll(bool isMuted);
    void setPlayAll(bool isPlaying);
    void checkForOtherFullscreenApplication();
    void setGlobalVolume(float volume);
    void setGlobalFillMode(QString fillMode);
    void writeSingleSettingConfig(QString name, QVariant value);
    void requestAllLicenses();
    void requestAllLDataProtection();
    void saveWallpaper(int monitorIndex, QUrl absoluteStoragePath, QStringList properties, QString type);
    void setqSetting(const QString& key, const QString& value);

    bool autostart() const
    {
        return m_autostart;
    }

    bool highPriorityStart() const
    {
        return m_highPriorityStart;
    }

    bool sendStatistics() const
    {
        return m_sendStatistics;
    }

    QString decoder() const
    {
        return m_decoder;
    }

    void setAutostart(bool autostart)
    {
        if (m_autostart == autostart)
            return;

        if (autostart) {
#ifdef Q_OS_WIN

            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.setValue("ScreenPlay", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()) + " -silent");
            settings.sync();
#endif
        } else {
#ifdef Q_OS_WIN
            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.remove("ScreenPlay");
#endif
        }

        m_autostart = autostart;
        writeSingleSettingConfig("autostart", autostart);
        emit autostartChanged(m_autostart);
    }

    void setHighPriorityStart(bool highPriorityStart)
    {
        if (m_highPriorityStart == highPriorityStart)
            return;

        m_highPriorityStart = highPriorityStart;
        writeSingleSettingConfig("highPriorityStart", highPriorityStart);
        emit highPriorityStartChanged(m_highPriorityStart);
    }

    void setSendStatistics(bool sendStatistics)
    {
        if (m_sendStatistics == sendStatistics)
            return;

        m_sendStatistics = sendStatistics;

        writeSingleSettingConfig("sendStatistics", sendStatistics);
        emit sendStatisticsChanged(m_sendStatistics);
    }

    QString loadProject(QString file);

    void setLocalStoragePath(QUrl localStoragePath)
    {
        if (m_localStoragePath == localStoragePath)
            return;

        //Remove: "file:///"
        QJsonValue cleanedPath = QJsonValue(localStoragePath.toString()); // QJsonValue(QString(localStoragePath.toString()).remove(0, 8));

        writeSingleSettingConfig("absoluteStoragePath", cleanedPath);

        m_ilm->setabsoluteStoragePath(cleanedPath.toString());
        m_localStoragePath = cleanedPath.toString();
        emit localStoragePathChanged(cleanedPath.toString());
        m_ilm->reset();
        m_ilm->loadInstalledContent();
    }

    void setDecoder(QString decoder)
    {
        if (m_decoder == decoder)
            return;

        m_decoder = decoder;

        emit decoderChanged(m_decoder);
    }

    void setHasWorkshopBannerSeen(bool hasWorkshopBannerSeen)
    {
        if (m_hasWorkshopBannerSeen == hasWorkshopBannerSeen)
            return;

        m_hasWorkshopBannerSeen = hasWorkshopBannerSeen;
        emit hasWorkshopBannerSeenChanged(m_hasWorkshopBannerSeen);
    }

    void setActiveWallpaperCounter(int activeWallpaperCounter)
    {
        if (m_activeWallpaperCounter == activeWallpaperCounter)
            return;

        m_activeWallpaperCounter = activeWallpaperCounter;
        emit activeWallpaperCounterChanged(m_activeWallpaperCounter);
    }

    void increaseActiveWallpaperCounter()
    {
        m_activeWallpaperCounter++;
        emit activeWallpaperCounterChanged(m_activeWallpaperCounter);
    }

    void decreaseActiveWallpaperCounter()
    {
        if (m_activeWallpaperCounter <= 0) {
            return;
        }
        m_activeWallpaperCounter--;
        emit activeWallpaperCounterChanged(m_activeWallpaperCounter);
    }

    void setPauseWallpaperWhenIngame(bool pauseWallpaperWhenIngame)
    {
        if (m_pauseWallpaperWhenIngame == pauseWallpaperWhenIngame)
            return;

        m_pauseWallpaperWhenIngame = pauseWallpaperWhenIngame;
        emit pauseWallpaperWhenIngameChanged(m_pauseWallpaperWhenIngame);
    }

    void setOfflineMode(bool offlineMode)
    {
        if (m_offlineMode == offlineMode)
            return;

        m_offlineMode = offlineMode;
        emit offlineModeChanged(m_offlineMode);
    }

private:
    void createDefaultConfig();
    void setupWidgetAndWindowPaths();

    QVersionNumber m_version;
    QSettings m_qSettings;
    QTranslator m_translator;
    ProfileListModel* m_plm;
    InstalledListModel* m_ilm;
    MonitorListModel* m_mlm;
    SDKConnector* m_sdkc;

    QTimer* m_checkForOtherFullscreenApplicationTimer;

    QUrl m_localStoragePath;
    QUrl m_localSettingsPath;
    QUrl m_screenPlayWindowPath;
    QUrl m_screenPlayWidgetPath;
    QUrl m_screenPlayBasePath;

    bool m_hasWorkshopBannerSeen = false;
    bool m_pauseWallpaperWhenIngame = true;
    bool m_autostart = true;
    bool m_highPriorityStart = true;
    bool m_sendStatistics;

    QString m_decoder;
    int m_activeWallpaperCounter = 0;
    QGuiApplication* m_app;

    bool m_offlineMode = true;
};
