// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include <QObject>

#undef signals
#include <gio/gio.h>
#define signals Q_SIGNALS

class AppInfoMonitor: public QObject
{
    Q_OBJECT

public:
    explicit AppInfoMonitor(QObject * parent);
    ~AppInfoMonitor();

    QList<QHash<QString, QString> > allAppInfosShouldBeShown();

Q_SIGNALS:
    void changed();
};
