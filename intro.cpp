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
            this, SLOT(setupRhythmicSolfege()));
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
    std::array<int, MelodicSetup::notesTotal> notesWeight;
    notesWeight.fill(0);
    notesWeight[A] = 1; //Dummy note used in rhythmic solfege

    std::array<int, MelodicSetup::intervalsTotal> intervalsWeight;
    intervalsWeight.fill(0);
    intervalsWeight[UNISON] = 1;

    hold.highestPitch = 69;
    hold.lowestPitch = 69;
    hold.firstPitch = 69;
    hold.notesWeight = notesWeight;
    hold.intervalsWeight = intervalsWeight;
    hold.noLoop = false;

    rhythmicSetupWindow.show();
}
