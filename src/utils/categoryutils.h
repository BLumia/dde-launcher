#pragma once

#include <QList>

namespace CategoryUtils {

enum class Categorytype {
    CategoryInternet,
    CategoryChat,
    CategoryMusic,
    CategoryVideo,
    CategoryGraphics,
    CategoryGame,
    CategoryOffice,
    CategoryReading,
    CategoryDevelopment,
    CategorySystem,
    CategoryOthers,
    CategoryErr,
};

Categorytype parseBestMatchedCategory(QStringList categories);
Categorytype parseDDECategoryString(QString str);
QList<Categorytype> parseXdgCategoryString(QString str);

}
