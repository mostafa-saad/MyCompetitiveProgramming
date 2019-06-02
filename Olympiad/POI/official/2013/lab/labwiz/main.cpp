/* Labirynt, wizualizacja wyjścia
  Maciej Borsz
  2012
 */


#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("Olimpiada Informatyczna");
    a.setOrganizationDomain("oi.edu.pl");
    a.setApplicationName("Labwiz");
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    MainWindow w;
    w.show();
    QStringList args = a.arguments();
    if (args.length() > 1) {
        w.read(args.last());
    }
    
    return a.exec();
}
