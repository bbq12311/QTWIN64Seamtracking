﻿#include "weld.h"
#include "ui_weld.h"

Weld::Weld(QWidget *parent) :
    QDockWidget(parent),
    uiWeld(new Ui::weld)
{
    uiWeld->setupUi(this);
    setDefaultParameters();
}

Weld::~Weld()
{
    delete uiWeld;
}

/******************************************************************************
  Function:setDefaultParameters
  Description:设置默认的焊接参数。
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void Weld::setDefaultParameters()
{
    dWeldSpeed=2.0;
    dWireRate=2.0;
    dGasFlow=0.5;
    dWeldVoltage=25.0;
    dWeldCurrent=100.0;


    uiWeld->lineEditWeldSpeed->setText(QString::number(dWeldSpeed));
    uiWeld->lineEditWireRate->setText(QString::number(dWireRate));
    uiWeld->lineEditGasFlow->setText(QString::number(dGasFlow));
    uiWeld->lineEditWeldVoltage->setText(QString::number(dWeldVoltage));
    uiWeld->lineEditWeldCurrent->setText(QString::number(dWeldCurrent));
}

/******************************************************************************
  Function:checkWeldParameters
  Description:检查焊接参数合理性。返回true表示检查通过，返回false表示检查不通过
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
bool Weld::checkWeldParameters()
{
    QString str1,str2,str3,str4,str5,str6;

    str1=uiWeld->lineEditWeldSpeed->text();
    str2=uiWeld->lineEditWireRate->text();
    str3=uiWeld->lineEditGasFlow->text();
    str4=uiWeld->lineEditWeldVoltage->text();
    str5=uiWeld->lineEditWeldCurrent->text();
    str6=uiWeld->lineEditWeldDistance->text();


    dWeldSpeed=str1.toDouble();
    dWireRate=str2.toDouble();
    dGasFlow=str3.toDouble();
    dWeldVoltage=str4.toDouble();
    dWeldCurrent=str5.toDouble();
    dWeldDistance=str6.toDouble();

    //检查
    if(dWeldSpeed==0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("焊接速度格式不正确，请更正！"));
        msgbox.exec();
        return false;
    }

    if(dWireRate==0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("送丝速度格式不正确，请更正！"));
        msgbox.exec();
        return false;
    }

    if(dGasFlow==0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("保护气流量格式不正确，请更正！"));
        msgbox.exec();
        return false;
    }

    if(dWeldVoltage==0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("焊接电压格式不正确，请更正！"));
        msgbox.exec();
        return false;
    }

    if(dWeldCurrent==0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("焊接电流格式不正确，请更正！"));
        msgbox.exec();
        return false;
    }

    if(dWeldDistance==0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("焊接长度格式不正确，请更正！"));
        msgbox.exec();
        return false;
    }

    //经过排查，没有问题，即可保存相关的参数
    wpWeldParameter.dWeldSpeed=dWeldSpeed;
    wpWeldParameter.dWireRate=dWireRate;
    wpWeldParameter.dGasFlow=dGasFlow;
    wpWeldParameter.dWeldVoltage=dWeldVoltage;
    wpWeldParameter.dWeldCurrent=dWeldCurrent;
    wpWeldParameter.dWeldDistance=dWeldDistance;

    spSeamTrackParameter.trackingDistance=dWeldDistance;
    spSeamTrackParameter.trackingVelocity=dWeldSpeed;
    spSeamTrackParameter.trackingDirection=1;

    return true;
}

/******************************************************************************
  Function:on_pushButtonConfirm_clicked
  Description:
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void Weld::on_pushButtonConfirm_clicked()
{
    bool checkResult=checkWeldParameters();

    if(checkResult==true)	//检查通过，emit焊接参数
    {
        emit updateWeldParameters_triggered(wpWeldParameter);
        emit updateSeamTrackParameters_triggerd(spSeamTrackParameter);
        close();
    }
    else if(checkResult==false)
    {
        return;
    }
}

/******************************************************************************
  Function:on_pushButtonCancel_clicked
  Description:退出设置界面
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void Weld::on_pushButtonCancel_clicked()
{
    close();
}
