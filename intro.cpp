#include "intro.h"
#include "ui_intro.h"
#include "melodicsetupform.h"

Intro::Intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);

    setFixedSize(size());

    //pushButtonSM
    connect(ui->pushButtonSM, SIGNAL(clicked(bool)),
            this, SLOT(showMelodicSetupForm()));
    connect(ui->pushButtonSM, SIGNAL(clicked(bool)),
            this, SLOT(close()));

    //pushButtonSR
    connect(ui->pushButtonSR, SIGNAL(clicked(bool)),
            this, SLOT(close()));




}

Intro::~Intro()
{
    delete ui;
}

void Intro::showMelodicSetupForm()
{
    //melodicSetupWindow.show();
}
