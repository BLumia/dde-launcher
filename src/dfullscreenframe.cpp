// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "dfullscreenframe.h"

#include "constants.h"

#include <DDBusSender>
#include <QHBoxLayout>
#include <QQmlContext>
#include <QQuickWidget>
#include <launcherappiconprovider.h>

using namespace DLauncher;

DFullScreenFrame::DFullScreenFrame(QWidget *parent)
    : BoxFrame(parent)
    , m_menuWorker(new MenuWorker(this))
    , m_allAppsModel(new AppsListModel(AppsListModel::WindowedAll, this))
    , m_filterModel(new SortFilterProxyModel(this))
    , m_appsManager(AppsManager::instance())
{
    initUi();
}

DFullScreenFrame::~DFullScreenFrame()
{

}

void DFullScreenFrame::updateDisplayMode(const int mode)
{
    //?
}

void DFullScreenFrame::initUi()
{
    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QQuickWidget * qqw = new QQuickWidget();
    QQmlEngine * engine = qqw->engine();
    QQmlContext * ctx = engine->rootContext();
    LauncherAppIconProvider * provider = new LauncherAppIconProvider;
    engine->addImageProvider("app-icon", provider);
    ctx->setContextProperty("appModel", m_filterModel); // the `m_allAppsModel` is likely not needed at all
//    ctx->setContextProperty("sortModel", m_sortModel);
//    ctx->setContextProperty("favoriteModel", m_favoriteModel);
    ctx->setContextProperty("menuWorker", m_menuWorker.get());
    ctx->setContextProperty("frame", this);
    qqw->setClearColor(QColor(Qt::transparent));
    qqw->setAttribute(Qt::WA_AlwaysStackOnTop);
    qqw->setSource(QUrl("qrc:/qml/FullscreenFrame.qml"));
    mainLayout->addWidget(qqw);

    setLayout(mainLayout);

    m_filterModel->setSourceModel(m_allAppsModel);
    m_filterModel->setFilterRole(AppsListModel::AppRawItemInfoRole);
    m_filterModel->setFilterKeyColumn(0);
    m_filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);

//    m_sortModel->setSourceModel(m_allAppsModel);
//    m_sortModel->setSortRole(AppsListModel::AppCategoryNameRole);
    //    m_sortModel->sort(0);
}

void DFullScreenFrame::onToggleFullscreen()
{
//    emit toggleMode();
//    emit m_calcUtil->loadWindowIcon();
//    m_calcUtil->setFullScreen(false);

    DDBusSender()
        .service(DBUS_DAEMON_SERVICE_NAME)
        .interface(DBUS_DAEMON_SERVICE_NAME)
        .path(DBUS_DAEMON_PATH_NAME)
        .property("Fullscreen")
        .set(false);
}

void DFullScreenFrame::showLauncher()
{
//    m_focusIndex = 1;
//    m_appItemDelegate->setCurrentIndex(QModelIndex());

    // 启动器跟随任务栏位置
    updateGeometry();

//    m_searchWidget->edit()->clearEdit();
//    m_searchWidget->edit()->clear();

//    updateDisplayMode(m_displayMode);

//    m_searchWidget->edit()->lineEdit()->clearFocus();

    setFixedSize(m_appsManager->currentScreen()->geometry().size());
    show();
}

void DFullScreenFrame::hideLauncher()
{
    if (!isVisible())
        return;

//    m_searchWidget->clearSearchContent();
    hide();
}

bool DFullScreenFrame::visible()
{
    return isVisible();
}

void DFullScreenFrame::launchCurrentApp()
{
    //?
}

void DFullScreenFrame::appendToSearchEdit(const char ch)
{
    //?
}

void DFullScreenFrame::moveCurrentSelectApp(const int key)
{
    //?
}

void DFullScreenFrame::regionMonitorPoint(const QPoint &point, int flag)
{
    //?
}

void DFullScreenFrame::uninstallApp(const QString &desktopPath)
{
    //?
}
