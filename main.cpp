#include <QApplication>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "WindowWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    WindowWidget w(nullptr);
//    w.show();
    return QApplication::exec();
}
