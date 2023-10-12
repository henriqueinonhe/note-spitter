#include "symmetricclichesform.h"
#include "ui_symmetricclichesform.h"
#include "intro.h"

SymmetricClichesForm::SymmetricClichesForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SymmetricClichesForm)
{
    ui->setupUi(this);

    setFixedSize(size());

    //Validators
    QRegularExpression rx("[A-G]#?b?[0-9]");
    pitchValidator = new QRegularExpressionValidator(rx, this);
    ui->lineEditLimiteSuperior->setValidator(pitchValidator);
    ui->lineEditLimiteInferior->setValidator(pitchValidator);
    ui->lineEditFirstPitch->setValidator(pitchValidator);

    QRegularExpression rx2("(((\\+|\\-)([2-3]|[6-7])(m|M);)|((\\+|\\-)([4-5]|8)(a|J);))+");
    intervalPatternValidator = new QRegularExpressionValidator(rx2, this);
    ui->lineEditPadraoIntervalar->setValidator(intervalPatternValidator);

    cycleNumberValidator = new QIntValidator(1, 1000, this);
    ui->lineEditNumeroCiclos->setValidator(cycleNumberValidator);

    connect(ui->pushButtonOK, SIGNAL(clicked(bool)),
            this, SLOT(runSymmetricCliches()));
    connect(ui->pushButtonCancel, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonCancel, SIGNAL(clicked(bool)),
            this, SLOT(openParent()));

    //Line Edit Connects

    connect(ui->lineEditFirstPitch, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnableOk()));
    connect(ui->lineEditLimiteInferior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnableOk()));
    connect(ui->lineEditLimiteSuperior, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnableOk()));
    connect(ui->lineEditNumeroCiclos, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnableOk()));
    connect(ui->lineEditPadraoIntervalar, SIGNAL(textChanged(QString)),
            this, SLOT(checkEnableOk()));
}

std::vector<int> SymmetricClichesForm::convertIntervalPattern()
{
    /* This routine converts interval pattern line edit's contents
     * to an int vector which is basically a sequence
     * of the intervals within the interval pattern. */

    std::vector<int> _pattern;
    QString _content = ui->lineEditPadraoIntervalar->text();

    /* The pattern is:
     * 1 - Direction of interval (+|-)
     * 2 - "Raw" interval [1-8]
     * 3 - Interval Quality (m-M)
     * 4 - semi-colon as a separator */

    int _index = 0, _sign = 0;
    while(_index < _content.size())
    {
        //1:
        if(_content[_index] == '+') _sign = 1;
        else _sign = -1; /* == -*/
        _index++;

        //2:
        switch(_content[_index].digitValue())
        {
            case 1:
            _pattern.push_back(0);
            break;

            case 2:
            _pattern.push_back(1);
            break;

            case 3:
            _pattern.push_back(3);
            break;

            case 4:
            _pattern.push_back(5);
            break;

            case 5:
            _pattern.push_back(7);
            break;

            case 6:
            _pattern.push_back(8);
            break;

            case 7:
            _pattern.push_back(10);
            break;

            case 8:
            _pattern.push_back(12);
            break;
        }
        _index++;

        //3:
        if(_content[_index] == 'M') _pattern.back()++;
        else if(_content[_index] == 'a') _pattern.back()++;
        else{};
        _index++;

        //4:
        _index++;
        _pattern.back() *= _sign;

    }
    return _pattern;
}

void SymmetricClichesForm::closeEvent(QCloseEvent *event)
{
    openParent();
    event->accept();
}

SymmetricClichesForm::~SymmetricClichesForm()
{
    delete ui;
}

void SymmetricClichesForm::checkEnableOk()
{
    QLabel *_info = ui->labelInfo;

    ui->pushButtonOK->setEnabled(false);
    if(!checkLimitsDefined()) _info->setText("Defina os limites e a primeira nota!");
    else if(!checkPitchLimits()) _info->setText("Limite inferior deve ser menor ou igual ao limite superior!");
    else if(!checkFirstPitch()) _info->setText("A primeira nota precisa estar entre o limite inferior e superior!");
    else if(!checkCycleNumber()) _info->setText("Deve haver ao menos 1 ciclo!");
    else if(!checkIntervalPattern()) _info->setText("O padrão intervalar não está preenchido corretamente!");
    else
    {
        _info->setText("");
        ui->pushButtonOK->setEnabled(true);
    }
}

void SymmetricClichesForm::openParent()
{
    parentWindow->show();
}

bool SymmetricClichesForm::checkLimitsDefined()
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

bool SymmetricClichesForm::checkPitchLimits()
{
    /* Highest pitch must be greater than lowest pitch.
     * First pitch must be within the lowest and highest pitch range. */

    return getLowestPitch() <= getHighestPitch();
}

bool SymmetricClichesForm::checkFirstPitch()
{
    /* The first pitch must be within
     * lowest and highest pitch boundaries. */

    return getLowestPitch() <= getFirstPitch() && getFirstPitch() <= getHighestPitch();
}

bool SymmetricClichesForm::checkCycleNumber()
{
    /* Checks if there is at least one cycle.*/

    QString _s = ui->lineEditNumeroCiclos->text();
    int pos = 0;

    return cycleNumberValidator->validate(_s, pos) == QValidator::Acceptable;
}

bool SymmetricClichesForm::checkIntervalPattern()
{
    /* Checks if the interval pattern field suits
     * the requirements for further processing. */

    QString _s = ui->lineEditPadraoIntervalar->text();
    int pos = 0;

    return intervalPatternValidator->validate(_s, pos) == QValidator::Acceptable;
}

int SymmetricClichesForm::getHighestPitch()
{
    return translatePitch(ui->lineEditLimiteSuperior->text());
}

int SymmetricClichesForm::getLowestPitch()
{
    return translatePitch(ui->lineEditLimiteInferior->text());
}

int SymmetricClichesForm::getFirstPitch()
{
    return translatePitch(ui->lineEditFirstPitch->text());
}

int SymmetricClichesForm::getCycleNumber()
{
    return ui->lineEditNumeroCiclos->text().toInt();
}

int SymmetricClichesForm::translatePitch(const QString &_str)
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

void SymmetricClichesForm::runSymmetricCliches()
{
    instance = new SymmetricCliches(getFirstPitch(),
                                    1,
                                    getLowestPitch(),
                                    getHighestPitch(),
                                    getCycleNumber(),
                                    convertIntervalPattern());
    instance->generateNoteSequence();

    MidiTranslationUnit unit;

    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\ClichesOut.mid");
    unit.setSampleHeaderAddress(":/MyFiles/NEWSAMPLE.mid");
    unit.setPulseNumber(4);
    unit.setPulseMeasure(MEASURE_QUARTER);
    unit.setTimeClock(960);
    unit.translateToMidi(instance->getNoteOutput());
    unit.writeToFile();
}




















