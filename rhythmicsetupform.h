#ifndef RHYTHMICSETUPFORM_H
#define RHYTHMICSETUPFORM_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>
#include <QLabel>

#include <limits>

#include "rhythmicsetup.h"
#include "musicenums.h"
#include "datahold.h"
#include "melodicsolfege.h"
#include "miditranslationunit.h"

extern DataHold hold;
class MelodicSetupForm;
class Intro;

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
        MelodicSetupForm *parentWindow;
        Intro *introWindow;

    private:
        void setSpinBoxRange();
        void setValidators();
        void setConnections();
        void spinBoxToArray();
        void textLabelToArray();
        bool checkTempo();
        bool checkMeter();
        bool checkBarNumber();
        bool checkCellWeight();
        Ui::RhythmicSetupForm *ui;
        QValidator *barNumberValidator;
        std::array<QSpinBox *, RhythmicSetup::cellsTotal> pesoCelulas;
        std::array<QLabel *, RhythmicSetup::cellsTotal> porcentagemCelulas;

    private slots:
        void concatenatePercentage();
        void updatePercentage(); //I can realy make some improvements to this system
        void checkEnablePushButtonOK();
        void binaryMeterChosen();
        void ternaryMeterChosen();
        void MAGIC();
        void openParent();

    signals:
        void propagatePercentageUpdate();
};

#endif // RHYTHMICSETUPFORM_H
