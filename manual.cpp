#include "manual.h"
#include <ui_manual.h>

Manual::Manual(QWidget *parent) :
    QDockWidget(parent),
    uiManual(new Ui::manual)
{
    uiManual->setupUi(this);
    //manualMotionObject=new Motion;

    initializeParameters();//初始化设置manuanlControl ui相关内容
    fillDefaultParamters();//填充
}

Manual::~Manual()
{
    delete uiManual;
    //delete manualMotionObject;
}

void Manual::closeEvent(QCloseEvent *e)
{
    emit disableManualMode();
    e->accept();
}
/*****************************************************************************
Function:void Manual::_initializeParameters()
Description:初始化默认参数
Input:
Output:
Return:
Others:
*****************************************************************************/
void Manual::initializeParameters()
{
    //**************默认参数设定***************//
    rotationDirectionA = 1;     //默认正向
    motionModeA = 2;			//默认定长运动
    moveDistanceA = 5;		//默认移动距离1mm
    maxSpeedA = 2;		//默认最高速度2mm/s
}


/*****************************************************************************
Function:void Manual::_fillDefaultParamters()
Description:往各种lineEdit里面填充默认参数。
Input:
Output:
Return:
Others:
*****************************************************************************/
void Manual::fillDefaultParamters()
{
    QString str1, str2;

    str1 = QString::number((double)moveDistanceA);
    str2 = QString::number((double)maxSpeedA);


    uiManual->lineEditDistanceSetting->setText(str1);
    uiManual->lineEditHighestSpeedValue->setText(str2);


    uiManual->radioButtonCW->setChecked(true);                  //默认正向旋转
    uiManual->radioButtonFixedMode->setChecked(true);         //默认定长运动
}

/*****************************************************************************
Function:void Manual::on_startPushButton_clicked()
Description:响应手动控制界面对“开始”按钮的点击事件
Input:
Output:
Return:
Others:
*****************************************************************************/
void Manual::on_pushButtonStart_clicked()
{
    updateParameters();			//更新数据，载入各种LineEdit的内容
    if (!checkPass)
    {
        QMessageBox msgBox;
        msgBox.setText(QStringLiteral("参数设置出错，未能开始运动"));
        msgBox.exec();
        return;
    }

    //连续运动
    if (uiManual->radioButtonCntnsMode->isChecked())
    {
        emit xRun(maxSpeedA, rotationDirectionA);
        //manualMotionObject->xRun(maxSpeedA, rotationDirectionA);
        //manualMotionObject->run();
    }

    //定长运动
    if (uiManual->radioButtonFixedMode->isChecked())
    {
        emit xMove(maxSpeedA, rotationDirectionA, moveDistanceA);
       // manualMotionObject->xMove(maxSpeedA, rotationDirectionA, moveDistanceA);
       // manualMotionObject->run();
    }
}

/*****************************************************************************
Function:voidManual::on_stopPushButton_clicked()
Description:响应手动控制界面对“停止”按钮的点击事件
Input:
Output:
Return:
Others:
*****************************************************************************/
void Manual::on_pushButtonStop_clicked()
{
    emit xStop();
    //manualMotionObject->xStop();
}

void Manual::on_pushButtonQuit_clicked()
{
    close();
}

/*****************************************************************************
Function:Manual::on_returnOriginPushButton_clicked()
Description:响应手动控制界面对“返回原点”按钮的点击事件
Input:
Output:
Return:
Others:
*****************************************************************************/
void Manual::on_pushButtonReturnOrigin_clicked()
{
    emit xReturnOrigin();
   // manualMotionObject->returnOrigin();
    //manualMotionObject->run();
}


/*****************************************************************************
Function:void Manual::_updateParameters()
Description:更新运动数据
Input:
Output:
Return:
Others:
*****************************************************************************/
void Manual::updateParameters()
{
    QString str1, str2;
    double temp1, temp2;

    //方向
    if(uiManual->radioButtonCW->isChecked())            rotationDirectionA = 1;//正向
    else if (uiManual->radioButtonCCW->isChecked())    rotationDirectionA = 0;//负向

    //运动模式
    if (uiManual->radioButtonCntnsMode->isChecked())     motionModeA = 1; //连续模式
    else if (uiManual->radioButtonFixedMode->isChecked()) motionModeA = 2;//定长模式


    if (uiManual->lineEditDistanceSetting->isEnabled())
    {
        str1 = uiManual->lineEditDistanceSetting->text();
        temp1 = abs(str1.toDouble());
    }
    else
    {
        str1 = "";
        temp1 = -1;
    }

    str2 = uiManual->lineEditHighestSpeedValue->text();
    temp2 = str2.toDouble();
    if (temp1 == 0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("移动距离输入错误，请更正！"));
        msgbox.exec();
        checkPass = 0; //格式检查不通过
        return;
    }
    if (temp2 == 0.0||temp2<0.0)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("最高速度输入错误，请更正！"));
        msgbox.exec();
        checkPass = 0;		//格式检查不通过
        return;
    }
    moveDistanceA = temp1;
    maxSpeedA = temp2;


    checkPass = 1;//检查通过
}


void Manual::on_radioButtonCntnsMode_toggled()
{
    uiManual->lineEditDistanceSetting->setEnabled(false);
}



void Manual::on_radioButtonFixedMode_toggled()
{
    uiManual->lineEditDistanceSetting->setEnabled(true);
}




void Manual::on_radioButtonCW_toggled()
{
    rotationDirectionA = 1;
}



void Manual::on_radioButtonCCW_toggled()
{
    rotationDirectionA = 0;
}
