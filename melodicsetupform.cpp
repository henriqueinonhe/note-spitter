#include "melodicsetupform.h"
#include "ui_melodicsetupform.h"

MelodicSetupForm::MelodicSetupForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MelodicSetupForm)
{
    ui->setupUi(this);

    //UI Setup Complement
    setFixedSize(size());

    //lineEditLimiteSuperior e lineEditLimiteInferior Validators
    QRegularExpression rx("[A-G]#?b?[0-9]");
    pitchValidator = new QRegularExpressionValidator(rx, this);
    ui->lineEditLimiteSuperior->setValidator(pitchValidator);
    ui->lineEditLimiteInferior->setValidator(pitchValidator);
    ui->lineEditFirstPitch->setValidator(pitchValidator);

    //Assign SpinBox to Arrays
    spinBoxToArray();

    //Set SpinBox Range
    setSpinBoxRange();

    //Assign Labels to Arrays
    textLabelToArray();

    //Settting Initial Percentage
    setInitialPercentage();

    //Connects
    setConnections();


}

MelodicSetupForm::~MelodicSetupForm()
{
    delete ui;
}

void MelodicSetupForm::spinBoxToArray()
{
    pesoNotas[0] = ui->spinBoxC;
    pesoNotas[1] = ui->spinBoxDb;
    pesoNotas[2] = ui->spinBoxD;
    pesoNotas[3] = ui->spinBoxEb;
    pesoNotas[4] = ui->spinBoxE;
    pesoNotas[5] = ui->spinBoxF;
    pesoNotas[6] = ui->spinBoxGb;
    pesoNotas[7] = ui->spinBoxG;
    pesoNotas[8] = ui->spinBoxAb;
    pesoNotas[9] = ui->spinBoxA;
    pesoNotas[10] = ui->spinBoxBb;
    pesoNotas[11] = ui->spinBoxB;


    pesoIntervalos[0] = ui->spinBoxUnissono;
    pesoIntervalos[1] = ui->spinBox2m;
    pesoIntervalos[2] = ui->spinBox2M;
    pesoIntervalos[3] = ui->spinBox3m;
    pesoIntervalos[4] = ui->spinBox3M;
    pesoIntervalos[5] = ui->spinBox4J;
    pesoIntervalos[6] = ui->spinBox4aum;
    pesoIntervalos[7] = ui->spinBox5J;
    pesoIntervalos[8] = ui->spinBox6m;
    pesoIntervalos[9] = ui->spinBox6M;
    pesoIntervalos[10] = ui->spinBox7m;
    pesoIntervalos[11] = ui->spinBox7M;
    pesoIntervalos[12] = ui->spinBox8J;
    pesoIntervalos[13] = ui->spinBox9m;
    pesoIntervalos[14] = ui->spinBox9M;
    pesoIntervalos[15] = ui->spinBox10m;
    pesoIntervalos[16] = ui->spinBox10M;
    pesoIntervalos[17] = ui->spinBox11J;
    pesoIntervalos[18] = ui->spinBox11aum;
    pesoIntervalos[19] = ui->spinBox12J;
    pesoIntervalos[20] = ui->spinBox13m;
    pesoIntervalos[21] = ui->spinBox13M;
    pesoIntervalos[22] = ui->spinBox14m;
    pesoIntervalos[23] = ui->spinBox14M;
    pesoIntervalos[24] = ui->spinBox15J;
}

void MelodicSetupForm::setSpinBoxRange()
{
    /* Sets the range of the Spin Boxes. */

    for(int _index = 0; _index < 12; _index++)
    {
        pesoNotas[_index]->setRange(0, 100);
    }
    for(int _index = 0; _index < 25; _index++)
    {
        pesoNotas[_index]->setRange(0, 100);
    }
}

