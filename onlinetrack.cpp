#include "onlinetrack.h"

onlinetrack::onlinetrack(QObject *parent)
{

    createSerialPort();
    serialPort2->moveToThread(this);

    isDIPAllowed=false;
    isAutoTrackTriggered=false;
    isTestModeTriggered=false;
    isManualMode=false;

    nthFrame = 0;
    dTorchSensorDistance=60;
    dSensorFrameRate=5;
    intOffsetCount=0;
    intNthPeriod=0;
    dWeldSpeed=2.0;
    intTrackMethod=TRACKMETHOD_REFERENCE;
    dLastPeriodRemain=0.0;
    m_workState=stateXWait;
    dmanualMaxVec=0.0;
    dmanualDistance=0.0;



    timeoutFlag =true;

    connect(&sTimer,SIGNAL(timeout()),this,SLOT(timeOut200ms()));
}


/******************************************************************************
  Function:~onlinetrack
  Description:
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
onlinetrack::~onlinetrack()
{

}

void onlinetrack::syncHorizontalCalibrationRatio(double dHorizontalCalibrationRatio)
{
    this->dHorizontalCalibrationRatio=dHorizontalCalibrationRatio;
}

/******************************************************************************
  Function:start200msTiming
  Description: 启动200ms定时
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::start200msTiming()
{
    sTimer.start(200);
}

/******************************************************************************
  Function:stopTiming
  Description: stop200ms定时
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::stopTiming()
{
    sTimer.stop();
}


/******************************************************************************
  Function:timeOut200ms
  Description: 启动200ms定时
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::timeOut200ms()
{
    timeoutFlag =true;
    stopTiming();
    emit enableNextDIP_triggered();
}

/******************************************************************************
  Function:dip
  Description: 允许一次图像处理
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::dip(QImage image)
{
    //深拷贝
    _image = image.copy();
    start200msTiming();
    isDIPAllowed = true;

}
/******************************************************************************
  Function:enableAutoTrack
  Description: 使能自动跟踪
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::enableAutoTrack(SeamTrackParameter spParameter)
{
    isAutoTrackTriggered=true;
    dWeldSpeed=spParameter.trackingVelocity;
    dTrackDistance=spParameter.trackingDistance;
    intBufferNum=dSensorFrameRate*dTorchSensorDistance/dWeldSpeed;
    intTotalTrackPeriodNum=dSensorFrameRate*spParameter.trackingDistance/dWeldSpeed;

    qDebug()<<QStringLiteral("Total tracking period:")<<intTotalTrackPeriodNum;



}

/******************************************************************************
  Function:disableAutoTrack
  Description: 关闭自动跟踪
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::disableAutoTrack()
{
    isAutoTrackTriggered=false;
    nthFrame=0;
    resetWeldTrackConfiguration();
}

/******************************************************************************
  Function:resetWeldTrackConfiguration
  Description:
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::resetWeldTrackConfiguration()
{
    dWeldSpeed=0.0;
    dTrackDistance=0.0;
    intBufferNum=0;
    intNthPeriod=0;
    intTotalTrackPeriodNum=0;

}

/******************************************************************************
  Function:enableTestingMode
  Description: 允许测试模式
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::enableTestingMode()
{
    isTestModeTriggered=true;
}

/******************************************************************************
  Function:disableTestingMode
  Description: 禁止测试模式
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::disableTestingMode()
{
    isTestModeTriggered =false;
    nthFrame=0;
}

/******************************************************************************
  Function:referenceTrack
  Description:
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::referenceTrack(double dDeviation)
{
    if(checkRecitificationAvailable(dDeviation))
    {
        recitifyWeldTorch(5*abs(dDeviation),dDeviation);

    }
    intOffsetCount++;
    intNthPeriod++;

    if(intNthPeriod>intTotalTrackPeriodNum)//跟踪完毕
    {
        isAutoTrackTriggered=false;
    }
}


/******************************************************************************
  Function:checkRecitificationAvailable
  Description:判断偏差量大小，若偏差量小于thresh则无需进行纠偏，返回false，否则需要进行
              纠偏控制，返回true
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
bool onlinetrack::checkRecitificationAvailable(double deviation)
{
    double dThreshold=0.5;
    if(abs(deviation)<dThreshold)
    {
        dLastPeriodRemain=deviation;
        return false;
    }
    else
    {
        dLastPeriodRemain=0.0;
        return true;
    }
}

/******************************************************************************
  Function:recitifyWeldTorch
  Description:纠正焊枪的位置
  Calls:
  Called By:
  Input:dSpeed-纠偏速度；dDistance-纠偏距离；
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::recitifyWeldTorch(double dSpeed, double dDistance)
{
    qDebug()<<"Rectify distance:"<<dDistance<<"speed:"<<dSpeed;
    //int iDistance=(int)dDistance;
    //int iSpeed=(int)dSpeed;
    int dir=dDistance>0?0:1;
    //qDebug()<<"Distance:"<<iDistance<<"Speed:"<<iSpeed<<"dir:"<<dir;
    m_workState = stateXMove;
    //xMove(dSpeed,dir,abs(dDistance)); //开环加减速模式
    xPIDMove(dir,abs(dDistance));
    //xmotionObject->xMove(200,dir,iDistance);
//    motionObject->xMove(200,dir,iDistance);
//    motionObject->run();

}

void onlinetrack::createSerialPort()
{
    m_workState = stateXWait;
    m_sendData = "";
    initInfo(xserialPortInfo(115200,1024,"COM5"));
    serialPort2 = new QSerialPort;
    xserialPortInfo& cfg = m_serialPortInfo;


    serialPort2->setPortName(cfg.portName);
    serialPort2->setReadBufferSize(cfg.readBufferSize);
    serialPort2->setBaudRate(cfg.baudRate,cfg.direction);
    serialPort2->setDataBits(cfg.dataBits);
    serialPort2->setFlowControl(cfg.flowControl);
    serialPort2->setParity(cfg.parity);
    if (serialPort2->open(QIODevice::ReadWrite))
        {
            serialPort2->setDataTerminalReady(true);
        }
        else
        {
            serialPort2->clear();
            serialPort2->close();
            serialPort2->deleteLater();
            qDebug() << "onlinetrack serialport open failed";
        }
}

void onlinetrack::initInfo(const xserialPortInfo &info)
{
    m_serialPortInfo=info;
}

void onlinetrack::xMove(double maxVec, int dir, double distance)
{
    if(m_workState == stateXMove)
    {
        if ((maxVec <= 0) || (maxVec > 30))//速度不在范围内，直接返回
        {
            qDebug() << "maxVec not in range!";
            return;
        }
        if ((dir != 1 && dir != 0))
        {
            qDebug() << "please select the correct direction";
            return;
        }
        if(distance<=0 || distance >3)
        {
            qDebug()<<"Rectify distance not in range!";
            return;
        }
        //double vec = maxVec*stepValue*microStep*1.8*3.141592/180;    //mm/s -> rad/s
        int vec =maxVec*unitStepMM*1.8/microStep*3.141592/180*20;
        int dist = abs(distance) *unitStepMM;
        qDebug("vec:%d",vec);
        qDebug("dist:%d",dist);
        QString sDist = QString("%1").arg(dist,4,10,QLatin1Char('0'));
        QString sVec = QString("%1").arg(vec,4,10,QLatin1Char('0'));
        QString sendData = "1"+QString::number(dir)+ sDist + sVec;
        qDebug()<<sendData;
        m_sendData = sendData.toLatin1();
        serialPort2->write(m_sendData);
        if(serialPort2->waitForBytesWritten(50))
             qDebug()<<"Success!";
        //m_sendData.clear();
        //m_workState=stateXWait;
        qDebug()<<"Ok!";
    }
    return;
}

void onlinetrack::xRun(double maxVec, int dir)
{
    if(m_workState == stateXRun)
    {
        if ((maxVec <= 0) || (maxVec > 10))//速度不在范围内，直接返回
        {
            qDebug() << "maxVec not in range!";
            return;
        }
        if ((dir != 1 && dir != 0))
        {
            qDebug() << "please select the correct direction!";
            return;
        }
        //将运动参数转化为数据写入缓存区
        int vec =maxVec*unitStepMM*1.8/microStep*3.141592/180*20;  //2mm/s -> 50
        qDebug("vec=%d",vec);
        QString sVec = QString("%1").arg(vec,4,10,QLatin1Char('0'));
        QString sendData = "1"+QString::number(dir)+ "9999" + sVec ;
        m_sendData = sendData.toLatin1();
        serialPort2->write(m_sendData);
        if(serialPort2->waitForBytesWritten(50))
             qDebug()<<"Success!";
        m_sendData.clear();
    }
}

void onlinetrack::xStop()
{
    if(m_workState == stateXStop)
    {
        QString sendData = "4000000000";
        m_sendData = sendData.toLatin1();
        serialPort2->write(m_sendData);
        if(serialPort2->waitForBytesWritten(50))
             qDebug()<<"Success!";
        m_sendData.clear();
    }
}

void onlinetrack::xReturnOrigin()
{
    if(m_workState == stateXReturn)
    {
        QString sendData="2100000025";
        m_sendData = sendData.toLatin1();
        serialPort2->write(m_sendData);
        if(serialPort2->waitForBytesWritten(50))
             qDebug()<<"Success!";
        m_sendData.clear();
    }
}

/******************************************************************************
  Function:run
  Description:
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::run()
{
    while(true)
    {
        if(isManualMode)
        {
            switch(m_workState)
            {
                case stateXRun:
                    xRun(dmanualMaxVec,imanualDir);
                    dmanualMaxVec=0.0;
                    m_workState=stateXWait;
                    break;
                case stateXMove:
                    xMove(dmanualMaxVec,imanualDir,dmanualDistance);
                    dmanualMaxVec=0.0;
                    dmanualDistance=0.0;
                    m_workState=stateXWait;
                    break;
                case stateXStop:
                    xStop();
                    m_workState=stateXWait;
                    break;
                case stateXReturn:
                    xReturnOrigin();
                    m_workState=stateXWait;
                    break;
                default:break;
            }
        }
        else if(isDIPAllowed)//&& isTestModeTriggered
        {
            double time0 = static_cast<double>(getTickCount());
            Mat image=DIP::qImage2Mat(_image);
            if(nthFrame==0)
            {
             DIP::setROISize(400,200);
             DIP::locateROI(image);
             objectDIP = new DIP;
             objectDIP->processLaserStripeImage(image);
            }
            else {
                qDebug()<<"start KCF!"<<endl;
                objectDIP->KCF(image);
                qDebug()<<"KCF over!"<<endl;
            }
            emit sendDIPResult2_triggered(objectDIP->qOutPutImage);
            emit sendDIPCalculationResult_triggered(objectDIP->seamProfileInfo);
            dOffset=objectDIP->seamProfileInfo.dWeldSeamOffset*dHorizontalCalibrationRatio; //offset,左正右负
            emit sendPIDresult_triggered(dOffset);
            //dOffset=dip.seamProfileInfo.dWeldSeamOffset*dHorizontalCalibrationRatio;
            isDIPAllowed=false;

            double dDeviation;
            /************进行在线跟踪************/
            if(isAutoTrackTriggered)
            {

//                motionObject=new Motion();
//                motionObject->serialPort->moveToThread(this);
               if(intTrackMethod==TRACKMETHOD_REFERENCE)//参考点法
               {
                    dDeviation=dOffset+dLastPeriodRemain;
                    referenceTrack(dDeviation);
               }
            }
            ++nthFrame;
            time0 = ((double)getTickCount() - time0)/getTickFrequency();
            qDebug()<<"Total time:"<<time0<<"s"<<endl;
            //exec();
        }
    }
}

