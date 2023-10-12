#ifndef INTRO_H
#define INTRO_H

#include <QWidget>
#include "melodicsetupform.h"
#include "symmetricclichesform.h"
#include "variationsform.h"
#include "settingsform.h"

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
        RhythmicSetupForm rhythmicSetupWindow;
        SymmetricClichesForm symmetricSetupWindow;
        VariationsForm variationsWindow;
        SettingsForm settingsWindow;

    private slots:
        void showMelodicSetupForm();
        void setupRhythmicSolfege();
        void showSymmetricClichesForm();
        void showVariationsForm();
        void showSettingsForm();
};

#endif // INTRO_H
