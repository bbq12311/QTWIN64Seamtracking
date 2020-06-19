#ifndef ONLINETRACK_H
#define ONLINETRACK_H

#include <QObject>
#include "dip.h"
#include "var.h"

struct xserialPortInfo
{
    qint32 baudRate;
    qint32 readBufferSize;
    QString portName;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::FlowControl flowControl;
    QSerialPort::StopBits stopBits;
    QSerialPort::Direction direction;
    xserialPortInfo()
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
    xserialPortInfo(qint32 BaudRate,qint32 ReadBufferSize,QString PortName):xserialPortInfo()
    {
        baudRate = BaudRate;
        readBufferSize = ReadBufferSize;
        portName = PortName;
    }
};
enum xworkState
{
    stateXRun,
    stateXMove,
    stateXStop,
    stateXReturn,
    stateXWait
};

class onlinetrack : public QThread
{
    Q_OBJECT
public:
    explicit onlinetrack(QObject *parent=0);
    ~onlinetrack(void);
public:
    void run();
    void dip(QImage image);
private:
    void start200msTiming();
    void stopTiming();

    bool checkRecitificationAvailable(double deviation);
    void recitifyWeldTorch(double dSpeed,double dDistance);
    void referenceTrack(double dDeviation);
    void resetWeldTrackConfiguration();


    void xMove(double maxVec,int dir,double distance);
    void xRun(double maxVec, int dir);
    void xStop();
    void xReturnOrigin();
    void initInfo(const xserialPortInfo& info);
    void createSerialPort();
    void xPIDMove(int dir,double distance);

private:

   // Motion *motionObject;
    bool isDIPAllowed;
    QImage _image;
    int nthFrame;

    QTimer sTimer;
    bool timeoutFlag;

    bool isTestModeTriggered;
    bool isManualMode;


    double dHorizontalCalibrationRatio;
    double dOffset;
    bool isAutoTrackTriggered;
    int intBufferNum;
    int intTotalTrackPeriodNum;
    double dSensorFrameRate;
    double dWeldSpeed;
    double dTrackDistance;
    double dTorchSensorDistance;
    int intOffsetCount;
    int intNthPeriod;
    double dLastPeriodRemain;

    int intTrackMethod;


    xworkState m_workState;
    xserialPortInfo m_serialPortInfo;
    QByteArray m_sendData;
    QSerialPort* serialPort2;

    double dmanualMaxVec;
    int imanualDir;
    double dmanualDistance;
    DIP *objectDIP;
signals:
    void sendDIPResult_triggered(QImage);
    void sendDIPResult2_triggered(QImage);
    void sendDIPCalculationResult_triggered(SeamInfo);
    void enableNextDIP_triggered();
    void sendPIDresult_triggered(double offset);

private slots:
    void timeOut200ms();
    void enableTestingMode();
    void disableTestingMode();
    void syncHorizontalCalibrationRatio(double dHorizontalCalibrationRatio);
    void enableAutoTrack(SeamTrackParameter spParameter);
    void disableAutoTrack();
    void manualXRun(double maxVec, int dir);
    void manualXMove(double maxVec,int dir,double distance);
    void manualXStop();
    void manualXReturnOrigin();
    void enableManualControl();
    void disableManualControl();
    void returnFirstFrame();


};

#endif // ONLINETRACK_H