/******************************************************************************
  Function:manualXRun
  Description:执行手动控制界面传过来的指令
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::manualXRun(double maxVec, int dir)
{
   m_workState = stateXRun;
   dmanualMaxVec = maxVec;
   imanualDir = dir;
   qDebug()<<"manual run!";
}


/******************************************************************************
  Function:manualXMove
  Description:执行手动控制界面传过来的指令
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::manualXMove(double maxVec,int dir,double distance)
{
    m_workState = stateXMove;
    dmanualMaxVec = maxVec;
    imanualDir = dir;
    dmanualDistance = distance;
    qDebug()<<"manual move!";
}

/******************************************************************************
  Function:manualXStop
  Description:执行手动控制界面传过来的指令
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::manualXStop()
{
    m_workState = stateXStop;
    qDebug()<<"manual stop!";
}

/******************************************************************************
  Function:manualXReturnOrigin
  Description:执行手动控制界面传过来的指令
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::manualXReturnOrigin()
{
    m_workState = stateXReturn;
    qDebug()<<"manual return!";
}

/******************************************************************************
  Function:enableManualControl
  Description:进入手动控制模式，暂不进行识别跟踪
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::enableManualControl()
{
    isManualMode=true;
    qDebug()<<"Manual mode on!";
}

void onlinetrack::disableManualControl()
{
    isManualMode=false;
    qDebug()<<"Manual mode off!";
}


/******************************************************************************
  Function:returnFirstFrame
  Description:主窗口关识别，回归第一帧图像以准备下次识别
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::returnFirstFrame()
{
    isDIPAllowed=false;
    nthFrame=0;
    delete objectDIP;
}

/******************************************************************************
  Function:xPIDMove
  Description:将偏差传给STM32进行模糊PID控制，distance>0:dir=0;distance<0:dir=1
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void onlinetrack::xPIDMove(int dir, double distance)
{
    if ((dir != 1 && dir != 0))
    {
        qDebug() << "please select the correct direction";
        return;
    }
    if(distance<0 || distance >3)
    {
        qDebug()<<"Rectify distance not in range!";
        return;
    }
    int dist = (int)(distance * 1000);

    qDebug("dist:%d",dist);
    QString sDist = QString("%1").arg(dist,4,10,QLatin1Char('0'));
    QString sendData = QString::number(dir)+ sDist;
    qDebug()<<sendData;
    m_sendData = sendData.toLatin1();
    serialPort2->write(m_sendData);
    if(serialPort2->waitForBytesWritten(50))
         qDebug()<<"Success!";
    qDebug()<<"Ok!";

}

