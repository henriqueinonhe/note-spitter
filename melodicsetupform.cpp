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

void MelodicSetupForm::setConnections()
{
    /* Setup the connections. */

    connect(ui->lineEditLimiteSuperior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnablePushButtonOK()));
    connect(ui->lineEditLimiteInferior, SIGNAL(textChanged(QString)),
             this, SLOT(checkEnablePushButtonOK()));
    connect(ui->pushButtonCancel, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonOK, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonOK, SIGNAL(clicked(bool)),
            this, SLOT(showRhythmicSetupForm()));
}

void MelodicSetupForm::checkEnablePushButtonOK()
{
    /* Enables pushButtonOK if allowed. */

    QString _s1 = ui->lineEditLimiteInferior->text(), _s2 = ui->lineEditLimiteSuperior->text();
    QString _s3 = ui->lineEditFirstPitch->text();
    int pos = 0;

    ui->pushButtonOK->setEnabled(pitchValidator->validate(_s1, pos) == QValidator::Acceptable &&
                                 pitchValidator->validate(_s2, pos) == QValidator::Acceptable &&
                                 pitchValidator->validate(_s3, pos) == QValidator::Acceptable &&
                                 translatePitch(_s1) <= translatePitch(_s2) &&
                                 translatePitch(_s1) <= translatePitch(_s3) && translatePitch(_s3) <= translatePitch(_s2));

}

int MelodicSetupForm::translatePitch(QString _str)
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

void MelodicSetupForm::showRhythmicSetupForm()
{
    /* Sending to Data Hold. */
    hold.highestPitch = getHighestPitch();
    hold.lowestPitch = getLowestPitch();
    hold.firstPitch = 65; //FIX THIS!
    hold.notesWeight = getPesoNotas();
    hold.intervalsWeight = getPesoIntervalos();
    hold.noLoop = true; //FIX THIS!

    rhythmicSetupWindow.show();
}

