#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QColorDialog>
#include <QComboBox>
#include <QLabel>
#include <QColor>
#include "canvas.h"
#include "enums.h"
#include "canvaswidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() {}

private:
    Canvas canvas;
    CanvasWidget* canvasWidget;
    Mode mode = Mode::SELECT;
    FigureType figureType = FigureType::RECTANGLE;
    QColor currentColor = Qt::black;
    QButtonGroup* modeGroup;
    QButtonGroup* figureGroup;
    QPushButton* selectModeBtn;
    QPushButton* paintModeBtn;
    QPushButton* rectBtn;
    QPushButton* ellipseBtn;
    QPushButton *colorButton;
    QPushButton *triangBtn;
    QPushButton *aboutButton;
    QSlider *sizeSlider;
    QHBoxLayout* makeModeLayout();
    QHBoxLayout* makeFigureChangeLayout();

private slots:
    void onModeChanged(int id);
    void onFigureTypeChanged(int id);
    void onColorChange();
    void showAbout();
};



#endif // MAINWINDOW_H
