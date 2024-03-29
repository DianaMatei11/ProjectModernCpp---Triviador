#ifndef HARTA_H
#define HARTA_H

#include<vector>
#include <QMainWindow>
#include <QPushButton>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <cpr/cpr.h>
#include <crow.h>
#include "intrebarinumerice.h"
#include "intrebarigrila.h"
#include <qtimer.h>

namespace Ui { class harta; }

class Harta : public QMainWindow
{
    Q_OBJECT
private:
    enum class Etapa
    {
        AlegereBaza,
        Cucerire,
        Razboi
    };

public:

    explicit Harta(QWidget* parent = nullptr);
    void setUsername(const std::string& str);
    void setColor(QColor color);
    void mousePressEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent*);
    void coord();
    void gameManager();
    void getScore();
    void getOrder(Etapa etapa);
    ~Harta();

private slots:

private:
    std::vector<QRect> patrat;
    std::string userName;
    QColor userColor;
    IntrebariNumerice intrebareNumerica;
    IntrebariGrila intrebareGrila;
    QTimer t;
    int nrPlayers;
    Ui::harta* ui;
};
#endif // HARTA_H
