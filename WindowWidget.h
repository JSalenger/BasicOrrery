//
// Created by Jón Salenger on 3/8/22.
//

#ifndef BASEORRERY_WINDOWWIDGET_H
#define BASEORRERY_WINDOWWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QGraphicsView>
#include <QTimer>
#include "Celestial.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

namespace Vec {
    std::vector<double> vectorSubtraction(std::vector<double> a, std::vector<double> b);
    std::vector<double> vectorAddition(std::vector<double> a, std::vector<double> b);
    std::vector<double> vectorDivision(std::vector<double> a, double b);
    std::vector<double> vectorMultiplication(std::vector<double> a, double b);
}

class WindowWidget : public QWidget
{
Q_OBJECT

public:
    WindowWidget(QWidget *parent = nullptr);
    ~WindowWidget();
    void update();
    void updatePosition(Celestial* planet, std::vector<double> netForce);

private:
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse;
    QGraphicsView *view;
    QLabel *clock;
    // Define Planets
    Celestial *sun;
    Celestial *mercury;
    Celestial *venus;
    Celestial *earth;
    Celestial *mars;
    Celestial *jupiter;
    Celestial *saturn;
    Celestial *uranus;
    Celestial *neptune;
    Celestial *moon;
    long totalTime = 0;
    std::vector<Celestial*> planets;
};


#endif //BASEORRERY_WINDOWWIDGET_H
