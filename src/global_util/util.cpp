// SPDX-FileCopyrightText: 2015 - 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "util.h"
#include "appsmanager.h"

#include "utils.h"

#include <DHiDPIHelper>
#include <DGuiApplicationHelper>
#include <DConfig>

#include <QStandardPaths>
#include <QDir>
#include <QPixmap>
#include <QPainter>
#include <QSvgRenderer>
#include <QImageReader>
#include <QApplication>
#include <QIcon>
#include <QScopedPointer>
#include <QIconEngine>


DWIDGET_USE_NAMESPACE

/**
 * @brief renderSVG 根据实体屏幕渲染指定路径、指定大小的图片
 * @param path 渲染图片的路径
 * @param size 渲染图片的大小
 * @return 返回渲染后的pixmap
 */
const QPixmap renderSVG(const QString &path, const QSize &size)
{
    if (!QFileInfo::exists(path))
        return QPixmap();

    QImageReader reader;
    QPixmap pixmap;
    reader.setFileName(path);
    if (reader.canRead()) {
        const qreal ratio = qApp->devicePixelRatio();
        reader.setScaledSize(size * ratio);
        pixmap = QPixmap::fromImage(reader.read());
        pixmap.setDevicePixelRatio(ratio);
    }
    else {
        pixmap.load(path);
    }

    return pixmap;
}

const QPixmap loadSvg(const QString &fileName, const QSize &size)
{
    if (!QFileInfo::exists(fileName))
         return QPixmap();

    QPixmap pixmap(size);
    QSvgRenderer renderer(fileName);
    pixmap.fill(Qt::transparent);

    QPainter painter;
    painter.begin(&pixmap);
    renderer.render(&painter);
    painter.end();

    return pixmap;
}

/**
 * @brief SettingsPtr 根据给定信息返回一个QGSettings指针
 * @param schema_id The id of the schema
 * @param path If non-empty, specifies the path for a relocatable schema
 * @param parent 创建指针的父对象
 * @return 返回QGSetting指针对象
 */
QGSettings *SettingsPtr(const QString &schema_id, const QByteArray &path, QObject *parent)
{
    if (QGSettings::isSchemaInstalled(schema_id.toUtf8())) {
        QGSettings *settings = new QGSettings(schema_id.toUtf8(), path, parent);
        return settings;
    }
    qDebug() << "Cannot find gsettings, schema_id:" << schema_id;
    return nullptr;
}

/**
 * @brief SettingsPtr 根据给定信息返回一个QGSettings指针
 * @param module 传入QGSettings构造函数时，会添加"com.deepin.dde.dock.module."前缀
 * @param path If non-empty, specifies the path for a relocatable schema
 * @param parent 创建指针的付对象
 * @return
 */
QGSettings *ModuleSettingsPtr(const QString &module, const QByteArray &path, QObject *parent)
{
    return SettingsPtr("com.deepin.dde.dock.module." + module, path, parent);
}

/* convert 'some-key' to 'someKey' or 'SomeKey'.
 * the second form is needed for appending to 'set' for 'setSomeKey'
 */
QString qtify_name(const char *name)
{
    bool next_cap = false;
    QString result;

    while (*name) {
        if (*name == '-') {
            next_cap = true;
        } else if (next_cap) {
            result.append(QChar(*name).toUpper().toLatin1());
            next_cap = false;
        } else {
            result.append(*name);
        }

        name++;
    }

    return result;
}

/**
 * @brief SettingValue 根据给定信息返回获取的值
 * @param schema_id The id of the schema
 * @param path If non-empty, specifies the path for a relocatable schema
 * @param key 对应信息的key值
 * @param fallback 如果找不到信息，返回此默认值
 * @return
 */
QVariant SettingValue(const QString &schema_id, const QByteArray &path, const QString &key, const QVariant &fallback)
{
    const QGSettings *settings = SettingsPtr(schema_id, path);

    if (settings && ((settings->keys().contains(key)) || settings->keys().contains(qtify_name(key.toUtf8().data())))) {
        QVariant v = settings->get(key);
        delete settings;
        return v;
    } else {
        qDebug() << "Cannot find gsettings, schema_id:" << schema_id
                 << " path:" << path << " key:" << key
                 << "Use fallback value:" << fallback;
        return fallback;
    }
}

/**
 * @brief getThemeIcon 从系统主题或者缓存中获取应用图标
 * @param pixmap 应用图标对象
 * @param itemInfo 应用程序信息
 * @param size 应用程序大小
 * @param reObtain 是否重新获取标识
 * @return 返回是否获取到应用图标状态
 */
bool getThemeIcon(QPixmap &pixmap, const ItemInfo_v1 &itemInfo, const int size)
{
    return IconUtils::getThemeIcon(pixmap, itemInfo.m_iconKey, itemInfo.m_desktop, size);
}

/**
 * @brief getIcon 根据传入的\a name 参数重新从系统主题中获取一次图标
 * @param name 图标名
 * @return 获取到的图标
 * @note 之所以不使用QIcon::fromTheme是因为这个函数中有缓存机制，获取系统主题中的图标的时候，第一次获取不到，下一次也是获取不到
 */
QIcon getIcon(const QString &name)
{
    //TODO 这里找图标会耗时，界面轻微卡顿，后面可以改成单独开启线程去查找
    auto getIconList = [ = ] (const QString &iconName) {
        QProcess process;
        process.start("qtxdg-iconfinder", QStringList() << iconName);
        process.closeWriteChannel();
        process.waitForFinished();

        int exitCode = process.exitCode();
        QString outputTxt = process.readAllStandardOutput();

        auto list = outputTxt.split("\n");

        if (exitCode != 0 || list.size() <= 3)
            return QStringList() << "";

        // 去掉无用数据
        list.removeFirst();
        list.removeLast();
        list.removeLast();

        for (auto &s : list) {
            s = s.simplified();
        }

        return list;
    };

    return QIcon::fromTheme(getIconList(name).first());
}

QString cacheKey(const ItemInfo_v1 &itemInfo)
{
    return itemInfo.m_name + itemInfo.m_iconKey;
}

DConfig *ConfigWorker::INSTANCE = Q_NULLPTR;

DConfig *ConfigWorker::instance()
{
    if (!INSTANCE)
        INSTANCE = new DConfig(DLauncher::DEFAULT_META_CONFIG_NAME);

    return INSTANCE;
}

QVariant ConfigWorker::getValue(const QString &key, const QVariant &defaultValue)
{
    if (!instance()->isValid()) {
        qWarning() << QString("DConfig is invalid, name:[%1], subpath[%2].").
                        arg(instance()->name(), instance()->subpath());
        return defaultValue;
    }

    if (!instance()->keyList().contains(key)) {
        qWarning() << QString("key: (%1) doesn't exist").arg(key);
        return defaultValue;
    }

    return instance()->value(key);
}

void ConfigWorker::setValue(const QString &key, const QVariant &value)
{
    if (!instance()->isValid()) {
        qWarning() << QString("DConfig is invalid, name:[%1], subpath[%2].").
                        arg(instance()->name(), instance()->subpath());
        return;
    }

    if (!instance()->keyList().contains(key)) {
        qWarning() << QString("key: (%1) doesn't exist").arg(key);
        return;
    }

    instance()->setValue(key, value);
}
