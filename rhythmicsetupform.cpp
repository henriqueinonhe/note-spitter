#include "rhythmicsetupform.h"
#include "ui_rhythmicsetupform.h"

RhythmicSetupForm::RhythmicSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RhythmicSetupForm)
{
    ui->setupUi(this);
}

RhythmicSetupForm::~RhythmicSetupForm()
{
    delete ui;
}