void MelodicSetupForm::textLabelToArray()
{
    porcentagemNotas[0] = ui->labelC;
    porcentagemNotas[1] = ui->labelDb;
    porcentagemNotas[2] = ui->labelD;
    porcentagemNotas[3] = ui->labelEb;
    porcentagemNotas[4] = ui->labelE;
    porcentagemNotas[5] = ui->labelF;
    porcentagemNotas[6] = ui->labelGb;
    porcentagemNotas[7] = ui->labelG;
    porcentagemNotas[8] = ui->labelAb;
    porcentagemNotas[9] = ui->labelA;
    porcentagemNotas[10] = ui->labelBb;
    porcentagemNotas[11] = ui->labelB;


    porcentagemIntervalos[0] = ui->labelUnissono;
    porcentagemIntervalos[1] = ui->label2m;
    porcentagemIntervalos[2] = ui->label2M;
    porcentagemIntervalos[3] = ui->label3m;
    porcentagemIntervalos[4] = ui->label3M;
    porcentagemIntervalos[5] = ui->label4J;
    porcentagemIntervalos[6] = ui->label4aum;
    porcentagemIntervalos[7] = ui->label5J;
    porcentagemIntervalos[8] = ui->label6m;
    porcentagemIntervalos[9] = ui->label6M;
    porcentagemIntervalos[10] = ui->label7m;
    porcentagemIntervalos[11] = ui->label7M;
    porcentagemIntervalos[12] = ui->label8J;
    porcentagemIntervalos[13] = ui->label9m;
    porcentagemIntervalos[14] = ui->label9M;
    porcentagemIntervalos[15] = ui->label10m;
    porcentagemIntervalos[16] = ui->label10M;
    porcentagemIntervalos[17] = ui->label11J;
    porcentagemIntervalos[18] = ui->label11aum;
    porcentagemIntervalos[19] = ui->label12J;
    porcentagemIntervalos[20] = ui->label13m;
    porcentagemIntervalos[21] = ui->label13M;
    porcentagemIntervalos[22] = ui->label14m;
    porcentagemIntervalos[23] = ui->label14M;
    porcentagemIntervalos[24] = ui->label15J;
}

void MelodicSetupForm::setConnections()
{
    /* Setup the connections. */

    connect(ui->lineEditLimiteSuperior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->lineEditLimiteInferior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->lineEditFirstPitch, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->pushButtonCancel, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonOK, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonOK, SIGNAL(clicked(bool)),
            this, SLOT(showRhythmicSetupForm()));

    /* Percentage update connections. */

    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
        connect(pesoNotas[_index], SIGNAL(valueChanged(int)),
                this, SIGNAL(propagatePercentageChange()));
    }

    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        connect(pesoIntervalos[_index], SIGNAL(valueChanged(int)),
                this, SIGNAL(propagatePercentageChange()));
    }

    connect(this, SIGNAL(propagatePercentageChange()),
            this, SLOT(updatePercentage()));

    /* Info Text Update Connections. */

    connect(ui->lineEditFirstPitch, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->lineEditLimiteInferior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->lineEditLimiteSuperior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->checkBoxNoLoop, SIGNAL(stateChanged(int)),
            this, SLOT(checkEnablePushButtonOK()));
    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
        connect(pesoNotas[_index], SIGNAL(valueChanged(int)),
                this, SLOT(checkEnablePushButtonOK()));
    }

    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        connect(pesoIntervalos[_index], SIGNAL(valueChanged(int)),
                this, SLOT(checkEnablePushButtonOK()));
    }
}

void MelodicSetupForm::checkEnablePushButtonOK()
{
    /* Enables pushButtonOK if allowed. */

    QLabel *_info = ui->labelInfo;

    if(!checkLimitsDefined()) _info->setText("Defina os limites e a primeira nota!");
    else if(!checkPitchLimits()) _info->setText("Limite inferior deve ser menor ou igual ao limite superior!");
    else if(!checkFirstPitch()) _info->setText("A primeira nota precisa estar entre o limite inferior e superior!");
    else if(!checkAvailableNotes()) _info->setText("Número de notas permitidas é insuficiente!");
    else if(!checkAvailableIntervals()) _info->setText("Número de intervalos permitidos é insuficiente!");
    else if(!checkIntervalsLimitsConformity()) _info->setText("O maior intervalo permitido deve ser menor que a diferença entre os limites inferior e superior!");
    else if(!checkIntervalsPitchConformity()) _info->setText("Esta configuração não é possível!");
    else
    {
        _info->setText("");
        ui->pushButtonOK->setEnabled(true);
    }
}

bool MelodicSetupForm::checkPitchLimits()
{
    /* Highest pitch must be greater than lowest pitch.
     * First pitch must be within the lowest and highest pitch range. */

    return getLowestPitch() <= getHighestPitch();
}

bool MelodicSetupForm::checkAvailableNotes()
{
    /* There must be at least one note available
     * and if noLoop is checked there must be at
     * least two notes available. */

    int _availablePitchCounter = 0;

    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
        if(pesoNotas[_index]->value() > 0) _availablePitchCounter++;
    }

    if(!getNoLoop()) return _availablePitchCounter > 0;
    else return _availablePitchCounter > 1;
}

