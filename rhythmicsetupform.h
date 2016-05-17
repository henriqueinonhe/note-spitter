#ifndef RHYTHMICSETUPFORM_H
#define RHYTHMICSETUPFORM_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>

#include <limits>

#include "rhythmicsetup.h"
#include "musicenums.h"
#include "datahold.h"
#include "melodicsolfege.h"
#include "miditranslationunit.h"

extern DataHold hold;

namespace Ui {
class RhythmicSetupForm;
}

class RhythmicSetupForm : public QWidget
{
        Q_OBJECT

    public:
        explicit RhythmicSetupForm(QWidget *parent = 0);
        ~RhythmicSetupForm();
        std::array<int, RhythmicSetup::cellsTotal> getPesoCelulas();
        int getBarNumber();
        int getPulseNumber();
        PulseMeasureValidFigures getPulseMeasure();
        int getSlurChance();
        TimeSignatureMeter getMeter();

    private:
        void setSpinBoxRange();
        void setValidators();
        void setConnections();
        void spinBoxToArray();
        Ui::RhythmicSetupForm *ui;
        QValidator *barNumberValidator;
        QSpinBox *pesoCelulas[RhythmicSetup::cellsTotal];

    private slots:
        void concatenatePercentage();
        void MAGIC();
};

#endif // RHYTHMICSETUPFORM_H
