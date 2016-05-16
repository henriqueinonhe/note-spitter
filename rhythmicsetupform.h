#ifndef RHYTHMICSETUPFORM_H
#define RHYTHMICSETUPFORM_H

#include <QWidget>

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
        Ui::RhythmicSetupForm *ui;
};

#endif // RHYTHMICSETUPFORM_H
