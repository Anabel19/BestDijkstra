#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "graphshow.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    public:
        CGraphShow * graphShow;
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
};

#endif // MAINWINDOW_H
