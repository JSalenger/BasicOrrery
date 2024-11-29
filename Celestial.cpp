//
// Created by Jón Salenger on 3/8/22.
//

#include "Celestial.h"
#include <math.h>
#include <QGraphicsScene>
#include <QDebug>
#include "WindowWidget.h"

Celestial::Celestial(int id, double m, double pX, double pY, double pZ, double vX, double vY, double vZ, QGraphicsScene* scene, Qt::GlobalColor penColor, Qt::GlobalColor brushColor, double size)
{
    hash = id;
    mass = m;

    position.push_back(pX);
    position.push_back(pY);
    position.push_back(pZ);

    velocity.push_back(vX);
    velocity.push_back(vY);
    velocity.push_back(vZ);

    QPen pen(penColor);
    QBrush brush(brushColor);
    pen.setWidth(2);
//    qDebug() << "Adding Planet to: " << pX/S << "," << pY/S << ".\n";
    planet = scene->addEllipse(pX/S + (scene->width()/2), pY/S + (scene->height()/2), size, size, pen, brush);
}

// calculates the force due to gravity between the two celestials
std::vector<double> Celestial::calcGravity(Celestial* other) {
    const double G = 0.0000000000667408;

    // a - b = b --> a
    std::vector<double> distance(3, 0);
    distance = Vec::vectorSubtraction(other->position, this->position);

    // magnitude of distance
    double Dmag = sqrt(distance[0] * distance[0] + distance[1] * distance[1] + distance[2] * distance[2]);
    distance = Vec::vectorDivision(distance, Dmag);
    distance = Vec::vectorMultiplication(distance, (G * mass * other->mass) / (Dmag * Dmag));


    // its called distance because it was the distance but it points from other --> this
    // and has been scaled to Gmag meaning it is equivalent to the force of gravity
    return distance;
}
