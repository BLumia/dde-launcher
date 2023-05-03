// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "dwindowedframe.h"

#include "constants.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickWidget>
#include <launcherappiconprovider.h>
#include <DDBusSender>

using namespace DLauncher;

DWindowedFrame::DWindowedFrame(QWidget *parent)
    : DBlurEffectWidget(parent)
    , m_menuWorker(new MenuWorker(this))
    , m_allAppsModel(new AppsListModel(AppsListModel::WindowedAll, this))
    , m_favoriteModel(new AppsListModel(AppsListModel::Favorite, this))
    , m_filterModel(new SortFilterProxyModel(this))
    , m_sortModel(new QSortFilterProxyModel(this))
    , m_appsManager(AppsManager::instance())
{
    initUi();
    initConnections();
}

DWindowedFrame::~DWindowedFrame()
{

}

void DWindowedFrame::initUi()
{
    setMaskColor(DBlurEffectWidget::AutoColor);
    setBlendMode(DBlurEffectWidget::InWindowBlend);

    QHBoxLayout * mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);

    QQuickWidget * qqw = new QQuickWidget();
    QQmlEngine * engine = qqw->engine();
    QQmlContext * ctx = engine->rootContext();
    LauncherAppIconProvider * provider = new LauncherAppIconProvider;
    engine->addImageProvider("app-icon", provider);
    ctx->setContextProperty("appModel", m_filterModel); // the `m_allAppsModel` is likely not needed at all
    ctx->setContextProperty("sortModel", m_sortModel);
    ctx->setContextProperty("favoriteModel", m_favoriteModel);
    ctx->setContextProperty("menuWorker", m_menuWorker.get());
    ctx->setContextProperty("frame", this);
    qqw->setClearColor(QColor(Qt::transparent));
    qqw->setAttribute(Qt::WA_AlwaysStackOnTop);
    qqw->setSource(QUrl("qrc:/qml/WindowedFrame.qml"));
    mainLayout->addWidget(qqw);

    setLayout(mainLayout);

    m_filterModel->setSourceModel(m_allAppsModel);
    m_filterModel->setFilterRole(AppsListModel::AppRawItemInfoRole);
    m_filterModel->setFilterKeyColumn(0);
    m_filterModel->setSortCaseSensitivity(Qt::CaseInsensitive);

    m_sortModel->setSourceModel(m_allAppsModel);
    m_sortModel->setSortRole(AppsListModel::AppCategoryNameRole);
    m_sortModel->sort(0);

    setFixedSize(780, 600);
}

void DWindowedFrame::initConnections()
{
    connect(m_menuWorker.get(), &MenuWorker::requestEditCollected, m_appsManager, &AppsManager::onEditCollected);
    connect(m_menuWorker.get(), &MenuWorker::showDebugInfo, this, [](const QModelIndex & idx){
        DDialog * dlg = new DDialog;
        dlg->setMessage(idx.data(AppsListModel::AppRawItemInfoRole).value<ItemInfo_v1>().m_key);
        dlg->show();
//        dlg->deleteLater();
        qDebug() << idx.data(AppsListModel::AppRawItemInfoRole).value<ItemInfo_v1>().m_key << "xxxxx";
    });
}

void DWindowedFrame::onToggleFullscreen()
{
    // 后台没有启动,切换全屏会造成后台默认数据和前台数据不统一,造成显示问题
    if (!m_appsManager->appNums(AppsListModel::FullscreenAll))
        return;

//    // 切换到全屏就不绘制小窗口列表中的item
//    AppListDelegate *delegate = static_cast<AppListDelegate *>(m_appsView->itemDelegate());
//    if (delegate)
//        delegate->setActived(false);

//    // 全屏状态标识
//    m_calcUtil->setFullScreen(true);

    // 同步本地当前是全屏的状态
    DDBusSender()
        .service(DBUS_DAEMON_SERVICE_NAME)
        .interface(DBUS_DAEMON_SERVICE_NAME)
        .path(DBUS_DAEMON_PATH_NAME)
        .property("Fullscreen")
        .set(true);
}

void DWindowedFrame::showLauncher()
{
    activateWindow();
    setFocus(Qt::ActiveWindowFocusReason);

    show();
}

void DWindowedFrame::hideLauncher()
{
    if (!visible()) return;

    hide();
}

bool DWindowedFrame::visible()
{
    return isVisible();
}

void DWindowedFrame::launchCurrentApp()
{
    // ?
}

void DWindowedFrame::appendToSearchEdit(const char ch)
{
    // ?
}

void DWindowedFrame::moveCurrentSelectApp(const int key)
{
    // ?
}

void DWindowedFrame::regionMonitorPoint(const QPoint &point, int flag)
{
    // ?
}

void DWindowedFrame::uninstallApp(const QString &desktopPath)
{
    // ?
}
