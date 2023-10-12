#ifndef SYMMETRICCLICHESFORM_H
#define SYMMETRICCLICHESFORM_H

#include <QWidget>
#include "symmetriccliches.h"
#include "miditranslationunit.h"
#include <QValidator>
#include <QCloseEvent>

class Intro;

namespace Ui {
class SymmetricClichesForm;
}

class SymmetricClichesForm : public QWidget
{
        Q_OBJECT

    public:
        explicit SymmetricClichesForm(QWidget *parent = 0);
        ~SymmetricClichesForm();
        Intro *parentWindow;

    private:
        bool checkLimitsDefined();
        bool checkPitchLimits();
        bool checkFirstPitch();
        bool checkIntervalPattern();
        bool checkCycleNumber();
        int getHighestPitch();
        int getLowestPitch();
        int getFirstPitch();
        int getCycleNumber();
        int translatePitch(const QString &_str);
        std::vector<int> convertIntervalPattern();
        void closeEvent(QCloseEvent *event);
        Ui::SymmetricClichesForm *ui;
        QRegularExpressionValidator *pitchValidator;
        QRegularExpressionValidator *intervalPatternValidator;
        QIntValidator *cycleNumberValidator;
        SymmetricCliches *instance;


    private slots:
        void checkEnableOk();
        void runSymmetricCliches();
        void openParent();
};

#endif // SYMMETRICCLICHESFORM_H
