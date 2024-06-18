#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->calcParamsCB, &QComboBox::currentIndexChanged, this, &MainWindow::UnableOtherParams);
    connect(ui->stepCalcButton, &QPushButton::clicked, this, &MainWindow::RecalcSteps);
    connect(ui->plotButton, &QPushButton::clicked, this, &MainWindow::RedrawClick);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UnableOtherParams()
{

    ui->stepPupilKedLine->setEnabled(false);
    ui->stepImgKedLine->setEnabled(false);
    ui->stepImgMkmLine->setEnabled(false);
    ui->stepObjKedLine->setEnabled(false);
    ui->stepObjMkmLine->setEnabled(false);
    ui->pupilSizeKedLine->setEnabled(false);

    QString currentParam = ui->calcParamsCB->currentText();
    if(currentParam == "Охват зрачка [к.ед.]")
    {
        ui->pupilSizeKedLine->setEnabled(true);
    }
    else if(currentParam == "Шаг по зрачку [к.ед.]")
    {
        ui->stepPupilKedLine->setEnabled(true);
    }
    else if(currentParam == "Шаг по предмету [к.ед.]")
    {
        ui->stepObjKedLine->setEnabled(true);
    }
    else if(currentParam == "Шаг по изображению [к.ед]")
    {
        ui->stepImgKedLine->setEnabled(true);
    }
}

void MainWindow::RecalcSteps()
{
    prms.Size = ui->sizeCB->currentText().toInt();
    prms.Lamda = ui->waveLengthLine->text().toDouble();
    prms.Aperture_ = ui->rearApertureLine->text().toDouble();
    prms.V = ui->zoomLine->text().toDouble();
    prms.C20 = ui->defocusLine->text().toDouble();
    prms.C22 = ui->astigmatismLine->text().toDouble();
    if(prms.Lamda <= 0 || prms.Aperture_ == 0)
    {
        qDebug() << "error in optic params";
        return;
    }

    prms.Aperture = prms.Aperture_ * prms.V;
    int flag;
    if(ui->calcParamsCB->currentText() == "Охват зрачка [к.ед.]")
    {
        if (ui->pupilSizeKedLine->text().toDouble() <= 0)
        {
            qDebug() << "error in pupil size param";
            return;
        }
        prms.PupilD = ui->pupilSizeKedLine->text().toDouble();
        prms.StepPupil = prms.PupilD/prms.Size;
        prms.StepOb = 1/(prms.Size * prms.StepPupil);
        prms.StepObMkm = prms.StepOb * prms.Lamda/prms.Aperture;
        prms.StepImMkm = prms.StepOb * prms.Lamda/prms.Aperture_;
    }
    else if(ui->calcParamsCB->currentText() == "Шаг по зрачку [к.ед.]")
    {
        if (ui->stepPupilKedLine->text().toDouble() <= 0)
        {
            qDebug() << "error in pupil step param";
            return;
        }
        prms.StepPupil = ui->stepPupilKedLine->text().toDouble();
        prms.PupilD = prms.StepPupil/prms.Size;
        prms.StepOb = 1/(prms.Size * prms.StepPupil);
        prms.StepObMkm = prms.StepOb * prms.Lamda/prms.Aperture;
        prms.StepImMkm = prms.StepOb * prms.Lamda/prms.Aperture_;
    }
    else if(ui->calcParamsCB->currentText() == "Шаг по предмету [к.ед.]")
    {
        if (ui->stepObjKedLine->text().toDouble() <= 0)
        {
            qDebug() << "error in object step param";
            return;
        }
        prms.StepOb = ui->stepObjKedLine->text().toDouble();
        prms.StepPupil = 1/(prms.Size * prms.StepOb);
        prms.PupilD = prms.StepPupil/prms.Size;
        prms.StepObMkm = prms.StepOb * prms.Lamda/prms.Aperture;
        prms.StepImMkm = prms.StepOb * prms.Lamda/prms.Aperture_;
    }
    else if(ui->calcParamsCB->currentText() == "Шаг по изображению [к.ед]")
    {
        if (ui->stepImgKedLine->text().toDouble() <= 0)
        {
            qDebug() << "error in image step param";
            return;
        }
        prms.StepOb = ui->stepImgKedLine->text().toDouble();
        prms.StepPupil = 1/(prms.Size * prms.StepOb);
        prms.PupilD = prms.StepPupil/prms.Size;
        prms.StepObMkm = prms.StepOb * prms.Lamda/prms.Aperture;
        prms.StepImMkm = prms.StepOb * prms.Lamda/prms.Aperture_;
    }
    ui->stepPupilKedLine->setText(QString::number(prms.StepPupil));
    ui->pupilSizeKedLine->setText(QString::number(prms.PupilD));
    ui->stepObjKedLine->setText(QString::number(prms.StepOb));
    ui->stepObjMkmLine->setText(QString::number(prms.StepObMkm));
    ui->stepImgKedLine->setText(QString::number(prms.StepOb));
    ui->stepImgMkmLine->setText(QString::number(prms.StepImMkm));
}


