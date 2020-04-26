#pragma once

#include <QAbstractListModel>
#include <QApplication>
#include <QDebug>
#include <QApplication>
#include <QRect>
#include <QScreen>
#include <QSize>
#include <QString>
#include <QVector>

#include "projectsettingslistmodel.h"
#include "screenplaywallpaper.h"
#include "screenplaywidget.h"

#ifdef Q_OS_WIN
#include <qt_windows.h>
#endif
#include <memory>
#include <optional>

namespace ScreenPlay {

struct Monitor {

    Monitor(
        const int number,
        const QRect& availableGeometry,
        QScreen* screen)
    {
        m_number = number;
        m_availableGeometry = availableGeometry;
        m_screen = screen;
    }

    QRect m_availableGeometry;
    int m_number { 0 };
    QScreen* m_screen { nullptr };
    std::shared_ptr<ScreenPlayWallpaper> m_activeWallpaper { nullptr };
};

class MonitorListModel : public QAbstractListModel {
    Q_OBJECT

public:
    explicit MonitorListModel(QObject* parent = nullptr);

    ~MonitorListModel() override
    {
        m_monitorList.clear();
    }

    enum class MonitorRole {
        AppID = Qt::UserRole,
        MonitorID,
        Name,
        Size,
        AvailableGeometry,
        AvailableVirtualGeometry,
        Number,
        Geometry,
        Model,
        Manufacturer,
        PreviewImage,
    };
    Q_ENUM(MonitorRole)

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    void setWallpaperActiveMonitor(const std::shared_ptr<ScreenPlayWallpaper>& wallpaper,
        const QVector<int> monitors);

    std::optional<QString> getAppIDByMonitorIndex(const int index) const;

signals:
    void monitorReloadCompleted();
    void setNewActiveMonitor(int index, QString path);
    void monitorConfigurationChanged();

public slots:
    void reset();
    void clearActiveWallpaper();
    void closeWallpaper(const QString& appID);

    void screenAdded(QScreen* screen)
    {
        qDebug() << "screenAdded" << screen->geometry() << m_monitorList.size();
        emit monitorConfigurationChanged();
        reset();
    }
    void screenRemoved(QScreen* screen)
    {
        qDebug() << "screenRemoved" << screen->geometry() << m_monitorList.size();
        emit monitorConfigurationChanged();
        reset();
    }

    QRect getAbsoluteDesktopSize() const
    {
        auto* app = static_cast<QApplication*>(QApplication::instance());
        return app->screens().at(0)->availableVirtualGeometry();
    }

private:
    void loadMonitors();

private:
    QVector<Monitor> m_monitorList;
    QVector<QSharedPointer<ProjectSettingsListModel>> m_plm;
};

}
