#ifndef SYMMETRICCLICHESFORM_H
#define SYMMETRICCLICHESFORM_H

#include <QWidget>

#include "symmetriccliches.h"

namespace Ui {
class VariationsForm;
}

class VariationsForm : public QWidget
{
        Q_OBJECT

    public:
        explicit VariationsForm(QWidget *parent = 0);
        ~VariationsForm();
        int getHighestPitch();
        int getLowestPitch();

    private:
        Ui::VariationsForm *ui;
        Variations instance;

};

#endif // SYMMETRICCLICHESFORM_H
