#ifndef APPLICATIONPROPERTIES_H
#define APPLICATIONPROPERTIES_H

#include "appdata.h"

#include <QDialog>

namespace Ui {
class ApplicationProperties;
}

class ApplicationProperties : public QDialog
{
    Q_OBJECT

public:
    explicit ApplicationProperties(AppData appData, QWidget *parent = 0);
    ~ApplicationProperties();

private:
    Ui::ApplicationProperties *ui;
    AppData app;
};

#endif // APPLICATIONPROPERTIES_H
