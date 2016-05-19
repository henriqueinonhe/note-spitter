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

    //Turn Labels into Array
    textLabelToArray();

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

    /* Connecting percentage update. */

    for(int _index = 0; _index < RhythmicSetup::cellsTotal; _index++)
    {
        connect(pesoCelulas[_index], SIGNAL(valueChanged(int)),
                this, SIGNAL(propagatePercentageUpdate()));
    }

    connect(this, SIGNAL(propagatePercentageUpdate()),
            this, SLOT(updatePercentage()));
}

void RhythmicSetupForm::updatePercentage()
{
    /* Updates the percentage regarding cellsWeight. */

    int _totalCellsWeight = 0;

    for(int _index = 0; _index < RhythmicSetup::cellsTotal; _index++)
    {
        _totalCellsWeight += pesoCelulas[_index]->value();
    }

    /* Dealing with arithmethic exception (division by zero), when
     * every cellWeight is set to 0, therefore _totalCellsWeight = 0. */

    if(_totalCellsWeight != 0)
    for(int _index  = 0; _index < RhythmicSetup::cellsTotal; _index++)
    {
        porcentagemCelulas[_index]->setNum(100 * pesoCelulas[_index]->value() /_totalCellsWeight);
        porcentagemCelulas[_index]->setText(porcentagemCelulas[_index]->text().append("%"));
    }
    else
    for(int _index  = 0; _index < RhythmicSetup::cellsTotal; _index++)
    {
       porcentagemCelulas[_index]->setNum(0);
       porcentagemCelulas[_index]->setText(porcentagemCelulas[_index]->text().append("%"));
    }

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
    pesoCelulas[39] = ui->cellWeight40;
    pesoCelulas[40] = ui->cellWeight41;
    pesoCelulas[41] = ui->cellWeight42;
    pesoCelulas[42] = ui->cellWeight43;
    pesoCelulas[43] = ui->cellWeight44;
    pesoCelulas[44] = ui->cellWeight45;
    pesoCelulas[45] = ui->cellWeight46;
  /*  pesoCelulas[46] = ui->cellWeight47;
    pesoCelulas[47] = ui->cellWeight48;
    pesoCelulas[48] = ui->cellWeight49;
    pesoCelulas[49] = ui->cellWeight50;
    pesoCelulas[50] = ui->cellWeight51;
    pesoCelulas[51] = ui->cellWeight52;
    pesoCelulas[52] = ui->cellWeight53;
    pesoCelulas[53] = ui->cellWeight54;
    pesoCelulas[54] = ui->cellWeight55;
    pesoCelulas[55] = ui->cellWeight56;
    pesoCelulas[56] = ui->cellWeight57;
    pesoCelulas[57] = ui->cellWeight58;
    pesoCelulas[58] = ui->cellWeight59;
    pesoCelulas[59] = ui->cellWeight60;
    pesoCelulas[60] = ui->cellWeight61;
    pesoCelulas[61] = ui->cellWeight62;*/

}

void RhythmicSetupForm::textLabelToArray()
{
    /* Turns the labels into an array for
     * further manipulation. */

    porcentagemCelulas[0] = ui->labelCell0;
    porcentagemCelulas[1] = ui->labelCell1;
    porcentagemCelulas[2] = ui->labelCell2;
    porcentagemCelulas[3] = ui->labelCell3;
    porcentagemCelulas[4] = ui->labelCell4;
    porcentagemCelulas[5] = ui->labelCell5;
    porcentagemCelulas[6] = ui->labelCell6;
    porcentagemCelulas[7] = ui->labelCell7;
    porcentagemCelulas[8] = ui->labelCell8;
    porcentagemCelulas[9] = ui->labelCell9;
    porcentagemCelulas[10] = ui->labelCell10;
    porcentagemCelulas[11] = ui->labelCell11;
    porcentagemCelulas[12] = ui->labelCell12;
    porcentagemCelulas[13] = ui->labelCell13;
    porcentagemCelulas[14] = ui->labelCell14;
    porcentagemCelulas[15] = ui->labelCell15;
    porcentagemCelulas[16] = ui->labelCell16;
    porcentagemCelulas[17] = ui->labelCell17;
    porcentagemCelulas[18] = ui->labelCell18;
    porcentagemCelulas[19] = ui->labelCell19;
    porcentagemCelulas[20] = ui->labelCell20;
    porcentagemCelulas[21] = ui->labelCell21;
    porcentagemCelulas[22] = ui->labelCell22;
    porcentagemCelulas[23] = ui->labelCell23;
    porcentagemCelulas[24] = ui->labelCell24;
    porcentagemCelulas[25] = ui->labelCell25;
    porcentagemCelulas[26] = ui->labelCell26;
    porcentagemCelulas[27] = ui->labelCell27;
    porcentagemCelulas[28] = ui->labelCell28;
    porcentagemCelulas[29] = ui->labelCell29;
    porcentagemCelulas[30] = ui->labelCell30;
    porcentagemCelulas[31] = ui->labelCell31;
    porcentagemCelulas[32] = ui->labelCell32;
    porcentagemCelulas[33] = ui->labelCell33;
    porcentagemCelulas[34] = ui->labelCell34;
    porcentagemCelulas[35] = ui->labelCell35;
    porcentagemCelulas[36] = ui->labelCell36;
    porcentagemCelulas[37] = ui->labelCell37;
    porcentagemCelulas[38] = ui->labelCell38;
    porcentagemCelulas[39] = ui->labelCell39;
    porcentagemCelulas[40] = ui->labelCell40;
    porcentagemCelulas[41] = ui->labelCell41;
    porcentagemCelulas[42] = ui->labelCell42;
    porcentagemCelulas[43] = ui->labelCell43;
    porcentagemCelulas[44] = ui->labelCell44;
    porcentagemCelulas[45] = ui->labelCell45;
    porcentagemCelulas[46] = ui->labelCell46;
    porcentagemCelulas[47] = ui->labelCell47;
    porcentagemCelulas[48] = ui->labelCell48;
    porcentagemCelulas[49] = ui->labelCell49;
    porcentagemCelulas[50] = ui->labelCell50;
    porcentagemCelulas[51] = ui->labelCell51;
    porcentagemCelulas[52] = ui->labelCell52;
    porcentagemCelulas[53] = ui->labelCell53;
    porcentagemCelulas[54] = ui->labelCell54;
    porcentagemCelulas[55] = ui->labelCell55;
    porcentagemCelulas[56] = ui->labelCell56;
    porcentagemCelulas[57] = ui->labelCell57;
    porcentagemCelulas[58] = ui->labelCell58;
    porcentagemCelulas[59] = ui->labelCell59;
    porcentagemCelulas[60] = ui->labelCell60;
    porcentagemCelulas[61] = ui->labelCell61;
    porcentagemCelulas[62] = ui->labelCell62;



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







