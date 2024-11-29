//
// Created by Jón Salenger on 3/8/22.
//

#include "WindowWidget.h"
#include "Celestial.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <vector>
#include <QDebug>
#include <chrono>
#include <ctime>

struct tm* getTimeAndDate(unsigned long long milliseconds)
{
    time_t seconds = (time_t)(milliseconds/1000);
    if ((unsigned long long)seconds*1000 == milliseconds)
        return localtime(&seconds);
    return NULL; // milliseconds >= 4G*1000
}

WindowWidget::WindowWidget(QWidget *parent)
        : QWidget(parent)
{


    // start
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene);

    QSize size = this->size();

    scene->setSceneRect(
            0,
            0,
            size.width(),
            size.height());

    QPen redPen(Qt::red);
    QBrush greenBrush(Qt::green);
    QPen bluePen(Qt::blue);
    bluePen.setWidth(7);

    sun = new Celestial(0, 1988500e24,
                        -1.313115203921439e9,
                        4.178402812179458e8,
                        2.725338635781003e7,
                        -4.712250060815705e-3,
                        -1.493618902316053e1,
                        2.330282356755951e-1,
                        scene,
                        Qt::red,
                        Qt::red);

    mercury = new Celestial(1, 3.302e23,
                            3.561616207245586e9,
                            -6.819827487396267e10,
                            -6.027110284195155e9,
                            3.881596761488947e4,
                            5.937874860560860e3,
                            -3.074214602690660e3,
                            scene,
                            Qt::gray,
                            Qt::gray);

    venus = new Celestial(2, 48.685e23,
                          -1.020984875300008e11,
                          -3.788111125676975e10,
                          5.317066722178431e9,
                          1.219789970586874e4,
                          -3.291125910594936e4,
                          -1.155461896417066e3,
                          scene,
                          Qt::darkYellow,
                          Qt::darkYellow);

    earth = new Celestial(3, 5.97219e24,
                          -1.453898375063368e11,
                          3.610646588850922e10,
                          2.638346146375872e7,
                          -7.645200362164588e3,
                          -2.905316967439057e4,
                          7.123751832818215e-1,
                          scene,
                          Qt::blue,
                          Qt::blue);

    

//    rocket = new Celestial(3, 1,
//                          -1.453898375063368e11,
//                          3.610646588850922e10,
//                          2.638346146375872e7,
//                          -7.645200362164588e3,
//                          -2.905316967439057e4,
//                          7.123751832818215e-1,
//                          scene,
//                          Qt::blue,
//                          Qt::blue);

    mars = new Celestial(4, 6.4171e23,
                         2.191255984468861e9,
                         -2.169555733790518e11,
                         -4.614373541961804e9,
                         2.513334864632631e4,
                         2.459668803839013e3,
                         -5.645406215125717e2,
                         scene,
                         Qt::darkRed,
                         Qt::darkRed);

    jupiter = new Celestial(5, 189818.722e22, /* I know that this is not proper scientific notation and I am sorry */
                            7.175042768311715e11,
                            -1.948176524909190e11,
                            -1.524410871045007e10,
                            3.266127559345549e3,
                            1.322150954090218e4,
                            -1.280149278633376e2,
                            scene,
                            Qt::darkRed,
                            Qt::red);

    saturn = new Celestial(6, 5.6834e26,
                           1.074880694083678e12,
                           -1.018038196063326e12,
                           -2.509418840348059e10,
                           6.102337375093215e3,
                           6.994617380613650e3,
                           -3.651139915998614e2,
                           scene,
                           Qt::yellow,
                           Qt::yellow);

    uranus = new Celestial(7, 86.813e24,
                           2.125965188989765e12,
                           2.042849801191421e12,
                           -1.995505931252134e10,
                           -4.768521406590986e3,
                           4.593235694761563e3,
                           7.900491070501525e1,
                           scene,
                           Qt::cyan,
                           Qt::cyan);

    neptune = new Celestial(8, 102.409e24,
                            4.435656058448622e12,
                            -5.810154182866080e11,
                            -9.025927331585464e10,
                            6.699856339681983e2,
                            5.422188852764119e3,
                            -1.264922367074801e2,
                            scene,
                            Qt::darkCyan,
                            Qt::darkCyan);

    moon = new Celestial(9, 7.349e22,
                         -1.450790225808691e11,
                         3.634961945632948E+10,
                         1.642167266917229E+07,
                         -8.213804878425977E+03,
                         -2.824103833554625E+04,
                         8.350998884856331e1,
                         scene,
                         Qt::lightGray,
                         Qt::lightGray, 2);

    planets.push_back(sun);
    planets.push_back(mercury);
    planets.push_back(venus);
    planets.push_back(earth);
    planets.push_back(mars);
    planets.push_back(jupiter);
    planets.push_back(saturn);
    planets.push_back(uranus);
    planets.push_back(moon);
    planets.push_back(neptune);

