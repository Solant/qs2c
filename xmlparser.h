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
    void writeSettings();

    QStringList preparedConfigsPaths();
    AppData* loadPreparedConfig(QString &filePath);
    void saveUnpreparedConfig(AppData* appData, QString &filePath);
    void savePreparedConfig(AppData* appData, QString &filePath);
    AppData* prepareConfig(QString &filePath);
    AppData* loadUnpreparedConfig(QString &filePath);
private:
    QString preparePath(QString filePath);
};

#endif // XMLPARSER_H