bool MelodicSetupForm::checkAvailableIntervals()
{
    /* There must be at least one interval available
     * and if noLoop is checked there must be
     * at least two intervals available.
     * Also intervals available. */

    int _availableIntervalCounter = 0;

    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        if(pesoIntervalos[_index]->value() > 0) _availableIntervalCounter++;
    }

    if(!getNoLoop()) return _availableIntervalCounter > 0;
    else return _availableIntervalCounter > 1;
}

bool MelodicSetupForm::checkFirstPitch()
{
    /* The first pitch must be within
     * lowest and highest pitch boundaries. */

    return getLowestPitch() <= getFirstPitch() && getFirstPitch() <= getHighestPitch();
}

bool MelodicSetupForm::checkLimitsDefined()
{
    /* The limits and the first pitch must be well
     * defined and validated. */

    QString _s1 = ui->lineEditLimiteInferior->text(), _s2 = ui->lineEditLimiteSuperior->text();
    QString _s3 = ui->lineEditFirstPitch->text();
    int pos = 0;

    return pitchValidator->validate(_s1, pos) == QValidator::Acceptable &&
           pitchValidator->validate(_s2, pos) == QValidator::Acceptable &&
           pitchValidator->validate(_s3, pos) == QValidator::Acceptable;
}

bool MelodicSetupForm::checkIntervalsLimitsConformity()
{
    /* The greatest interval must be less or equal
     * to the difference of the highest pitch to the
     * lowest pitch. */

    int _greatestInterval = 0;

    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        if(pesoIntervalos[_index]->value() > 0) _greatestInterval = _index;
    }

    return _greatestInterval <= (getHighestPitch() - getLowestPitch());
}

bool MelodicSetupForm::checkIntervalsPitchConformity()
{
    /* This is a very complex algorithm.
     * It checks if it's possible to build
     * the composition without getting stuck.
     * If the noLoop option if off this check
     * procedure is very simple, checking the
     * first pitch only suffices.
     * Otherwise the checking process becomes
     * more complicated. */

    if(!getNoLoop())
    {
        /* If noLoop is off there must be at least one possible
         * "move" from the first pitch. */
        for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
        {
            if(pesoIntervalos[_index]->value() > 0 &&
              ( (isWithinLimits(getFirstPitch() + _index) && isAvailableNote(getFirstPitch() + _index) ) ||
              (isWithinLimits(getFirstPitch() - _index) && isAvailableNote(getFirstPitch() - _index) ) ) )
               return true;
        }
    }
    else
    {
        /* If noLoop is on we must check every single pitch,
         * moreover there must be at least two possible moves
         * from each pitch. */

        int _availableCounter = 0;
        for(int _pitch = getLowestPitch(); _pitch <= getHighestPitch(); _pitch++)
        {
            for(int _index = 0; _index < MelodicSetup::intervalsTotal && _availableCounter != 2; _index++)
            {
                if(pesoIntervalos[_index]->value() > 0 &&
                   isWithinLimits(_pitch + _index) &&
                   isAvailableNote(_pitch + _index)) _availableCounter++;
                if(pesoIntervalos[_index]->value() > 0 &&
                   isWithinLimits(_pitch - _index) &&
                   isAvailableNote(_pitch - _index)) _availableCounter++;
            }
            if(_availableCounter < 2) return false;
            else _availableCounter = 0;
        }
        return true;
    }
    return false;
}

bool MelodicSetupForm::isWithinLimits(const int _pitch)
{
    /* Checks if the given pitch index is within limits
     * (lowest and highest pitches). */

    return getLowestPitch() <= _pitch && _pitch <= getHighestPitch();
}

bool MelodicSetupForm::isAvailableNote(const int _pitch)
{
    /* Checks if the given pitch is an available note. */

    return pesoNotas[_pitch % 12]->value() > 0;
}

