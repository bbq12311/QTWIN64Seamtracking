#include "mainwindow.h"
#include "ui_Mainwindow.h"
#include "qdebug.h"

bool cameraIsRunning=false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),uiMainWindow(new Ui::MainWindow),videoItem(nullptr)
{
    qRegisterMetaType<SeamInfo> ("SeamInfo");
    qRegisterMetaType<WeldParameter> ("WeldParameter");
    qRegisterMetaType<SeamTrackParameter> ("SeamTrackParameter");
    uiMainWindow->setupUi(this);

    initializeVariable();
    imageAcquistionObject=new ImageAcqusition(this);
    onlinetrackObject = new onlinetrack(this);
    onlinetrackObject->start();

    scene = new QGraphicsScene(this);
    uiMainWindow->videoGraphicsView->setScene(scene);

    QObject::connect(imageAcquistionObject,SIGNAL(captured(QImage,unsigned char*)),this,SLOT(display(QImage,unsigned char*)));
    QObject::connect(imageAcquistionObject,SIGNAL(captured2(QImage)),this,SLOT(display2(QImage)));
    QObject::connect(this,SIGNAL(triggerTestingMode_triggered()),imageAcquistionObject,SLOT(triggerTestingMode()));
    QObject::connect(this,SIGNAL(detriggerTestingMode_triggered()),imageAcquistionObject,SLOT(detriggerTestingMode()));
    QObject::connect(this,SIGNAL(triggerTestingMode_triggered()),onlinetrackObject,SLOT(enableTestingMode()));
    QObject::connect(this,SIGNAL(detriggerTestingMode_triggered()),onlinetrackObject,SLOT(disableTestingMode()));
    QObject::connect(this,SIGNAL(updateHorizontalCalibrationRatio_triggered(double)),onlinetrackObject,SLOT(syncHorizontalCalibrationRatio(double)));
    QObject::connect(this,SIGNAL(autoTrack_triggered(SeamTrackParameter)),onlinetrackObject,SLOT(enableAutoTrack(SeamTrackParameter)));
    QObject::connect(this,SIGNAL(stopAutoTracking_triggered()),onlinetrackObject,SLOT(disableAutoTrack()));
    QObject::connect(this,SIGNAL(enableManualMode()),onlinetrackObject,SLOT(enableManualControl()));
    QObject::connect(this,SIGNAL(turnOffRecognition()),onlinetrackObject,SLOT(returnFirstFrame()));
    QObject::connect(onlinetrackObject,SIGNAL(sendDIPResult2_triggered(QImage)),this,SLOT(updateDIPResult(QImage)));
    QObject::connect(onlinetrackObject,SIGNAL(enableNextDIP_triggered()),this,SLOT(startDIP()));
    QObject::connect(onlinetrackObject,SIGNAL(sendDIPCalculationResult_triggered(SeamInfo)),this,SLOT(updateDIPCalculationResult(SeamInfo)));


    int cameraCount=0;
    CameraGetCount(&cameraCount);
    if(cameraCount>0)
       {
           cameraConnectionState=true;
           uiMainWindow->label_CameraState->setText(QStringLiteral("已连接"));
           uiMainWindow->label_CameraState->setStyleSheet("color:green;");
           _cameraIndex=0;
           CameraInit(_cameraIndex);
           CameraSetResolution(_cameraIndex,5,&width,&height);

           //qDebug()<<"Resolution="<<width<<","<<height;
       }
    else if(cameraCount==0)
       {
           cameraConnectionState=false;
           uiMainWindow->label_CameraState->setText(QStringLiteral("未连接"));
           uiMainWindow->label_CameraState->setStyleSheet("color:red;");
       }


    if(cameraConnectionState==true)
       {
           isTestModeTriggered=false;
           imageAcquistionObject->start();
           imageAcquistionObject->stream();
           cameraIsRunning=true;
       }
     else
       {
           QMessageBox msgbox;
           msgbox.setText((QStringLiteral("相机未连接，请连接相机！")));
           msgbox.exec();
       }
}

MainWindow::~MainWindow()
{
    CameraFree(0);
    delete uiMainWindow;
}

/***************************
 * Function:initializeVariable()
 * Description:初始化各种变量
 * ************************/
void MainWindow::initializeVariable()
{
   isSavingMultiImagesTriggered=false;
   isTestModeTriggered=false;
   isDIPStarted=false;
   isFirstDIPStarted=false;
   intMultipleImagesNo=0;
   qsMultipleImagesFilePath="..//images//multi//";

}
/***************************
 * Function:on_actionParameterSet_triggered()
 * Description:打开相机参数设置界面
 * ************************/
