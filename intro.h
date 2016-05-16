#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include "melodicsetup.h"

namespace Ui {
class Intro;
}

class Intro : public QWidget
{
    Q_OBJECT

public:
    explicit Intro(QWidget *parent = 0);
    ~Intro();

private:
    Ui::Intro *ui;
    MelodicSetup w_2;

private slots:
    void show_melodic_setup();
};

#endif // INTRO_H
