#ifndef MELODICSETUPFORM_H
#define MELODICSETUPFORM_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>
#include <QLabel>

#include <Array>

#include "melodicsetup.h"
#include "rhythmicsetupform.h"
#include "datahold.h"

extern DataHold hold;

namespace Ui {
class MelodicSetupForm;
}

class MelodicSetupForm : public QWidget
{
        Q_OBJECT

    public:
        explicit MelodicSetupForm(QWidget *parent = 0);
        ~MelodicSetupForm();
        std::array<int, MelodicSetup::notesTotal> getPesoNotas();
        std::array<int, MelodicSetup::intervalsTotal> getPesoIntervalos();
        int getHighestPitch();
        int getLowestPitch();
        int getFirstPitch();
        bool getNoLoop();

    private:
        void spinBoxToArray();
        void setSpinBoxRange();
        void textLabelToArray();
        void setInitialPercentage();
        void setConnections();
        int translatePitch(const QString &_str);
        bool checkPitchLimits();
        bool checkAvailableNotes();
        bool checkAvailableIntervals();
        bool checkFirstPitch();
        bool checkLimitsDefined();
        bool checkIntervalsLimitsConformity();
        bool checkIntervalsPitchConformity();
        bool isWithinLimits(const int _pitch);
        bool isAvailableNote(const int _pitch);
        Ui::MelodicSetupForm *ui;
        QValidator *pitchValidator;
        std::array<QSpinBox *, MelodicSetup::notesTotal> pesoNotas;
        std::array<QSpinBox *, MelodicSetup::intervalsTotal> pesoIntervalos;
        std::array<QLabel *, MelodicSetup::notesTotal> porcentagemNotas;
        std::array<QLabel *, MelodicSetup::intervalsTotal> porcentagemIntervalos;
        RhythmicSetupForm rhythmicSetupWindow;

    private slots:
        void checkEnablePushButtonOK();
        void showRhythmicSetupForm();
        void updatePercentage();

    signals:
        void propagatePercentageChange();

};

#endif // MELODICSETUPFORM_H
