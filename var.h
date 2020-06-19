#ifndef VAR_H
#define VAR_H


#include <opencv2/opencv.hpp>
#include "qthread.h"
#include "qimage.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <qpixmap.h>
#include "qdebug.h"
#include "QTime"
#include "qmessagebox.h"
#include <qfiledialog.h>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QTimer>
#include <QTime>
#include "time.h"
#include <QThread>
#include <QtSerialPort/qserialportinfo.h>
#include <QtSerialPort/qserialport.h>
#include <qdebug.h>
#include <qbytearray.h>

#define FILTER_MED_33 1
#define FILTER_MED_55 2
#define FILTER_OPEN_15 3
#define FILTER_OPEN_37 4

#define INTENSITY_GRAVITY 1
#define INTENSITY_MAXIMUM 2

#define EXTRACTION_ITERATION 1
#define EXTRACTION_DIFFERENTIAL 2

#define TRACKMETHOD_REFERENCE 1
#define TRACKMETHOD_GLOBAL_COORDINATE 2

#define stepValue 200 // 步进电机单圈步数，步距角：1.8° 360/1.8=200 正常情况下需要200步转一圈
#define microStep 8 //步进电机驱动器细分数
#define unitsDistance 5//步进电机转一圈，导轨前进5mm
#define SPR (stepValue*microStep) //旋转一圈需要的脉冲数
#define ALPHA   ((float)(2*3.14159/SPR))    //a= 2*pi/SPR 步距单位为弧度
#define unitStepMM  (SPR/unitsDistance) //步进1mm需要的步数

/******************************************************************************
  Name:WeldParameter
  Description: 焊接工艺参数
  Used By: tracksys.h tracksys.cpp weld.h weld.cpp
  Others:
******************************************************************************/
struct WeldParameter
{
    double dWeldSpeed;			//焊接速度
    double dWireRate;			//送丝速度
    double dGasFlow;			//保护气流量
    double dWeldVoltage;		//焊接电压
    double dWeldCurrent;		//焊接电流
    double dWeldDistance;		//焊接距离
    double dGasPressure;		//气体压力
};


/******************************************************************************
  Name:SeamTrackParameter
  Description: 焊缝跟踪参数
  Used By: tracksys.h tracksys.cpp dip.h dip.cpp
  Others:
******************************************************************************/
struct SeamTrackParameter
{
    double trackingVelocity;
    double trackingDistance;
    char trackingDirection;
};

/******************************************************************************
  Name:SeamType
  Description: 焊缝类型
  Used By: tracksys.h tracksys.cpp var.h
  Others:
******************************************************************************/
enum SeamType
{
    BUTT_WELD_SEAM,		//I型对接焊缝
    LAP_WELD_SEAM,		//搭接焊缝
    GROOVE_WELD_SEAM	//V型对接焊缝
};

/******************************************************************************
  Name:SeamInfo
  Description: 焊缝信息
  Used By: tracksys.h tracksys.cpp dip.h dip.cpp
  Others:
******************************************************************************/
struct SeamInfo
{
    double dWeldSeamOffset;
    double dWeldSeamWidth;
    double dRemainingHeight;	//焊缝余高
    SeamType weldSeamType;
};
#endif // VAR_H
