#ifndef PIDCURVE_H
#define PIDCURVE_H

#include <QDockWidget>
#include <qcustomplot.h>
#include <qvector.h>

namespace Ui {
class pidcurve;
}

class pidCurve : public QDockWidget
{
    Q_OBJECT

public:
    explicit pidCurve(QWidget *parent = nullptr);
    ~pidCurve();

    void GraphShow();
    void GetData(double offset);

private:
    Ui::pidcurve *ui;
    QCustomPlot *Plot;
    QVector <double>    XData;
    QVector <double>    YData;

    qint32 Slither_aMax;
    qint32 Slither_aMin;
    int Clk;

private slots:
    void on_pushButtonCW_clicked();

    void on_verticalSliderAMax_sliderMoved(int position);

    void on_horizontalSliderAMin_sliderMoved(int position);

    void ReadData(double offset);
};

#endif // PIDCURVE_H
