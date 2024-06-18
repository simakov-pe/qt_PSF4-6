#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sample.h"
#include "psfparam.h"
#include "psfcalc.h"
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void UnableOtherParams();
    void RecalcSteps();
    void RedrawClick();
    void DrawGraph(Sample<double>& PSF, QCustomPlot* graph, double dx,
        QString xName, QString yName);
    void DrawGRS(Sample<double>& PSF, QCustomPlot* graph, double dx,
        QString xName, QString yName);
    void RescaleCustomPlot(QCustomPlot* graph);
private:
    Ui::MainWindow *ui;
    PSFParam prms;
    Sample<double> data;
};
#endif // MAINWINDOW_H
