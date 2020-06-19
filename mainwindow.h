#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <camera.h>
#include <manual.h>
#include <offlinetrack.h>
#include <simplecalibration.h>
#include <weld.h>
#include <var.h>
#include "imageacqusition.h"
#include "onlinetrack.h"
#include "pidcurve.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//ui
private:
    Ui::MainWindow *uiMainWindow;
//Qt objects
private:
    ImageAcqusition *imageAcquistionObject;
    Camera *cameraObject;
    Manual *manualObject;
    OfflineTrack *offlinetrackObject;
    SimpleCalibration *simpleCalibrationObject;
    Weld *weldObject;
    onlinetrack *onlinetrackObject;
    pidCurve *pidCurveObject;

//normal variables
private:
    int _cameraIndex;
    int width;
    int height;
    QImage frame;
    int intMultipleImagesNo;
    QString qsMultipleImagesFilePath;
    QString qsMultipleImagesName;
    WeldParameter wpWeldParameter;
    SeamTrackParameter spSeamTrackParameter;
    SeamInfo siSemaInfo;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *videoItem;

    double dHorizontalCalibrationRatio;
    double dCurrentOffset;

    //开关、标志类
private:
    bool cameraConnectionState;
    bool isTestModeTriggered;
    bool isSavingMultiImagesTriggered;
    bool isDIPStarted;
    bool isFirstDIPStarted;
    bool isCalibrationFinished;
    bool isAutoTrackTriggered;


//普通私有函数
private:
    void initializeVariable();

//slots
public slots:
    //pushbotton-related
    void on_btnLoadTestData_clicked();
    void on_btnUnloadTestData_clicked();
    void on_btnTurnOnRecognition_clicked();
    void on_btnTurnOffRecognition_clicked();
    void on_btnStartAutoTrack_clicked();
    void on_btnStopAutoTrack_clicked();
    void on_actionParameterSet_triggered();
    void on_actionManualControl_triggered();
    void on_actionOfflineTrack_triggered();
    void on_actionCalibration1_triggered();
    void on_actionWeldParameter_triggered();
    void on_actionPID_triggered();

    //self-defined
    void display(QImage img,unsigned char* buffer);
    void display2(QImage img);
    void resolutionDisplay(int width,int height);
    void saveSingleImage();
    void saveMultipleImages();
    void stopSavingMultipleImages();
    void syncWeldParameters(WeldParameter parameters);
    void syncSeamTrackParameters(SeamTrackParameter parameters);
    void sendBlockWidthPixel();
    void syncCalibrationState();
    void syncHorizontalCalibrationRatio(double horizontalCalibrationRatio);
    void updateDIPCalculationResult(SeamInfo seaminfo);
    void updateDIPResult(QImage img);
    void startDIP();

signals:
    void triggerTestingMode_triggered();
    void detriggerTestingMode_triggered();
    void updateWeldParameters_triggered(WeldParameter parameters);
    void updateHorizontalCalibrationRatio_triggered(double rho);
    void sendBlockWidthPixel_triggered(double dBlockWidthPixel);
    void autoTrack_triggered(SeamTrackParameter seamTrackingParas);
    void stopAutoTracking_triggered();
    void enableManualMode();
    void turnOffRecognition();
};

#endif // MAINWINDOW_H
