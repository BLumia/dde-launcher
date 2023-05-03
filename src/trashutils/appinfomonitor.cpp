#include "appinfomonitor.h"

#include <gio/gdesktopappinfo.h>

#include <QHash>

AppInfoMonitor::AppInfoMonitor(QObject *parent)
    : QObject(parent)
{

}

AppInfoMonitor::~AppInfoMonitor()
{

}

QStringList fromGStrV(const char * const * gstr_array)
{
    QStringList result;
    for (unsigned long i = 0; i < g_strv_length((char**)gstr_array); i++) {
        result.append(QString(gstr_array[i]));
    }
    return result;
}

QList<QHash<QString, QString> > AppInfoMonitor::allAppInfosShouldBeShown()
{
    QList<QHash<QString, QString> > results;
    GList * app_infos = g_app_info_get_all();
    g_list_foreach(
        app_infos,
        [](gpointer data, gpointer user_data) {
            QList<QHash<QString, QString> > * result = (QList<QHash<QString, QString> > *)user_data;
            GAppInfo * app_info = (GAppInfo *)data;
            if (g_app_info_should_show(app_info)) {

                GIcon * icon = g_app_info_get_icon(app_info);
                QString iconStr(g_icon_to_string(icon));
                g_free(icon);

                const char * const * keywords = g_desktop_app_info_get_keywords((GDesktopAppInfo*)app_info);
                QStringList keywordsList(fromGStrV(keywords));

                result->append({
                    {"name", QString(g_app_info_get_display_name(app_info))},
                    {"id", QString(g_app_info_get_id(app_info))},
                    {"filepath", QString(g_desktop_app_info_get_filename((GDesktopAppInfo*)app_info))},
                    {"categories", QString(g_desktop_app_info_get_categories((GDesktopAppInfo*)app_info))},
                    {"keywords", keywordsList.join(';')},
                    {"icon", iconStr}
                });
            }
        },
        &results
    );

    return results;
}
