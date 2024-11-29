//
// Created by Jón Salenger on 3/8/22.
//

#ifndef BASEORRERY_CELESTIAL_H
#define BASEORRERY_CELESTIAL_H

#include <QWidget>
#include <QGraphicsScene>
#include <QtWidgets>
#include <QGraphicsView>
#include <QTimer>
#include <vector>

class Celestial
{
public:
    Celestial(int id, double mass, double pX, double pY, double pZ, double vX, double vY, double vZ, QGraphicsScene* scene, Qt::GlobalColor pen, Qt::GlobalColor brush, double size = 5);
    std::vector<double> calcGravity(Celestial* other);
    std::vector<double> position;
    std::vector<double> velocity;
    double mass;
    const double S = 1e10;
    QGraphicsEllipseItem *planet;
    int hash;
};

#endif //BASEORRERY_CELESTIAL_H
