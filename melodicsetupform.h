#ifndef MELODICSETUPFORM_H
#define MELODICSETUPFORM_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>

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

    private:
        void spinBoxToArray();
        void setSpinBoxRange();
        void setConnections();
        int translatePitch(QString _str);
        Ui::MelodicSetupForm *ui;
        QValidator *pitchValidator;
        QSpinBox *pesoNotas[MelodicSetup::notesTotal];
        QSpinBox *pesoIntervalos[MelodicSetup::intervalsTotal];
        RhythmicSetupForm rhythmicSetupWindow;

    private slots:
        void checkEnablePushButtonOK();
        void showRhythmicSetupForm();

};

#endif // MELODICSETUPFORM_H
