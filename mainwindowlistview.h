#ifndef MAINWINDOWLISTVIEW_H
#define MAINWINDOWLISTVIEW_H

#include <QListView>
#include <QPainter>

class MainWindowListView : public QListView
{
void paintEvent(QPaintEvent *e) {
    QListView::paintEvent(e);
    if (model() && model()->rowCount(rootIndex())) return;
    // The view is empty.
    QPainter p(this->viewport());
    p.drawPixmap((rect().width()-807)/2, 0, QPixmap(":/res/resources/tino.png"));
}
public:
    MainWindowListView(QWidget* parent = 0) : QListView(parent) {}
};

#endif // MAINWINDOWLISTVIEW_H
