#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtCore>
#include <QtGui>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void numberPressed();
    void mathOperationPressed();
    void equalsPressed();
    void signChangePressed();

    void on_clear_button_clicked();

private:
    Ui::Calculator *ui;
};
#endif // CALCULATOR_H
