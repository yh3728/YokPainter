#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "canvas.h"
#include "canvaswidget.h"
#include "figure.h"
#include "affine_transform.h"

#include <iostream>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QColor>
#include <QColorDialog>
#include <QComboBox>
#include <QLabel>
#include <QMessageBox>
#include "enums.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *window = new QWidget;
    canvasWidget = new CanvasWidget(&canvas);
    setMinimumSize(600, 600);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *toolsLayout = new QHBoxLayout();
    toolsLayout->addLayout(makeModeLayout());
    toolsLayout->addSpacing(20);
    toolsLayout->addLayout(makeFigureChangeLayout());
    toolsLayout->addSpacing(20);
    colorButton = new QPushButton("Выбрать цвет");
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::onColorChange);
    sizeSlider = new QSlider(Qt::Horizontal);
    sizeSlider->setRange(1, 30);
    sizeSlider->setValue(10);
    connect(sizeSlider, &QSlider::valueChanged, [this](int value) {
        canvasWidget->setSelectedFigSize(value/10.0);
    });

    toolsLayout->addWidget(colorButton);
    toolsLayout->addSpacing(20);
    toolsLayout->addWidget(sizeSlider);
    aboutButton = new QPushButton("Помощь");
    connect(aboutButton, &QPushButton::clicked, this, &MainWindow::showAbout);
    toolsLayout->addWidget(aboutButton);
    mainLayout->addLayout(toolsLayout);
    mainLayout->addWidget(canvasWidget);
    window->setLayout(mainLayout);
    setCentralWidget(window);
}

void MainWindow::onModeChanged(int id) {
    Mode currentMode;
    if (id == 0) {
        currentMode = Mode::SELECT;
        rectBtn->setCheckable(false);
        ellipseBtn->setCheckable(false);
        triangBtn->setCheckable(false);
    } else {
        currentMode = Mode::PAINT;
        rectBtn->setCheckable(true);
        ellipseBtn->setCheckable(true);
        triangBtn->setCheckable(true);
    }
    canvasWidget->setMode(currentMode);
}

QHBoxLayout* MainWindow::makeModeLayout(){
    QHBoxLayout *toolsLayout = new QHBoxLayout();

    modeGroup = new QButtonGroup(this);
    modeGroup->setExclusive(true);

    selectModeBtn = new QPushButton("Выделение");
    paintModeBtn = new QPushButton("Рисование");

    selectModeBtn->setCheckable(true);
    paintModeBtn->setCheckable(true);
    selectModeBtn->setChecked(true);

    modeGroup->addButton(selectModeBtn, 0);
    modeGroup->addButton(paintModeBtn, 1);

    connect(modeGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &MainWindow::onModeChanged);

    toolsLayout->addWidget(selectModeBtn);
    toolsLayout->addWidget(paintModeBtn);
    return(toolsLayout);
}

QHBoxLayout* MainWindow::makeFigureChangeLayout(){
    QHBoxLayout *figuresLayout = new QHBoxLayout();

    figureGroup = new QButtonGroup(this);
    figureGroup->setExclusive(true);

    rectBtn = new QPushButton("▯");
    ellipseBtn = new QPushButton("⬭");
    triangBtn = new QPushButton("△");

    rectBtn->setChecked(true);

    figureGroup->addButton(rectBtn, 0);
    figureGroup->addButton(ellipseBtn, 1);
    figureGroup->addButton(triangBtn, 2);

    connect(figureGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &MainWindow::onFigureTypeChanged);

    figuresLayout->addWidget(rectBtn);
    figuresLayout->addWidget(ellipseBtn);
    figuresLayout->addWidget(triangBtn);

    return figuresLayout;
}

void MainWindow::onFigureTypeChanged(int id){
    FigureType currentType;
    switch(id){
        case 0:
            currentType = FigureType::RECTANGLE;
            break;
        case 1:
            currentType = FigureType::CIRCLE;
            break;
        case 2:
            currentType = FigureType::TRIANGLE;
            break;
        default:
            currentType = FigureType::RECTANGLE;
    }
    canvasWidget->setFigType(currentType);
}

void MainWindow::onColorChange(){
    QColor color = QColorDialog::getColor(currentColor, this, "Выберите цвет");
    if (color.isValid()){
        canvasWidget->setColor(color);
        currentColor = color;
    }
}

void MainWindow::showAbout(){
    QMessageBox::about(this, "О программе YokPainter",
                       "<h3>YokPainter 2.0</h3>"
                       "<p>Простой графический редактор для рисования фигур.</p>"
                       "<p><b>Возможности:</b></p>"
                       "<ul>"
                       "<li>Рисование простых геометрических фигур</li>"
                       "<li>Выбор цвета фигур</li>"
                       "<li>Изменение размера фигур</li>"
                       "<li>Перемещение и поворот фигур</li>"
                       "</ul>"
                       "<p><b>Управление:</b></p>"
                       "<ul>"
                       "<li>ЛКМ - выделение/рисование фигуры</li>"
                       "<li>Зажать ПКМ - перемещение(если курсор внутри) и поворот(если курсор снаружи)</li>"
                       "<li>Слайдер для управления размерами выделенной фигуры</li>"
                       "</ul>");
}
