#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator w;
    w.setFixedSize(425,275);
    w.setWindowTitle("Calc");
    w.show();
    return a.exec();
}
