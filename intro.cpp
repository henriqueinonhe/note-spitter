#include "intro.h"
#include "ui_intro.h"

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
            this, SLOT(hide()));
    melodicSetupWindow.parentWindow = this;

    //pushButtonSR
    connect(ui->pushButtonSR, SIGNAL(clicked(bool)),
            this, SLOT(setupRhythmicSolfege()));
    connect(ui->pushButtonSR, SIGNAL(clicked(bool)),
            this, SLOT(hide()));
    rhythmicSetupWindow.introWindow = this;

    //pushButtonCS
    connect(ui->pushButtonCS, SIGNAL(clicked(bool)),
            this, SLOT(showSymmetricClichesForm()));
    connect(ui->pushButtonCS, SIGNAL(clicked(bool)),
            this, SLOT(hide()));
    symmetricSetupWindow.parentWindow = this;

    //pushButtonV
    connect(ui->pushButtonV, SIGNAL(clicked(bool)),
            this, SLOT(showVariationsForm()));
    connect(ui->pushButtonV, SIGNAL(clicked(bool)),
            this, SLOT(hide()));

    //pushButtonSettings
    connect(ui->pushButtonSettings, SIGNAL(clicked(bool)),
            this, SLOT(showSettingsForm()));
    connect(ui->pushButtonSettings, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    variationsWindow.parentWindow = this;

}

Intro::~Intro()
{
    delete ui;
}

void Intro::showSettingsForm()
{
    settingsWindow.show();
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

    //Security Measure
    rhythmicSetupWindow.parentWindow = nullptr;

    rhythmicSetupWindow.show();
}

void Intro::showVariationsForm()
{
    variationsWindow.show();
}

void Intro::showSymmetricClichesForm()
{
    symmetricSetupWindow.show();
}







