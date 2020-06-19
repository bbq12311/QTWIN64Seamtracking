#ifndef MANUAL_H
#define MANUAL_H

#include <QDockWidget>
#include <motion.h>
#include <QCloseEvent>

namespace Ui {
class manual;
}

class Manual : public QDockWidget
{
    Q_OBJECT

public:
    explicit Manual(QWidget *parent = nullptr);
    ~Manual();

private:
   Ui::manual *uiManual;
   Motion* manualMotionObject;
private:
    //*******参数********//
    int rotationDirectionA;		//转向选择：1正向，0负向
    int motionModeA;			//运动模式. 1-连续模式；2-定长模式
    double moveDistanceA;		//移动距离	单位脉冲数（暂定）
    double maxSpeedA;			//最高速度	单位脉冲频率（暂定）


    bool checkPass;				//检测，如果是1表示通过，0表示不通过


    void initializeParameters();
    void fillDefaultParamters();
    void updateParameters();
    void closeEvent(QCloseEvent* e);
private slots:
    void on_pushButtonReturnOrigin_clicked();
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonQuit_clicked();
    void on_radioButtonCW_toggled();
    void on_radioButtonCCW_toggled();
    void on_radioButtonCntnsMode_toggled();
    void on_radioButtonFixedMode_toggled();
signals:
    void xRun(double maxVec, int dir);
    void xMove(double maxVec,int dir,double distance);
    void xStop();
    void xReturnOrigin();
    void disableManualMode();

};

#endif // MANUAL_H
