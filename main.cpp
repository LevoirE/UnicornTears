#include "mainwindow.h"
#include <QApplication>
#include "filehelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    FileHelper *fileHelper = new FileHelper;
    QObject::connect(&w, SIGNAL(wantSearch(QString)),
                     fileHelper, SLOT(doSearch(QString)));

    return a.exec();
}
