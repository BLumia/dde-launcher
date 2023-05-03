#pragma once

#include <QPixmap>

namespace IconUtils {
    bool getThemeIcon(QPixmap &pixmap, const QString & iconName, const QString & entryPath, const int size);
    int perfectIconSize(const int size);
    bool createCalendarIcon(const QString &fileName);
    const QPixmap loadSvg(const QString &fileName, int size);
    const QPixmap loadSvg(const QString &fileName, const QSize &size);
}