int MelodicSetupForm::translatePitch(const QString &_str)
{
    /* Translates the pitch (absolute) from the line
     * edits. */

    int _ans = 0;
    if(_str.at(0) == 'C') _ans = 0;
    else if(_str.at(0) == 'D') _ans = 2;
    else if(_str.at(0) == 'E') _ans = 4;
    else if(_str.at(0) == 'F') _ans = 5;
    else if(_str.at(0) == 'G') _ans = 7;
    else if(_str.at(0) == 'A') _ans = 9;
    else if(_str.at(0) == 'B') _ans = 11;

    /* There always will be a letter in the zero'th element
     * of the string, so if the first element holds a digit
     * it means that the note is natural, therefore not sharp
     * nor flat.
     * If there isn't a digit in the first element it means
     * the note is sharp or flat, with no third option.
     * So if it is not sharp it is flat. */
    if(_str.at(1).isDigit()) _ans += _str.at(1).digitValue()*12;
    else
    {
        _ans +=  _str.at(1) == '#' ? 1 : -1;
        _ans += _str.at(2).digitValue()*12;
    }


    return _ans;
}

std::array<int, MelodicSetup::notesTotal> MelodicSetupForm::getPesoNotas()
{
    /* Returns the array needed to setup the melody */
    std::array<int, MelodicSetup::notesTotal> _array;

    for(unsigned int _index = 0; _index < MelodicSetup::notesTotal; _index ++)
    {
        _array[_index] = pesoNotas[_index]->value();
    }

    return _array;
}

std::array<int, MelodicSetup::intervalsTotal> MelodicSetupForm::getPesoIntervalos()
{
    /* Returns the array needed to setup the melody */
    std::array<int, MelodicSetup::intervalsTotal> _array;

    for(unsigned int _index = 0; _index < MelodicSetup::intervalsTotal; _index ++)
    {
        _array[_index] = pesoIntervalos[_index]->value();
    }

    return _array;
}

int MelodicSetupForm::getHighestPitch()
{
    return translatePitch(ui->lineEditLimiteSuperior->text());
}

int MelodicSetupForm::getLowestPitch()
{
    return translatePitch(ui->lineEditLimiteInferior->text());
}

int MelodicSetupForm::getFirstPitch()
{
    return translatePitch(ui->lineEditFirstPitch->text());
}

bool MelodicSetupForm::getNoLoop()
{
    return ui->checkBoxNoLoop->isChecked();
}

void MelodicSetupForm::showRhythmicSetupForm()
{
    /* Sending to Data Hold. */
    hold.highestPitch = getHighestPitch();
    hold.lowestPitch = getLowestPitch();
    hold.firstPitch = getFirstPitch();
    hold.notesWeight = getPesoNotas();
    hold.intervalsWeight = getPesoIntervalos();
    hold.noLoop = getNoLoop();

    rhythmicSetupWindow.show();
}

void MelodicSetupForm::updatePercentage()
{
    /* This updates the percentage regarding
     * notesWeight and intervalsWeight, this is
     * simple weighted mean. */

    int _totalNotesWeight = 0, _totalIntervalsWeight = 0;

    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
        _totalNotesWeight += pesoNotas[_index]->value();
    }

    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        _totalIntervalsWeight += pesoIntervalos[_index]->value();
    }

    /* Now the we have the total weight we just have
     * to divide each individual's weight by the total
     * so we have the chance of each one appearing.
     * We also append the percentage symbol.
     * We have to take care of arithmethic exceptions (division by 0)
     * in case all spinBoxes are set to 0. */

    if(_totalNotesWeight != 0)
    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
       porcentagemNotas[_index]->setNum(100*pesoNotas[_index]->value() / _totalNotesWeight);
       porcentagemNotas[_index]->setText(porcentagemNotas[_index]->text().append("%"));
    }
    else
    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
       porcentagemNotas[_index]->setNum(0);
       porcentagemNotas[_index]->setText(porcentagemNotas[_index]->text().append("%"));
    }

    if(_totalIntervalsWeight != 0)
    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        porcentagemIntervalos[_index]->setNum(100*pesoIntervalos[_index]->value() / _totalIntervalsWeight);
        porcentagemIntervalos[_index]->setText(porcentagemIntervalos[_index]->text().append("%"));
    }
    else
    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
       porcentagemIntervalos[_index]->setNum(0);
       porcentagemIntervalos[_index]->setText(porcentagemIntervalos[_index]->text().append("%"));
    }

}

void MelodicSetupForm::setInitialPercentage()
{
    /* Sets to 0 the initial percentage of
     * notesWeight and intervalsWeight. */

    for(int _index = 0; _index < MelodicSetup::notesTotal; _index++)
    {
        porcentagemNotas[_index]->setText("0%");
    }

    for(int _index = 0; _index < MelodicSetup::intervalsTotal; _index++)
    {
        porcentagemIntervalos[_index]->setText("0%");
    }
}






