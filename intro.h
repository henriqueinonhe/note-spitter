#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include "melodicsetupform.h"

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
        MelodicSetupForm melodicSetupWindow;


    private slots:
        void showMelodicSetupForm();
};

#endif // INTRO_H
