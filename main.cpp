
#include "mainwindow.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    mw.show();

    return a.exec();
}
