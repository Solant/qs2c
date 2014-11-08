#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QMap>
#include <QStringList>

#include "appdata.h"

class XMLParser
{
public:
    XMLParser();
    QMap<QString, QString>* readSettings();
    AppData readAppSettings(QString filePath);
    QList<AppData>* readAppsSettings(QStringList files);
    QStringList preparedConfigsPaths();
    void writeSettings();
    void writeAppSettings(AppData* appData, QString filePath);
};

#endif // XMLPARSER_H
