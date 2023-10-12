#ifndef VARIATIONSFORM_H
#define VARIATIONSFORM_H

#include "variations.h"
#include "miditranslationunit.h"

#include <QWidget>
#include <QValidator>

#include <array>

class Intro;

namespace Ui {
class VariationsForm;
}

class VariationsForm : public QWidget
{
        Q_OBJECT

    public:
        explicit VariationsForm(QWidget *parent = 0);
        ~VariationsForm();
        Intro *parentWindow;

    private:
        int getHighestPitch();
        int getLowestPitch();
        std::array<bool, 13> getAllowedIntervals();
        bool getStatic();
        int translatePitch(const QString &_str);
        Ui::VariationsForm *ui;
        QRegularExpressionValidator *pitchValidator;

    private slots:
        void openParent();
        void runVariations();
};

#endif // VARIATIONSFORM_H
