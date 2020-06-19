#ifndef SIMPLECALIBRATION_H
#define SIMPLECALIBRATION_H

#include <QDockWidget>
#include <QMessageBox>

namespace Ui {
class simplecalibration;
}

class SimpleCalibration : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleCalibration(QWidget *parent = nullptr);
    ~SimpleCalibration();

private:
    Ui::simplecalibration *uiSimplecalibration;
    double dHorizontalCalibrationRatio;
    double dBlockWidthPixel;
    double dBlockWidthmm;

    void setDefaultConfiguration();
private slots:
    void on_pushButtonCalculate_clicked();
    void on_pushButtonGetBlockWidthPixel_clicked();
    void on_pushButtonQuit_clicked();
    void receiveBlockWidthPixel(double blockWidth);
signals:
    void updateHorizontalCalibrationRatio_triggered(double horizontalCalibrationRatio);
    void updateCalibrationState_triggered();
    void getBlockWidthPixel_triggered();
};

#endif // SIMPLECALIBRATION_H