void MainWindow::RedrawClick()
{
    PSFCalc psfcalc;

    psfcalc.PSF(prms, data);
    if (data.GetSize() == 0)
    {
        qDebug() << "cannot draw due to error in params";
        return;
    }

    double step = 0;
    if (ui->mkmRB->isChecked())
    {
        step = ui->stepImgMkmLine->text().toDouble();
        DrawGraph(data, ui->graph, step, "x, мкм", "Intensity (x)");
        DrawGRS(data, ui->graphGR, step, "x, мкм", "y, мкм");
    }
    if (ui->pxRB->isChecked())
    {
        DrawGraph(data, ui->graph, 1, "x, пкс", "Intensity (x)");
        DrawGRS(data, ui->graphGR, 1, "x, пкс", "y, пкс");
    }
    if (ui->kedRB->isChecked())
    {
        step = ui->stepImgKedLine->text().toDouble();
        DrawGraph(data, ui->graph, step, "x, к.ед", "Intensity (x)");
        DrawGRS(data, ui->graphGR, step, "x, к.ед", "y, к.ед");
    }
}

void MainWindow::DrawGraph(Sample<double>& PSF, QCustomPlot* graph, double dx,
                            QString xName, QString yName)
{
	int dim = PSF.GetSizeX();

	graph->clearGraphs();
	graph->legend->setVisible(true);

	graph->addGraph();
	graph->graph(0)->setPen(QPen(Qt::red));
	graph->graph(0)->setName("Section X");

	graph->addGraph();
	graph->graph(1)->setPen(QPen(Qt::blue));
	graph->graph(1)->setName("Section Y");

	graph->xAxis->setLabel(xName);
	double min = PSF.CalcCoord(0, dx);
	double max = PSF.CalcCoord(dim, dx);
    graph->xAxis->setRange(min, max);

	min = 0, max = 0;
	for (int i = 0; i < PSF.GetSizeX(); i++)
	{
		double x = PSF.CalcCoord(i, dx);

		double value_x = PSF(i, dim / 2);
        graph->graph(0)->addData(x, value_x);

		double value_y = PSF(dim / 2, i);
        graph->graph(1)->addData(x, value_y);

		if (min > value_x)
			min = value_x;
		if (min > value_y)
			min = value_y;

		if (max < value_x)
			max = value_x;
		if (max < value_y)
			max = value_y;
	}
    graph->yAxis->setLabel(yName);
    graph->yAxis->setRange(min, max);
	QPen qAxisPen;
	qAxisPen.setWidth(2.);
    graph->xAxis->grid()->setZeroLinePen(qAxisPen);
    graph->yAxis->grid()->setZeroLinePen(qAxisPen);

    graph->replot();
}

void MainWindow::DrawGRS(Sample<double>& PSF, QCustomPlot* graphGR, double dx,
                         QString xName, QString yName)
{
    int dim = PSF.GetSize();
    graphGR->clearPlottables();
    QCPColorMap* qMap = new QCPColorMap(graphGR->xAxis, graphGR->yAxis);
    qMap->data()->setSize(dim, dim);

    double min = PSF.CalcCoord(0, dx);
    double max = PSF.CalcCoord(dim, dx);
    qMap->data()->setRange(QCPRange(min, max), QCPRange(min, max));

    for (int i = 0; i < PSF.GetSize(); i++)
    {
        for (int j = 0; j < PSF.GetSize(); j++)
        {
            qMap->data()->setCell(i, j, PSF(i, j));
        }
    }

    qMap->setGradient(QCPColorGradient::gpGrayscale);
    qMap->rescaleDataRange();

    graphGR->xAxis->setLabel(xName);
    graphGR->yAxis->setLabel(yName);

    graphGR->rescaleAxes();
    RescaleCustomPlot(graphGR);
    graphGR->replot();
}

void MainWindow::RescaleCustomPlot(QCustomPlot* graph)
{
    QSize graphRect = graph->axisRect()->size();
    if (graphRect.width() > graphRect.height())
        graph->xAxis->setScaleRatio(graph->yAxis, 1.);
    else
        graph->yAxis->setScaleRatio(graph->xAxis, 1.);
}