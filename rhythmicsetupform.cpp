#include "rhythmicsetupform.h"
#include "ui_rhythmicsetupform.h"

RhythmicSetupForm::RhythmicSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RhythmicSetupForm)
{
    ui->setupUi(this);

    //Convert SpinBox Array
    spinBoxToArray();

    //Setting Spin Boxes' Range
    setSpinBoxRange();

    //Setting Validators
    setValidators();

    //Making Connections
    setConnections();

    /* Testing and debugging purposes */
}

RhythmicSetupForm::~RhythmicSetupForm()
{
    delete ui;
}

void RhythmicSetupForm::setSpinBoxRange()
{
    ui->spinBoxTempo_2->setRange(1, 99);
    ui->sliderPercentage->setRange(0, 100);

    for(int _index = 0; _index < RhythmicSetup::cellsTotal; _index++)
    {
        pesoCelulas[_index]->setRange(0, 100);
    }
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
    connect(ui->pushButtonOK_2, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonOK_2, SIGNAL(clicked(bool)),
            this, SLOT(MAGIC()));
}

void RhythmicSetupForm::concatenatePercentage()
{
    QString _text = ui->labelLigadura_2->text();

    _text.append("%");

    ui->labelLigadura_2->setText(_text);
}

void RhythmicSetupForm::spinBoxToArray()
{
    pesoCelulas[0] = ui->cellWeight1;
    pesoCelulas[1] = ui->cellWeight2;
    pesoCelulas[2] = ui->cellWeight3;
    pesoCelulas[3] = ui->cellWeight4;
    pesoCelulas[4] = ui->cellWeight5;
    pesoCelulas[5] = ui->cellWeight6;
    pesoCelulas[6] = ui->cellWeight7;
    pesoCelulas[7] = ui->cellWeight8;
    pesoCelulas[8] = ui->cellWeight9;
    pesoCelulas[9] = ui->cellWeight10;
    pesoCelulas[10] = ui->cellWeight11;
    pesoCelulas[11] = ui->cellWeight12;
    pesoCelulas[12] = ui->cellWeight13;
    pesoCelulas[13] = ui->cellWeight14;
    pesoCelulas[14] = ui->cellWeight15;
    pesoCelulas[15] = ui->cellWeight16;
    pesoCelulas[16] = ui->cellWeight17;
    pesoCelulas[17] = ui->cellWeight18;
    pesoCelulas[18] = ui->cellWeight19;
    pesoCelulas[19] = ui->cellWeight20;
    pesoCelulas[20] = ui->cellWeight21;
    pesoCelulas[21] = ui->cellWeight22;
    pesoCelulas[22] = ui->cellWeight23;
    pesoCelulas[23] = ui->cellWeight24;
    pesoCelulas[24] = ui->cellWeight25;
    pesoCelulas[25] = ui->cellWeight26;
    pesoCelulas[26] = ui->cellWeight27;
    pesoCelulas[27] = ui->cellWeight28;
    pesoCelulas[28] = ui->cellWeight29;
    pesoCelulas[29] = ui->cellWeight30;
    pesoCelulas[30] = ui->cellWeight31;
    pesoCelulas[31] = ui->cellWeight32;
    pesoCelulas[32] = ui->cellWeight33;
    pesoCelulas[33] = ui->cellWeight34;
    pesoCelulas[34] = ui->cellWeight35;
    pesoCelulas[35] = ui->cellWeight36;
    pesoCelulas[36] = ui->cellWeight37;
    pesoCelulas[37] = ui->cellWeight38;
    pesoCelulas[38] = ui->cellWeight39;
}

std::array<int, RhythmicSetup::cellsTotal> RhythmicSetupForm::getPesoCelulas()
{
    /* Returns the array to setup the rhythm. */
    std::array<int,  RhythmicSetup::cellsTotal> _array;

    for(unsigned int _index = 0; _index < RhythmicSetup::cellsTotal; _index++)
    {
        _array[_index] = pesoCelulas[_index]->value();
    }

    return _array;
}

int RhythmicSetupForm::getBarNumber()
{
    return ui->lineEditBarNumber_2->text().toInt();
}

int RhythmicSetupForm::getPulseNumber()
{
    return ui->spinBoxTempo_2->value();
}

int RhythmicSetupForm::getSlurChance()
{
    return ui->sliderPercentage->value();
}

PulseMeasureValidFigures RhythmicSetupForm::getPulseMeasure()
{
    switch(ui->comboBoxCompasso_2->currentText().toInt())
    {
        case 2: return MEASURE_HALF;
        case 4: return MEASURE_QUARTER;
        case 8: return MEASURE_EIGHTH;
        case 16: return MEASURE_SIXTEENTH;
        case 32: return MEASURE_THIRTYSECOND;
    }
}

TimeSignatureMeter RhythmicSetupForm::getMeter()
{
    if(ui->radioButtonSimples_2->isChecked()) return BINARY_METER;
    else if(ui->radioButtonComposto_2->isChecked()) return TERNARY_METER;
}

void RhythmicSetupForm::MAGIC()
{
    /* For debbuging purposes only! */
    hold.pulseNumber = getPulseNumber();
    hold.pulseMeasure = getPulseMeasure();
    hold.meter = getMeter();
    hold.barNumber = getBarNumber();
    hold.slurChance = getSlurChance();
    hold.cellsWeight = getPesoCelulas();

    MelodicSolfege instance(hold.highestPitch,
                            hold.lowestPitch,
                            hold.firstPitch,
                            hold.notesWeight,
                            hold.intervalsWeight,
                            hold.noLoop,
                            hold.pulseNumber,
                            hold.pulseMeasure,
                            hold.meter,
                            hold.barNumber,
                            hold.slurChance,
                            hold.cellsWeight);

    MidiTranslationUnit unit;

    unit.setPulseNumber(hold.pulseNumber);
    unit.setPulseMeasure(hold.pulseMeasure);
    unit.setTimeClock(960);
    unit.setSampleHeaderAddress("C:\\Users\\Henrique Inonhe\\Desktop\\QTLearning\\ProjetoMusica\\NEWSAMPLE.mid");
    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\MidiOutput.mid");
    unit.translateToMidi(instance.getNoteArray());
    unit.writeToFile();

}







