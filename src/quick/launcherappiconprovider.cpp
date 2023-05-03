#include "launcherappiconprovider.h"

#include "iconutils.h"

LauncherAppIconProvider::LauncherAppIconProvider():
    QQuickImageProvider(QQuickImageProvider::Pixmap)
{

}

LauncherAppIconProvider::~LauncherAppIconProvider()
{

}

QPixmap LauncherAppIconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    QPixmap result(requestedSize);
    result.fill(Qt::transparent);

    // uri: image://provider/icon-name::/path/to/entry-name.desktop
    // id: icon-name::/path/to/entry-name.desktop
    if (!id.contains("::")) return result;
    QStringList splited = id.split("::");
    if (splited.count() < 2) return result;

    IconUtils::getThemeIcon(result, splited[0], splited[1], requestedSize.width());

    return result;
}
