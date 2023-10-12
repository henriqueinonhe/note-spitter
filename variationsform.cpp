#include "variationsform.h"
#include "ui_variationsform.h"
#include "intro.h"

VariationsForm::VariationsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VariationsForm)
{
    ui->setupUi(this);

    connect(ui->pushButtonCancel, SIGNAL(clicked(bool)),
            this, SLOT(openParent()));
    connect(ui->pushButtonCancel, SIGNAL(clicked(bool)),
            this, SLOT(close()));
    connect(ui->pushButtonOK, SIGNAL(clicked(bool)),
            this, SLOT(runVariations()));

    QRegularExpression rx("[A-G]#?b?[0-9]");
    pitchValidator = new QRegularExpressionValidator(rx, this);
    ui->lineEditLimiteSuperior->setValidator(pitchValidator);
    ui->lineEditLimiteInferior->setValidator(pitchValidator);

    setFixedSize(size());

}

VariationsForm::~VariationsForm()
{
    delete ui;
}

void VariationsForm::openParent()
{
    parentWindow->show();
}

void VariationsForm::runVariations()
{
    MidiTranslationUnit unit;

    unit.setInputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\Symmetric.mid");
    unit.setOutputFileAddress("C:\\Users\\Henrique Inonhe\\Desktop\\SymmetricOut.mid");
    unit.setSampleHeaderAddress(":/MyFiles/NEWSAMPLE.mid");
    unit.readToInput();
    unit.setAttributesFromInput();

    Variations instance;

    std::vector<Note> stream;

    unit.translateToNote(stream);
    instance.setNoteInput(stream);

    instance.setHighestPitch(getHighestPitch());
    instance.setLowestPitch(getLowestPitch());
    instance.setStaticFirstNote(getStatic());
    instance.setAllowedIntervals(getAllowedIntervals());
    instance.generateNoteSequences();
    instance.formatToNoteOutput();

    unit.translateToMidi(instance.getNoteOutput());
    unit.writeToFile();

}

std::array<bool, 13> VariationsForm::getAllowedIntervals()
{
    std::array<bool, 13> _array;
    _array.fill(false);

    _array[0] = ui->checkBox->isChecked();
    _array[1] = ui->checkBox_2->isChecked();
    _array[2] = ui->checkBox_3->isChecked();
    _array[3] = ui->checkBox_4->isChecked();
    _array[4] = ui->checkBox_5->isChecked();
    _array[5] = ui->checkBox_6->isChecked();
    _array[6] = ui->checkBox_7->isChecked();
    _array[7] = ui->checkBox_8->isChecked();
    _array[8] = ui->checkBox_9->isChecked();
    _array[9] = ui->checkBox_10->isChecked();
    _array[10] = ui->checkBox_11->isChecked();
    _array[11] = ui->checkBox_12->isChecked();
    _array[12] = ui->checkBox_13->isChecked();

    return _array;
}

int VariationsForm::translatePitch(const QString &_str)
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

int VariationsForm::getHighestPitch()
{
    return translatePitch(ui->lineEditLimiteSuperior->text());
}

int VariationsForm::getLowestPitch()
{
    return translatePitch(ui->lineEditLimiteInferior->text());
}

bool VariationsForm::getStatic()
{
    return ui->checkBoxStatic->isChecked();
}


