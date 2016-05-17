#include "rhythmicsetupform.h"
#include "ui_rhythmicsetupform.h"

RhythmicSetupForm::RhythmicSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RhythmicSetupForm)
{
    ui->setupUi(this);

    //Convert SpinBox Array

    //Setting Spin Boxes' Range
    setSpinBoxRange();

    //Setting Validators
    setValidators();

    //Making Connections
    setConnections();

}

RhythmicSetupForm::~RhythmicSetupForm()
{
    delete ui;
}

void RhythmicSetupForm::setSpinBoxRange()
{
    ui->spinBoxTempo_2->setRange(1, 99);
    ui->sliderPercentage->setRange(0, 100);
}

void RhythmicSetupForm::setValidators()
{
    barNumberValidator = new QIntValidator(1, INT_MAX, this);
    ui->lineEditBarNumber_2->setValidator(barNumberValidator);
}

void RhythmicSetupForm::setConnections()
{
    connect(ui->sliderPercentage, SIGNAL(valueChanged(int)),
            ui->labelLigadura_2, SLOT(setNum(int)));
    connect(ui->sliderPercentage, SIGNAL(valueChanged(int)),
            this, SLOT(concatenatePercentage()));
    connect(ui->pushButtonCancel_2, SIGNAL(clicked(bool)),
            this, SLOT(close()));
}

void RhythmicSetupForm::concatenatePercentage()
{
    QString _text = ui->labelLigadura_2->text();

    _text.append("%");

    ui->labelLigadura_2->setText(_text);
}

void RhythmicSetupForm::spinBoxToArray()
{

}

