#ifndef IMAGEACQUSITION_H
#define IMAGEACQUSITION_H


#include "JHCap.h"
#include "var.h"
#include "dip.h"

extern bool cameraIsRunning;

class ImageAcqusition:public QThread
{
 Q_OBJECT
public:
 explicit ImageAcqusition(QObject* parent=nullptr);
public:
 void run();
 void setCameraIndex(int index);
 void stream();
 void pause();
 void stop();

private:
 //普通变量
 int cameraIndex;
 static int INT_IMAGE_COUNT;

 //开关、标志等
 bool isCapturingImagesAllowed;
 bool terminateState;
 bool isTestingModeTriggered;

 //slots
public slots:
 void triggerTestingMode();
 void detriggerTestingMode();
 //void allowSavingMultipleImages();
 //void declineSavingMultipleImages();

 //信号
signals:
 void captured(QImage img,unsigned char* buffer);
 void captured2(QImage img);

};
































#endif // IMAGEACQUSITION_H
