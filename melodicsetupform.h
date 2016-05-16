#ifndef MELODICSETUPFORM_H
#define MELODICSETUPFORM_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>

#include "melodicsetup.h"
#include "rhythmicsetupform.h"

namespace Ui {
class MelodicSetupForm;
}

class MelodicSetupForm : public QWidget
{
        Q_OBJECT

    public:
        explicit MelodicSetupForm(QWidget *parent = 0);
        ~MelodicSetupForm();

    private:
        void spinBoxToArray();
        void setSpinBoxRange();
        void setConnections();
        int translatePitch(QString _str);
        Ui::MelodicSetupForm *ui;
        QValidator *pitchValidator;
        QSpinBox *PesoNotas[MelodicSetup::notesTotal];
        QSpinBox *PesoIntervalos[MelodicSetup::intervalsTotal];
        RhythmicSetupForm rhythmicSetupWindow;

    private slots:
        void checkEnablePushButtonOK();
        void showRhythmicSetupForm();

};

#endif // MELODICSETUPFORM_H