void MainWindow::on_actionParameterSet_triggered()
{
    cameraObject=new Camera;
    QObject::connect(cameraObject,SIGNAL(resolutionChanged(int,int)),this,SLOT(resolutionDisplay(int,int)));
    QObject::connect(cameraObject,SIGNAL(savingSingleImage_triggered()),this,SLOT(saveSingleImage()));
    QObject::connect(cameraObject,SIGNAL(savingMultipleImages_triggered()),this,SLOT(saveMultipleImages()));
    QObject::connect(cameraObject,SIGNAL(stopSaving_triggered()),this,SLOT(stopSavingMultipleImages()));
    cameraObject->show();
}

/************************************************
 * Function:resolutionDisplay(int,int)
 * Description:根据camera线程改变的分辨率显示相应分辨率
 * **********************************************/
void MainWindow::resolutionDisplay(int width,int height)
{
    //String resolution=std::to_string((long long)width)+"X"+std::to_string((long long)height);
    uiMainWindow->label_CameraResolution->setText(QString("%1X%2").arg(width).arg(height));
    uiMainWindow->label_CameraResolution->setStyleSheet("color:green;");
}

/************************************************
 * Function:saveSingleImage()
 * Description:保存单张图片
 * **********************************************/
void MainWindow::saveSingleImage()
{
    imageAcquistionObject->pause();

    QString fileName;
    fileName=QFileDialog::getSaveFileName(this,QStringLiteral("保存"),"..","Images(*.png *.bmp *.jpg)");

    if(!fileName.isNull())
    {
        if(!frame.isNull())
        {
            bool retV=false;
            retV=frame.save(fileName,nullptr,-1);
            if(retV)
            {
                QMessageBox msgbox;
                msgbox.setText(QStringLiteral("已保存")+fileName);
                msgbox.exec();
                imageAcquistionObject->stream();
            }
        }
        else
        {
            QMessageBox msgbox;
            msgbox.setText(QStringLiteral("当前无图片！"));
            msgbox.exec();
            return;
        }
    }
    else
    {
        return;
    }
}

/************************************************
 * Function:saveMultipleImages()
 * Description:保存多张图片
 * **********************************************/
void MainWindow::saveMultipleImages()
{
    isSavingMultiImagesTriggered=true;
}


/************************************************
 * Function:stopSavingMultipleImages()
 * Description:停止保存多张图片
 * **********************************************/
void MainWindow::stopSavingMultipleImages()
{
    isSavingMultiImagesTriggered=false;
    intMultipleImagesNo=0;
}

/***************************
 * Function:on_actionManualControl_triggered()
 * Description:打开手动控制设置界面
 * ************************/
void MainWindow::on_actionManualControl_triggered()
{
    manualObject=new Manual(this);
    QObject::connect(manualObject,SIGNAL(xRun(double, int)),onlinetrackObject,SLOT(manualXRun(double, int)));
    QObject::connect(manualObject,SIGNAL(xMove(double,int,double)),onlinetrackObject,SLOT(manualXMove(double,int,double)));
    QObject::connect(manualObject,SIGNAL(xStop()),onlinetrackObject,SLOT(manualXStop()));
    QObject::connect(manualObject,SIGNAL(xReturnOrigin()),onlinetrackObject,SLOT(manualXReturnOrigin()));
    QObject::connect(manualObject,SIGNAL(disableManualMode()),onlinetrackObject,SLOT(disableManualControl()));
    emit enableManualMode();
    manualObject->show();


}

/***************************
 * Function:on_actionPID_triggered()
 * Description:打开PID曲线绘制界面
 * ************************/
void MainWindow::on_actionPID_triggered()
{
    pidCurveObject = new pidCurve(this);
    QObject::connect(onlinetrackObject,SIGNAL(sendPIDresult_triggered(double)),pidCurveObject,SLOT(ReadData(double)));
    pidCurveObject->show();
}

/***************************
 * Function:on_actionOfflineTrack_triggered()
 * Description:打开离线跟踪界面
 * ************************/
void MainWindow::on_actionOfflineTrack_triggered()
{
    offlinetrackObject=new OfflineTrack(this);
    offlinetrackObject->show();
}

/***************************
 * Function:on_actionCalibration1_triggered()
 * Description:打开简单校正界面
 * ************************/
void MainWindow::on_actionCalibration1_triggered()
{
    simpleCalibrationObject=new SimpleCalibration(this);
    QObject::connect(simpleCalibrationObject,SIGNAL(getBlockWidthPixel_triggered()),this,SLOT(sendBlockWidthPixel()));
    QObject::connect(simpleCalibrationObject,SIGNAL(updateCalibrationState_triggered()),this,SLOT(syncCalibrationState()));
    QObject::connect(simpleCalibrationObject,SIGNAL(updateHorizontalCalibrationRatio_triggered(double)),this,SLOT(syncHorizontalCalibrationRatio(double)));
    QObject::connect(this,SIGNAL(sendBlockWidthPixel_triggered(double)),simpleCalibrationObject,SLOT(receiveBlockWidthPixel(double)));
    simpleCalibrationObject->show();
}

