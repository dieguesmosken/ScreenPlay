#include "installedlistfilter.h"

InstalledListFilter::InstalledListFilter(InstalledListModel* ilm)
{
    setSourceModel(ilm);
}

void InstalledListFilter::sortByRoleType(QString type)
{
    if (type == "All") {
        setFilterRole(InstalledListModel::InstalledRole::TitleRole);
        setFilterWildcard("*");
    } else if (type == "Wallpaper") {
        setFilterRole(InstalledListModel::InstalledRole::TypeRole);
        setFilterFixedString("video");
    } else if (type == "Widgets") {
        setFilterRole(InstalledListModel::InstalledRole::TypeRole);
        setFilterFixedString("widget");
    }

    sort(0);
}

void InstalledListFilter::sortByName(QString name)
{
    setFilterRole(InstalledListModel::InstalledRole::TitleRole);
    setFilterFixedString(name);
    sort(0);
}

void InstalledListFilter::resetFilter()
{
    setFilterRole(InstalledListModel::InstalledRole::TitleRole);
    setFilterWildcard("*");
    sort(0);
}
