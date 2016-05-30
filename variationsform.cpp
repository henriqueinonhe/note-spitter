#include "variationsform.h"
#include "ui_symmetricclichesform.h"

VariationsForm::VariationsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VariationsForm)
{
    ui->setupUi(this);
}

VariationsForm::~VariationsForm()
{
    delete ui;
}