/***************************
 * Function:sendBlockWidthPixel
 * Description:emit一个sendBlockWidthPixel消息给simpleCalibrationObject
 * ************************/
void MainWindow::sendBlockWidthPixel()
{

}

/***************************
 * Function:syncCalibrationState
 * Description:
 * ************************/
void MainWindow::syncCalibrationState()
{
    isCalibrationFinished=true;
}

/***************************
 * Function:syncHorizontalCalibrationRatio
 * Description:
 * ************************/
void MainWindow::syncHorizontalCalibrationRatio(double horizontalCalibrationRatio)
{
    dHorizontalCalibrationRatio=horizontalCalibrationRatio;
    emit updateHorizontalCalibrationRatio_triggered(horizontalCalibrationRatio);
}

/***************************
 * Function:on_actionWeldParameter_triggered()
 * Description:打开焊接参数设置界面
 * ************************/
void MainWindow::on_actionWeldParameter_triggered()
{
    weldObject=new Weld(this);
    QObject::connect(weldObject,SIGNAL(updateWeldParameters_triggered(WeldParameter)),this,SLOT(syncWeldParameters(WeldParameter)));
    QObject::connect(weldObject,SIGNAL(updateSeamTrackParameters_triggerd(SeamTrackParameter)),this,SLOT(syncSeamTrackParameters(SeamTrackParameter)));
    weldObject->show();
}

/******************************************************************************
  Function: syncWeldParameters
  Description:
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void MainWindow::syncWeldParameters(WeldParameter parameters)
{
    wpWeldParameter=parameters;
    //isWeldParametersUpdated=true;
    emit updateWeldParameters_triggered(wpWeldParameter);
    //更新显示焊接速度
}

/******************************************************************************
  Function: syncSeamTrackParameters
  Description: 更新weldui时，跟踪参数也要更新
  Calls:
  Called By:
  Input:
  Output:
  Return:
  Others:
******************************************************************************/
void MainWindow::syncSeamTrackParameters(SeamTrackParameter parameters)
{
    spSeamTrackParameter=parameters;
}


/***************************
 * Function:on_btnLoadTestData_clicked()
 * Description:加载测试图片
 * ************************/
void MainWindow::on_btnLoadTestData_clicked()
{

    imageAcquistionObject->start();
    //imageAcquistionObject->stream();
    cameraIsRunning=false;
    emit triggerTestingMode_triggered();
    isTestModeTriggered=true;
}


/***************************
 * Function:on_btnUnloadTestData_clicked()
 * Description:卸载测试图片
 * ************************/
void MainWindow::on_btnUnloadTestData_clicked()
{
    emit detriggerTestingMode_triggered();
    isTestModeTriggered=false;
    //imageAcquistionObject->pause();
}


/***************************
 * Function:display
 * Description:显示相机采集的图片
 * ************************/
void MainWindow::display(QImage img,unsigned char* buffer)
{

    if(!img.isNull())
    {
        frame=img.copy(0,0,img.width(),img.height());
        if(isDIPStarted && cameraIsRunning && !isFirstDIPStarted)
        {
            //qDebug()<<"进入识别";
             onlinetrackObject->dip(frame);
             isFirstDIPStarted=true;
        }
        else if(!isDIPStarted)
        {
            if(videoItem)
            {
                scene->removeItem(videoItem);
                delete videoItem;
                videoItem=nullptr;
            }
            if(isSavingMultiImagesTriggered==true)
            {
                intMultipleImagesNo++;
                qsMultipleImagesName=qsMultipleImagesFilePath+QString::number(intMultipleImagesNo)+".bmp";
                frame.save(qsMultipleImagesName,nullptr,-1);

            }
            QImage img1=img.scaled(uiMainWindow->videoGraphicsView->width(),uiMainWindow->videoGraphicsView->height());
            videoItem = scene->addPixmap(QPixmap::fromImage(img1));
            scene->setSceneRect(0,0,img1.width(),img1.height());
        }

    }
    delete [] buffer;

}

/***************************
 * Function:display2
 * Description:显示测试的图片
 * ************************/
