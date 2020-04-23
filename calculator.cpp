#include "calculator.h"
#include "ui_calculator.h"


double inputCalcText = 0.00;
bool divButtonPressed = false;
bool mulButtonPressed = false;
bool subButtonPressed = false;
bool addButtonPressed = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->lineEdit_text->setText(QString::number(inputCalcText));
    QPushButton *numberButtons[10];
    for(int i= 0 ;i < 10; i++){
        QString buttonName = "button_" + QString::number(i);
        numberButtons[i] = Calculator::findChild<QPushButton *>(buttonName);
        connect(numberButtons[i],SIGNAL(released()),this,SLOT(numberPressed()));
    }
    connect(ui->add_button,SIGNAL(released()),this,SLOT(mathOperationPressed()));
    connect(ui->subtract_button,SIGNAL(released()),this,SLOT(mathOperationPressed()));
    connect(ui->multiply_button,SIGNAL(released()),this,SLOT(mathOperationPressed()));
    connect(ui->divide_button,SIGNAL(released()),this,SLOT(mathOperationPressed()));
    connect(ui->sign_button,SIGNAL(released()),this,SLOT(signChangePressed()));
    connect(ui->eqauls_button,SIGNAL(released()),this,SLOT(equalsPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numberPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    QString inputDisplayValue = ui->lineEdit_text->text();
    if((inputDisplayValue.toDouble() == 0) || (inputDisplayValue.toDouble() == 0.00) || (inputDisplayValue.toDouble() == 0.0)){
        ui->lineEdit_text->setText(buttonValue);
    }else{
        QString newValue = inputDisplayValue + buttonValue;
        double doubleNewValue = newValue.toDouble();
        ui->lineEdit_text->setText(QString::number(doubleNewValue,'g',16));
    }

}

void Calculator::mathOperationPressed()
{
    divButtonPressed = false;
    mulButtonPressed = false;
    subButtonPressed = false;
    addButtonPressed = false;
    QString inputTextValue = ui->lineEdit_text->text();
    inputCalcText = inputTextValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString buttonValue = button->text();
    qDebug() << "Button Value: " << buttonValue;
    if(QString::compare(buttonValue,"/",Qt::CaseSensitive) == 0){
        divButtonPressed = true;
    }else if(QString::compare(buttonValue,"*",Qt::CaseSensitive) == 0){
        mulButtonPressed = true;
    }else if (QString::compare(buttonValue,"+",Qt::CaseSensitive) == 0){
        addButtonPressed = true;
    }else{
        subButtonPressed = true;
    }
    ui->lineEdit_text->setText("");
}

void Calculator::equalsPressed()
{
    double result = 0.0;
    QString displayValue = ui->lineEdit_text->text();
    double doubleDisplayValue = displayValue.toDouble();
    if(addButtonPressed || subButtonPressed || mulButtonPressed || divButtonPressed){
        if(addButtonPressed){
            result = inputCalcText + doubleDisplayValue;
        }else if(subButtonPressed){
            result = inputCalcText - doubleDisplayValue;
        }else if(mulButtonPressed){
            result = inputCalcText * doubleDisplayValue;
        }else{
            if((doubleDisplayValue != 0) || (doubleDisplayValue != 0.0) || (doubleDisplayValue != 0.00)){
                result = inputCalcText / doubleDisplayValue;
            }else{
               QMessageBox msgBox;
               msgBox.setText("Value cannot be 0");
               msgBox.exec();
            }
        }
        ui->lineEdit_text->setText(QString::number(result));
    }
}

void Calculator::signChangePressed()
{
    QString inputTextValue = ui->lineEdit_text->text();
    QRegExp reg("[-]?[0-9.]*");
    if(reg.exactMatch(inputTextValue)){
        double doubleInputValue = inputTextValue.toDouble();
        doubleInputValue = -1 * doubleInputValue;
        ui->lineEdit_text->setText(QString::number(doubleInputValue));
    }
}


void Calculator::on_clear_button_clicked()
{
    ui->lineEdit_text->clear();
}
