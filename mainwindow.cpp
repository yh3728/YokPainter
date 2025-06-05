#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "canvas.h"
#include "canvaswidget.h"
#include "figure.h"

#include <QMouseEvent>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    canvas.addFigure(new RectFigure(QPoint(295, 354), QPoint(522, 406)));
    CanvasWidget* widget = new CanvasWidget(&canvas);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    std::cout<<event->position().x()<<' ' <<event->position().y()<<std::endl;
}
