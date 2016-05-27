#include "symmetricclichesform.h"
#include "ui_symmetricclichesform.h"

SymmetricClichesForm::SymmetricClichesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SymmetricClichesForm)
{
    ui->setupUi(this);
}

SymmetricClichesForm::~SymmetricClichesForm()
{
    delete ui;
}
