#include "pidcurve.h"
#include "ui_pidcurve.h"

pidCurve::pidCurve(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::pidcurve)
{
    ui->setupUi(this);

    ui->verticalSliderAMax->setRange(5,10);
    ui->verticalSliderAMax->setValue(5);
    ui->horizontalSliderAMin->setRange(-10,-5);
    ui->horizontalSliderAMin->setValue(-5);

    XData.resize(50);
       XData.value(0,1);
       YData.resize(50);

       Plot = ui->widget;
       Plot->addGraph();

       Plot->graph(0)->setPen(QPen(Qt::blue));
       Plot->xAxis->setLabel("mS");
       Plot->yAxis->setLabel("mA");

       Plot->yAxis->setRange(-10,10);
       Plot->xAxis->rescale(true);

       Clk=0;

       GraphShow();
}

pidCurve::~pidCurve()
{
    delete ui;
}

void pidCurve::GraphShow()
{
    Plot->graph(0)->setData(XData,YData);
    Plot->yAxis->setRange(Slither_aMin,Slither_aMax);
    Plot->xAxis->rescale(true);
    Plot->replot();
}

void pidCurve::GetData(double offset)
{
    XData.pop_front();
    XData.push_back(Clk++);

    YData.pop_front();
    YData.push_back(offset);
}

void pidCurve::ReadData(double offset)
{
    QString tmp;
    tmp = QString::number(offset,10,5);
    ui->textEdit->append(tmp);
    GetData(offset);
    GraphShow();
}

void pidCurve::on_pushButtonCW_clicked()
{
    ui->textEdit->clear();
    Clk=0;
}


void pidCurve::on_verticalSliderAMax_sliderMoved(int position)
{
    Slither_aMax = position;
}

void pidCurve::on_horizontalSliderAMin_sliderMoved(int position)
{
    Slither_aMin = position;
}
