#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);

    setFixedSize(size());

    //pushButtonSM
    //connect(ui->pushButtonSM, SIGNAL(clicked(bool)),
      //      this, SLOT(show_melodic_setup()));
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
