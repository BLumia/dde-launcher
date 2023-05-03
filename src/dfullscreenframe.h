// SPDX-FileCopyrightText: 2017 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "launcherinterface.h"

#include "worker/menuworker.h"
#include "sortfilterproxymodel.h"

#include "boxframe.h"

DWIDGET_USE_NAMESPACE

class DFullScreenFrame : public BoxFrame, public LauncherInterface
{
    Q_OBJECT
public:
    DFullScreenFrame(QWidget *parent = nullptr);
    ~DFullScreenFrame();

    void updateDisplayMode(const int mode);

private:
    void initUi();

    std::unique_ptr<MenuWorker> m_menuWorker;
    AppsListModel *m_allAppsModel;
    SortFilterProxyModel *m_filterModel;
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

