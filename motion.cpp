#include "motion.h"





Motion::Motion()
{
    m_workState = xrun;
    m_sendData = "";
    initInfo(serialPortInfo(115200,1024,"COM5"));
    serialPort = new QSerialPort;
    serialPortInfo& cfg = m_serialPortInfo;

    //serialPort.setPortName(QString("ttyUSB0"));
   // serialPort.setReadBufferSize(1024);
    //serialPort.setBaudRate(115200);
    serialPort->setPortName(cfg.portName);
    serialPort->setReadBufferSize(cfg.readBufferSize);
    serialPort->setBaudRate(cfg.baudRate,cfg.direction);
    serialPort->setDataBits(cfg.dataBits);
    serialPort->setFlowControl(cfg.flowControl);
    serialPort->setParity(cfg.parity);
    if (serialPort->isOpen())
    {
        serialPort->close();
    }
    if (serialPort->open(QIODevice::ReadWrite))
        {
            serialPort->setDataTerminalReady(true);
        }
        else
        {
            serialPort->clear();
            serialPort->close();
            serialPort->deleteLater();
            qDebug() << "serialport open failed";
        }
    /*serialPort = new QSerialPort(this);
        serialPort->setBaudRate(115200);
        //数据位数
        serialPort->setDataBits(QSerialPort::Data8);
        //奇偶校验
        serialPort->setParity(QSerialPort::NoParity);
        //流控制
        serialPort->setFlowControl(QSerialPort::NoFlowControl);
        //停止位
        serialPort->setStopBits(QSerialPort::OneStop);
        serialPort->setReadBufferSize(1024);
        //设置串口号
        serialPort->setPortName(QString("ttyUSB0"));
        if (serialPort->open(QIODevice::ReadWrite))
            {
                serialPort->setDataTerminalReady(true);
            }
            else
            {
                serialPort->clear();
                serialPort->close();
                serialPort->deleteLater();
                qDebug() << "串口打开失败";
            }*/
}


Motion::~Motion(void)
{
	if (serialPort->isOpen())
	{
		serialPort->close();
	}
	delete serialPort;
}

void Motion::initInfo(const serialPortInfo& info)
{
    m_serialPortInfo = info;

}

void Motion::run()
{
    /*QSerialPort* serialPort = new QSerialPort;
    serialPortInfo& cfg = m_serialPortInfo;

    //serialPort.setPortName(QString("ttyUSB0"));
   // serialPort.setReadBufferSize(1024);
    //serialPort.setBaudRate(115200);
    serialPort->setPortName(cfg.portName);
    serialPort->setReadBufferSize(cfg.readBufferSize);
    serialPort->setBaudRate(cfg.baudRate,cfg.direction);
    serialPort->setDataBits(cfg.dataBits);
    serialPort->setFlowControl(cfg.flowControl);
    serialPort->setParity(cfg.parity);
    if (serialPort->open(QIODevice::ReadWrite))
        {
            serialPort->setDataTerminalReady(true);
        }
        else
        {
            serialPort->clear();
            serialPort->close();
            serialPort->deleteLater();
            qDebug() << "串口打开失败";
        }*/
    if(m_workState == xrun)
    {
        serialPort->write(m_sendData);
        m_sendData.clear();
       // if(serialPort.waitForBytesWritten(200));
     //   {
        //    qDebug()<<"waitForBytesWrittenTimeOut";
       //     return;
        //}

    }
    if(m_workState == xstop)
    {

        serialPort->write(m_sendData);
        m_sendData.clear();
      //  serialPort.waitForBytesWritten(200);
    //    {
          //  qDebug()<<"waitForBytesWrittenTimeOut";
         //   return;
        //}
    }
    if(m_workState == xmove)
    {

        serialPort->write(m_sendData);
         m_sendData.clear();
       // if(serialPort.waitForBytesWritten(200));
      //  {
        //    qDebug()<<"waitForBytesWrittenTimeOut";
        //    return;
       // }
    }
    if(m_workState == xreturn)
    {
        serialPort->write(m_sendData);
        m_sendData.clear();
        //serialPort.waitForBytesWritten(200);
      //  {
            //qDebug()<<"waitForBytesWrittenTimeOut";
           // return;
       // }
    }
    //delete serialPort;
}




/*************连续运动模式***************/
//maxVec最高运行速度，暂时以脉冲为单位
//dir 旋转方向，1为顺时针，0为逆时针
void Motion::xRun(double maxVec, int dir)
{
     m_workState = xrun;
    if ((maxVec <= 0) || (maxVec > 2))//速度不在范围内，直接返回
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
    //QByteArray sendData_2 = sendData.toLatin1();
    //写入缓冲区
   // serialPort->write(sendData_2);
}


/*************定长运动模式**************/
void Motion::xMove(double maxVec, int dir, double distance)
{
    m_workState = xmove;
    if ((maxVec <= 0) || (maxVec > 2))//速度不在范围内，直接返回
    {
        qDebug() << "maxVec not in range！";
        return;
    }
    if ((dir != 1 && dir != 0))
    {
        qDebug() << "please select the correct direction!";
        return;
    }
    //int vec = maxVec*stepValue*microStep*1.8/8*3.141592/180*20;    //mm/s -> rad/s 实际单位0.05rad/s,最后乘20
    int vec =maxVec*unitStepMM*1.8/microStep*3.141592/180*20;
    int dist = distance * unitStepMM;

    QString sDist = QString("%1").arg(dist,4,10,QLatin1Char('0'));
    QString sVec = QString("%1").arg(vec,4,10,QLatin1Char('0'));
    QString sendData = "1"+QString::number(dir)+ sDist + sVec;
    m_sendData = sendData.toLatin1();
    //写入缓冲区
    //serialPort->write(sendData_2);
    //serialPort->waitForBytesWritten(100);
    //{
     //   qDebug()<<"waitForBytesWrittenTimeOut";
       // return;
  //  }
}


void Motion::xStop()
{
     m_workState = xstop;
    QString sendData = "4000000000";
     m_sendData = sendData.toLatin1();
   // QByteArray sendData_2 = sendData.toLatin1();
    //写入缓冲区
   // serialPort->write(sendData_2);
}




void Motion::returnOrigin()
{
     m_workState = xreturn;
    QString sendData="2100000500";
    m_sendData = sendData.toLatin1();
    //QByteArray sendData_2 = sendData.toLatin1();
    /*写入缓冲区*/
   // serialPort->write(sendData_2);
}






























