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
            this, SLOT
    connect(ui->pushButtonSR, SIGNAL(clicked(bool)),
            melodicSetupWindow.rhythmicSetupWindow, SLOT(showRhythmicSetupForm));
    connect(ui->pushButtonSR, SIGNAL(clicked(bool)),
            this, SLOT(close()));




}

Intro::~Intro()
{
    delete ui;
}

void Intro::showMelodicSetupForm()
{
    melodicSetupWindow.show();
}

void Intro::setupRhythmicSolfege()
{


    hold.highestPitch = 69;
    hold.lowestPitch = 69;
    hold.firstPitch = 69;
    hold.notesWeight = getPesoNotas();
    hold.intervalsWeight = getPesoIntervalos();
    hold.noLoop = getNoLoop();
}
