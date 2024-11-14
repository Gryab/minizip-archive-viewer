
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
    #ifdef WIN32
    // Gryab: small hack, req for absolute path resolution
        std::string path = "/" + std::string(argv[1]);
    #else
        std::string path = std::string(argv[1]);
    #endif
        mw.handlePath(path);
    }

    return a.exec();
}