void MainWindow::display2(QImage img)
{
    /*if(videoItem)
       {
           scene->removeItem(videoItem);
           delete videoItem;
           videoItem=nullptr;
       }*/
    //frame=img.copy(0,0,img.width(),img.height());
     if(!img.isNull())
     {
        frame=img.copy(0,0,img.width(),img.height());
        if(isDIPStarted && isTestModeTriggered && !isFirstDIPStarted)
        {
             onlinetrackObject->dip(frame);
             isFirstDIPStarted=true;
        }
        else if(!isDIPStarted)
        {
            if(videoItem)
               {
                   scene->removeItem(videoItem);
                   delete videoItem;
                   videoItem=nullptr;
               }
        QImage img1=img.scaled(uiMainWindow->videoGraphicsView->width(),uiMainWindow->videoGraphicsView->height());
        videoItem = scene->addPixmap(QPixmap::fromImage(img1));
        scene->setSceneRect(0,0,img1.width(),img1.height());
        }
     }
}

/***************************
 * Function:on_btnTurnOnRecognition_clicked()
 * Description:开识别
 * ************************/
void MainWindow::on_btnTurnOnRecognition_clicked()
{

   if(true==cameraIsRunning)
   {
       isTestModeTriggered=false;
       isDIPStarted=true;
   }
   else
   {
       if(!isTestModeTriggered)
       {
           QMessageBox msgbox;
           msgbox.setText(QStringLiteral("相机未开，请先开启相机！"));
           msgbox.exec();
       }
       else //测试模式下的识别
       {
           //qDebug()<<"测试模式下识别";
           isDIPStarted=true;
       }
   }
}

/***************************
 * Function:on_btnTurnOffRecognition_clicked()
 * Description:关识别
 * ************************/
void MainWindow::on_btnTurnOffRecognition_clicked()
{
//   onlinetrackObject->quit();
//   onlinetrackObject->wait();
   isDIPStarted=false;
   isFirstDIPStarted=false;
   emit turnOffRecognition();
}

/***************************
 * Function:on_btnStartAutoTrack_clicked
 * Description:开启自动跟踪
 * ************************/
void MainWindow::on_btnStartAutoTrack_clicked()
{
    //check
    if(!cameraIsRunning)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("请先打开相机！"));
        msgbox.exec();
        return;
    }
    if(!isDIPStarted)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("识别未开！"));
        msgbox.exec();
        return;
    }
    if(!isCalibrationFinished)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("校正未完成！"));
        msgbox.exec();
        return;
    }
    if(isCalibrationFinished)
    {
        isAutoTrackTriggered=true;
        emit autoTrack_triggered(spSeamTrackParameter);
    }
}

/***************************
 * Function:on_btnStopAutoTrack_clicked
 * Description:关闭自动跟踪
 * ************************/
void MainWindow::on_btnStopAutoTrack_clicked()
{
    isAutoTrackTriggered=false;
    qDebug()<<"isAutoTrackTriggered="<<isAutoTrackTriggered;
    emit stopAutoTracking_triggered();
}

/***************************
 * Function:updateDIPResult(QImage)
 * Description:更新识别显示
 * ************************/
void MainWindow::updateDIPResult(QImage img)
{
    //qDebug()<<"进入更新识别";
    if(videoItem)
    {
        //qDebug()<<"videoItem existed";
        scene->removeItem(videoItem);
        delete videoItem;
        videoItem=nullptr;
    }
    img=img.scaled(uiMainWindow->videoGraphicsView->width(),uiMainWindow->videoGraphicsView->height());
    videoItem = scene->addPixmap(QPixmap::fromImage(img));
    scene->setSceneRect(0,0,img.width(),img.height());
}

/***************************
 * Function:startDIP()
 * Description:进入持续识别
 * ************************/
void MainWindow::startDIP()
{
    if(isDIPStarted && isFirstDIPStarted)
    {
        //qDebug()<<"进入持续识别";
        onlinetrackObject->dip(frame);
    }
}

/***************************
 * Function:updateDIPCalculationResult(SeamInfo seaminfo)
 * Description:更新图像识别计算结果
 * ************************/
void MainWindow::updateDIPCalculationResult(SeamInfo seaminfo)
{
    siSemaInfo=seaminfo;

    dCurrentOffset=seaminfo.dWeldSeamOffset*dHorizontalCalibrationRatio;
    double sw=int(seaminfo.dWeldSeamWidth*dHorizontalCalibrationRatio*1000)/1000.0;
    QString seamWidth = QString::number(sw);

    QString weldTorchHeight=QString::number(seaminfo.dRemainingHeight);

    double co=int(seaminfo.dWeldSeamOffset*dHorizontalCalibrationRatio*1000)/1000.0;
    QString weldingcurrentOffset=QString::number(co);
    qDebug("seamWidth:%f",sw);
    qDebug("seamOffset:%f",co);
    uiMainWindow->label_WeldSeamWidth->setText(seamWidth);
    uiMainWindow->label_WeldSeamRemainHeight->setText(weldTorchHeight);
    uiMainWindow->label_WeldSeamOffset->setText(weldingcurrentOffset);
}

