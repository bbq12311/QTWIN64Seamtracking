#ifndef MOTION_H
#define MOTION_H


#include "var.h"



struct serialPortInfo
{
    qint32 baudRate;
    qint32 readBufferSize;
    QString portName;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::FlowControl flowControl;
    QSerialPort::StopBits stopBits;
    QSerialPort::Direction direction;
    serialPortInfo()
    {
        direction = QSerialPort::AllDirections;
        dataBits = QSerialPort::Data8;
        //奇偶校验
        parity = QSerialPort::NoParity;
        //流控制
        flowControl = QSerialPort::NoFlowControl;
        //停止位
        stopBits = QSerialPort::OneStop;
    }
    serialPortInfo(qint32 BaudRate,qint32 ReadBufferSize,QString PortName):serialPortInfo()
    {
        baudRate = BaudRate;
        readBufferSize = ReadBufferSize;
        portName = PortName;
    }
};
enum workState
{
    xrun,
    xmove,
    xstop,
    xreturn,
    xwait
};

class Motion:public QThread
{
    Q_OBJECT
public:
    Motion(void);
    ~Motion(void);

public:
        void xRun(double maxVec,int dir);
        void xMove(double maxVec,int dir,double distance);
        void xStop(void);
        void returnOrigin(void);
        void initInfo(const serialPortInfo& info);
        void run();

public:
       // QSerialPort* serialPort;
        workState m_workState;
        serialPortInfo m_serialPortInfo;
        QByteArray m_sendData;
        QSerialPort* serialPort;
};







#endif // MOTION_H
