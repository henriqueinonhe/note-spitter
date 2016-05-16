#ifndef RHYTHMICSETUPFORM_H
#define RHYTHMICSETUPFORM_H

#include <QWidget>
#include <QValidator>
#include <QSpinBox>

#include <limits>

#include "rhythmicsetup.h"

namespace Ui {
class RhythmicSetupForm;
}

class RhythmicSetupForm : public QWidget
{
        Q_OBJECT

    public:
        explicit RhythmicSetupForm(QWidget *parent = 0);
        ~RhythmicSetupForm();

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
};

#endif // RHYTHMICSETUPFORM_H
