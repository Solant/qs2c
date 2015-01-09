#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QStringList>

#include "appdata.h"

class XmlParser
{
public:
    XmlParser();
    QMap<QString, QString>* readSettings();
    AppData readAppSettings(QString filePath);
    QList<AppData>* readAppsSettings(QStringList files);
    QStringList preparedConfigsPath();
    void writeSettings();
    void writeAppSettings(AppData* appData, QString filePath);
};

#endif // XMLPARSER_H
