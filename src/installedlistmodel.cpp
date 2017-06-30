#include "installedlistmodel.h"

InstalledListModel::InstalledListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int InstalledListModel::rowCount(const QModelIndex& parent) const
{
    return _screenPlayFiles.count();
}

QVariant InstalledListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < rowCount())
        switch (role) {
        case TitleRole:
            return _screenPlayFiles.at(index.row())._title;
        case PreviewRole:
            return _screenPlayFiles.at(index.row())._preview;
        case FolderIdRole:
            return _screenPlayFiles.at(index.row())._folderId;
        case FileIdRole:
            return _screenPlayFiles.at(index.row())._file;
        default:
            return QVariant();
        }
    return QVariant();
}

QHash<int, QByteArray> InstalledListModel::roleNames() const
{
    static const QHash<int, QByteArray> roles{
        { TitleRole, "screenTitle" },
        { PreviewRole, "screenPreview" },
        { FolderIdRole, "screenFolderId" },
        { FileIdRole, "screenFile" },
    };
    return roles;
}

void InstalledListModel::append(const QJsonObject obj, const QString folderName)
{
    int row = 0;

    beginInsertRows(QModelIndex(), row, row);

    ScreenPlayFile tmpFile(obj, folderName);
    _screenPlayFiles.append(tmpFile);

    endInsertRows();
}

void InstalledListModel::loadScreens()
{
    QJsonDocument jsonProject;
    QJsonParseError parseError;

    QFileInfoList list = QDir(_screensPath).entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);
    QString tmpPath;

    for (auto&& item : list) {
        tmpPath = _screensPath + item.baseName() + "/project.json";
        if (!QFile(tmpPath).exists())
            continue;

        QFile projectConfig;
        projectConfig.setFileName(tmpPath);
        projectConfig.open(QIODevice::ReadOnly | QIODevice::Text);
        QString projectConfigData = projectConfig.readAll();
        jsonProject = QJsonDocument::fromJson(projectConfigData.toUtf8(), &parseError);

        if (!(parseError.error == QJsonParseError::NoError))
            continue;

        append(jsonProject.object(), item.baseName());
    }
}

QVariantMap InstalledListModel::get(QString folderId)
{

    QVariantMap map;
    if (_screenPlayFiles.count() == 0)
        return map;

    for (int i = 0; i < _screenPlayFiles.count(); i++) {

        if (_screenPlayFiles[i]._folderId == folderId) {
            map.insert("screenTitle", _screenPlayFiles[i]._title);
            map.insert("screenPreview", _screenPlayFiles[i]._preview);
            map.insert("screenFile", _screenPlayFiles[i]._file);
        }
    }

    return map;
}

void InstalledListModel::setScreenVisibleFromQml(bool visible)
{
    emit setScreenVisible(visible);
}

void InstalledListModel::setScreenToVideoFromQml(QString absolutePath)
{
    emit setScreenToVideo(absolutePath);
}

ScreenPlayFile::ScreenPlayFile(QJsonObject obj, QString folderName)
{
    if (obj.contains("description"))
        _description = obj.value("description");

    if (obj.contains("file"))
        _file = obj.value("file");

    if (obj.contains("preview"))
        _preview = obj.value("preview");

    if (obj.contains("title"))
        _title = obj.value("title");

    _folderId = folderName;
}
