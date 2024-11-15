
#include "mainwindow.h"

#include <QApplication>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mw;
    mw.show();
    if(argc > 1)
    {
        std::string path = std::string(argv[1]);
        mw.handlePath(path);
    }

    return a.exec();
}
