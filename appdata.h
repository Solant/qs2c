#ifndef APPDATA_H
#define APPDATA_H

#include <QStringList>

class AppData
{
private:
    QStringList m_Files;
    QStringList m_CloudFiles;
    QString m_Name;
    QString m_FileName;
    QString m_OS;

public:
    AppData();
    ~AppData();

    QStringList files() const;
    QString fileName() const;
    QStringList cloudFiles() const;
    QString name() const;
    QString oS() const;

    void setFiles(QStringList *files);
    void setName(const QString name);
    void setFileName(const QString &fileName);
    void setCloudFiles(const QStringList &cloudFiles);
    void setOS(const QString &OS);

    void addFile(const QString file);

    void removeAt(int index);
};

#endif // APPDATA_H
