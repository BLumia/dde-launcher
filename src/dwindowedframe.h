// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "launcherinterface.h"

#include "worker/menuworker.h"
#include "sortfilterproxymodel.h"

#include <dblureffectwidget.h>

DWIDGET_USE_NAMESPACE

class DWindowedFrame : public DBlurEffectWidget, public LauncherInterface
{
    Q_OBJECT
public:
    DWindowedFrame(QWidget *parent = nullptr);
    ~DWindowedFrame();

private:
    void initUi();
    void initConnections();

    std::unique_ptr<MenuWorker> m_menuWorker;
    AppsListModel *m_allAppsModel;
    AppsListModel *m_favoriteModel;
    SortFilterProxyModel *m_filterModel;
    QSortFilterProxyModel *m_sortModel;
    AppsManager *m_appsManager;

signals:
    virtual void visibleChanged(bool visible);
    virtual void searchApp(const QString &keyword = QString());

public:
    Q_INVOKABLE void onToggleFullscreen();

    // LauncherInterface interface
public:
    void showLauncher() override;
    void hideLauncher() override;
    bool visible() override;
    void launchCurrentApp() override;
    void appendToSearchEdit(const char ch) override;
    void moveCurrentSelectApp(const int key) override;
    void regionMonitorPoint(const QPoint &point, int flag) override;
    void uninstallApp(const QString &desktopPath) override;
};
