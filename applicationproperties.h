#ifndef APPLICATIONPROPERTIES_H
#define APPLICATIONPROPERTIES_H

#include <QDialog>

#include "appdata.h"
#include "applicationpropertiestablemodel.h"

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
    ApplicationPropertiesTableModel *model;
    AppData app;
};

#endif // APPLICATIONPROPERTIES_H