//    clock->setText("yo mamma");
    clock = new QLabel(view);
    clock->setText("yo mamma");
//    auto tm = getTimeAndDate(0);
//    clock->setText("Year: " + QString::number(tm->tm_year) + "\n"
//        + "Month: " + QString::number(tm->tm_mon) + "\n" +
//        + "Day: " + QString::number(tm->tm_wday) + "\n" +
//        "Hr: " + QString::number(tm->tm_hour));

    view->setMinimumSize(900, 900);
    view->setMaximumSize(900, 900);
    view->show();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WindowWidget::update);
    timer->start();

    qDebug() << "Force of gravity of sun on earth: " << earth->calcGravity(sun);
}

std::vector<long> sepTime(long totalTime) {
    // seconds left over to be split into months
    long yearsRemainder = totalTime % 0x1E14320; // secs in year
    long monthsRemainder = yearsRemainder % 0x2819A0; // secs in month
    long dayRemainder = monthsRemainder % 0x15180;
    long hourRemainder = dayRemainder % 0xE10;
    long minRemainder = hourRemainder % 0x3C;

    long years = (totalTime - yearsRemainder) / 0x1E14320 + 2022;
    long months = (yearsRemainder - monthsRemainder) / 0x2819A0 + 3;
    long days = (monthsRemainder - dayRemainder) / 0x15180 + 8;
    long hours = (dayRemainder - hourRemainder) / 0xE10;
    long mins = (hourRemainder - minRemainder) / 0x3C;
    long secs = minRemainder;

    return std::vector<long> {years, months, days, hours, mins, secs};
}

std::vector<double> Vec::vectorSubtraction(std::vector<double> a, std::vector<double> b) {
    return std::vector<double> {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

std::vector<double> Vec::vectorAddition(std::vector<double> a, std::vector<double> b) {
    return std::vector<double> {a[0] + b[0], a[1] + b[1], a[2] + b[2]};
}

std::vector<double> Vec::vectorDivision(std::vector<double> a, double b) {
    return std::vector<double> {a[0] / b, a[1] / b, a[2] / b};
}

std::vector<double> Vec::vectorMultiplication(std::vector<double> a, double b) {
    return std::vector<double> {a[0] * b, a[1] * b, a[2] * b};
}

void WindowWidget::updatePosition(Celestial* planet, std::vector<double> netForce) {
    const double dt = 10e4;

    // calculate acceleration with force; F/m = a
    std::vector<double> acceleration = Vec::vectorDivision(netForce, planet->mass);

    // calculate the velocity
    std::vector<double> dV = Vec::vectorMultiplication(acceleration, dt);
    // add dV to planet V
    planet->velocity = Vec::vectorAddition(planet->velocity, dV);

    // calculate displacement
    std::vector<double> dP = Vec::vectorMultiplication(planet->velocity, dt);
    // add displacement to position; then update position
    planet->position = Vec::vectorAddition(planet->position, dP);

    planet->planet->moveBy(dP[0] / planet->S, dP[1] / planet->S);

    return;
}

void WindowWidget::update() {
    for (Celestial* major : planets) {
        std::vector<double> force(3, 0);
        for (Celestial* minor : planets) {
            if (major->hash == minor->hash) continue;
            force = Vec::vectorAddition(force, major->calcGravity(minor));
        }
        updatePosition(major, force);
    }

    totalTime += 10e4;
    std::vector<long> times = sepTime(totalTime);
    std::string str = std::to_string(times[0]) + "/" + std::to_string(times[1]) + "/" + std::to_string(times[2]) + "/" + std::to_string(times[3]) + "/" + std::to_string(times[4]) + "/" + std::to_string(times[5]);
    clock->setText(QString::fromStdString(str));
}

WindowWidget::~WindowWidget()
{}
