#pragma once

#include <QQuickImageProvider>

class LauncherAppIconProvider : public QQuickImageProvider {
public:
    LauncherAppIconProvider();
    ~LauncherAppIconProvider();

    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;
};
