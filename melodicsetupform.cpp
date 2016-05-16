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
    PesoNotas[0] = ui->spinBoxC;
    PesoNotas[1] = ui->spinBoxDb;
    PesoNotas[2] = ui->spinBoxD;
    PesoNotas[3] = ui->spinBoxEb;
    PesoNotas[4] = ui->spinBoxE;
    PesoNotas[5] = ui->spinBoxF;
    PesoNotas[6] = ui->spinBoxGb;
    PesoNotas[7] = ui->spinBoxG;
    PesoNotas[8] = ui->spinBoxAb;
    PesoNotas[9] = ui->spinBoxA;
    PesoNotas[10] = ui->spinBoxBb;
    PesoNotas[11] = ui->spinBoxB;


    PesoIntervalos[0] = ui->spinBoxUnissono;
    PesoIntervalos[1] = ui->spinBox2m;
    PesoIntervalos[2] = ui->spinBox2M;
    PesoIntervalos[3] = ui->spinBox3m;
    PesoIntervalos[4] = ui->spinBox3M;
    PesoIntervalos[5] = ui->spinBox4J;
    PesoIntervalos[6] = ui->spinBox4aum;
    PesoIntervalos[7] = ui->spinBox5J;
    PesoIntervalos[8] = ui->spinBox6m;
    PesoIntervalos[9] = ui->spinBox6M;
    PesoIntervalos[10] = ui->spinBox7m;
    PesoIntervalos[11] = ui->spinBox7M;
    PesoIntervalos[12] = ui->spinBox8J;
    PesoIntervalos[13] = ui->spinBox9m;
    PesoIntervalos[14] = ui->spinBox9M;
    PesoIntervalos[15] = ui->spinBox10m;
    PesoIntervalos[16] = ui->spinBox10M;
    PesoIntervalos[17] = ui->spinBox11J;
    PesoIntervalos[18] = ui->spinBox11aum;
    PesoIntervalos[19] = ui->spinBox12J;
    PesoIntervalos[20] = ui->spinBox13m;
    PesoIntervalos[21] = ui->spinBox13M;
    PesoIntervalos[22] = ui->spinBox14m;
    PesoIntervalos[23] = ui->spinBox14M;
    PesoIntervalos[24] = ui->spinBox15J;
}


void MelodicSetupForm::setSpinBoxRange()
{
    /* Sets the range of the Spin Boxes. */

    for(int _index = 0; _index < 12; _index++)
    {
        PesoNotas[_index]->setRange(0, 100);
    }
    for(int _index = 0; _index < 25; _index++)
    {
        PesoNotas[_index]->setRange(0, 100);
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
    int pos = 0;

    ui->pushButtonOK->setEnabled(pitchValidator->validate(_s1, pos) == QValidator::Acceptable &&
                                 pitchValidator->validate(_s2, pos) == QValidator::Acceptable &&
                                 translatePitch(_s1) <= translatePitch(_s2));

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

void MelodicSetupForm::showRhythmicSetupForm()
{

}

