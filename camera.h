#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QDockWidget>
#include <JHCap.h>
#include <QFileDialog>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <iostream>

namespace Ui {
class camera;
}

class Camera : public QDockWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();

private:
    Ui::camera *uiCamera;

private:
    int intCameraIndex;
    bool bAGC;
    bool bAEC;
private slots:
    void on_cmbCameraResolution_currentIndexChanged(int index);
    void on_pushButtonWhiteBalance_clicked();
    void on_horizontalSliderGamma_valueChanged(int intGamma);
    void on_horizontalSliderSaturation_valueChanged(int intSaturation);
    void on_sliderContrast_valueChanged(int intContrastValue);
    void on_horizontalSliderGain_valueChanged(int intGainValue);
    void on_horizontalSliderExposure_valueChanged(int intExposureValue);
    void on_checkBoxGain_toggled(bool checked);
    void on_checkBoxExposure_toggled(bool checked);
    void on_pushButtonSaveSingleImage_clicked();
    void on_pushButtonSaveMultipleImages_clicked();
    void on_pushButtonStopSaving_clicked();
    void on_pushButtonSaveCameraConfiguration_clicked();
    void on_pushButtonLoadCameraConfiguration_clicked();


signals:
    void resolutionChanged(int width1,int height1);
    void savingSingleImage_triggered();
    void savingMultipleImages_triggered();
    void stopSaving_triggered();

};

#endif // CAMERA_H
