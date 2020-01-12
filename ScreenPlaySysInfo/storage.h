#pragma once

#include <QAbstractListModel>
#include <QObject>
#include <QStorageInfo>
#include <QTimer>
#include <QVector>

class Storage : public QAbstractListModel {
    Q_OBJECT
public:
    explicit Storage(QObject* parent = nullptr);

    enum class StorageRole {
        BytesAvailable = Qt::UserRole,
        BytesFree,
        BytesTotal,
        DisplayName,
        FileSystemType,
        IsReadOnly,
        IsReady,
        IsRoot,
        IsValid,
        Name,
    };
    Q_ENUM(StorageRole)

    QHash<int, QByteArray> roleNames() const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;


public slots:
    void refresh();
    void reset();
signals:

private:
    void loadStorageDevices();
private:
    QVector<QStorageInfo> m_storageInfoList;
};
