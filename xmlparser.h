#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QStringList>
#include <QPair>

#include "appdata.h"

class XmlParser
{
public:
    XmlParser();
    static QMap<QString, QString>* readSettings();
    static void writeSettings(QMap<QString, QString> *map);

    QStringList preparedConfigsPaths();
    AppData* loadPreparedConfig(QString &filePath);
    void saveUnpreparedConfig(AppData* appData, QString &filePath);
    void savePreparedConfig(AppData* appData, QString &filePath);
    AppData* prepareConfig(QString &filePath);
    AppData* loadUnpreparedConfig(QString &filePath);
    static QPair<QStringList, QStringList> loadAppList(QString &page);
    static QString loadAppConfigFromUrl(QString& page);
private:
    QString preparePath(QString filePath);
};

#endif // XMLPARSER_H
