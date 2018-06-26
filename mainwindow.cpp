#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent) : QWidget(parent){
    graphShow = new CGraphShow(this);
    graphShow->generateGraph();
    graphShow->printGraph();
}

MainWindow::~MainWindow()
{
    delete graphShow;
}


