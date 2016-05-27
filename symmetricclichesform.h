#ifndef SYMMETRICCLICHESFORM_H
#define SYMMETRICCLICHESFORM_H

#include <QWidget>

#include "symmetriccliches.h"

namespace Ui {
class SymmetricClichesForm;
}

class SymmetricClichesForm : public QWidget
{
        Q_OBJECT

    public:
        explicit SymmetricClichesForm(QWidget *parent = 0);
        ~SymmetricClichesForm();
        int getHighestPitch();
        int getLowestPitch();

    private:
        Ui::SymmetricClichesForm *ui;
        SymmetricCliches instance;

};

#endif // SYMMETRICCLICHESFORM_H
