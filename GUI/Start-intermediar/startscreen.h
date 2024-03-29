#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QMainWindow>
#include "intermediaryscreen.h"


QT_BEGIN_NAMESPACE
namespace Ui { class StartScreen; }
QT_END_NAMESPACE

class StartScreen : public QMainWindow
{
    Q_OBJECT

public:
    StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

private slots:
    void on_START_clicked();

private:
    Ui::StartScreen *ui;
    IntermediaryScreen intscr;


};
#endif // STARTSCREEN_H
