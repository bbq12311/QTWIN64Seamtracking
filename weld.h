#ifndef WELD_H
#define WELD_H

#include <QDockWidget>
#include <var.h>

namespace Ui {
class weld;
}

class Weld : public QDockWidget
{
    Q_OBJECT

public:
    explicit Weld(QWidget *parent = nullptr);
    ~Weld();

private:
    Ui::weld *uiWeld;
    double dWeldSpeed;
    double dWireRate;
    double dGasFlow;
    double dWeldVoltage;
    double dWeldCurrent;
    double dWeldDistance;
    WeldParameter wpWeldParameter;
    SeamTrackParameter spSeamTrackParameter;


    void setDefaultParameters();
    bool checkWeldParameters();
private slots:
    void on_pushButtonConfirm_clicked();
    void on_pushButtonCancel_clicked();
signals:
    void updateWeldParameters_triggered(WeldParameter parameters);
    void updateSeamTrackParameters_triggerd(SeamTrackParameter parameters);
};

#endif // WELD_H
