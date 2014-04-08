#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator* translator=new QTranslator(0);
    QString local = QLocale::system().name().section('_',0,0);
    qDebug()<<local;
       if(QFile::exists("jeu_"+local+".qm"))
           qWarning("failed-no file");
       if(! translator->load("jeu_"+local+".qm"))
           qWarning("failed loading");
      a.installTranslator(translator);
    MainWindow w;
    w.show();
    return a.exec();
}
