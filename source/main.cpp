#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <qicon.h>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon{":/res/co2.ico"});
    a.setStyleSheet((
        []()
        {
            QFile file(":/res/lightstyle.css");
            QTextStream stream(&file);
            if (file.open(QIODevice::ReadOnly))
                return stream.readAll();
            return QString {};
        })());
    MainWindow w;
    w.show();
    return a.exec();
}
