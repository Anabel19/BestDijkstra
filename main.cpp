#include "mainwindow.h"
#include <QApplication>

CBigGraph::Node* FINAL;
CBigGraph::Node* ACTUAL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w = new MainWindow();
    w->show();

    return a.exec();
}

