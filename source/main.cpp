#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(([](){
        QFile file(":/qdarkstyle/light/lightstyle.css")        ;
                        QTextStream stream (&file);\
                            if (file.open(QIODevice::ReadOnly))
        return stream.readAll();
                            return QString{};
                     })());
    MainWindow w;
    w.show();
    return a.exec();
}
