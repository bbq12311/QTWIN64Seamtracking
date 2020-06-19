#include "camera.h"
#include "ui_camera.h"

Camera::Camera(QWidget *parent) :
    QDockWidget(parent),
    uiCamera(new Ui::camera)
{
    uiCamera->setupUi(this);

//初始化相机配置
//分辨率
        QStringList resolutionList;
        intCameraIndex=0;
        resolutionList<<"2048X1536"<<"1600X1200"<<"1280X1024"<<"1024x768"<<"800X600"<<"640X480";
        uiCamera->cmbCameraResolution->addItems(resolutionList);
        uiCamera->cmbCameraResolution->setCurrentIndex(5);

//设置horizontalSlider范围
        uiCamera->horizontalSliderGamma->setMaximum(20);
        uiCamera->horizontalSliderGamma->setMinimum(3);

        uiCamera->horizontalSliderSaturation->setMaximum(20);
        uiCamera->horizontalSliderSaturation->setMinimum(0);

        uiCamera->sliderContrast->setMaximum(20);
        uiCamera->sliderContrast->setMinimum(3);

        uiCamera->horizontalSliderGain->setMaximum(32);
        uiCamera->horizontalSliderGain->setMinimum(1);

        uiCamera->horizontalSliderExposure->setMaximum(4000);
        uiCamera->horizontalSliderExposure->setMinimum(1);

        //设置初始值
        double dGamma;//Gamma:0.3-2
        CameraGetGamma(intCameraIndex,&dGamma);
        uiCamera->labelGainValue->setText(QString("%1").arg(dGamma));
        uiCamera->horizontalSliderGamma->setValue(dGamma*10);

        double dContrast;//Contrast:0.3-2
        CameraGetContrast(intCameraIndex,&dContrast);
        uiCamera->labelContrastValue->setText(QString("%1").arg(dContrast));
        uiCamera->sliderContrast->setValue(dContrast*10);

        double dSaturation;//Saturaion:0-2
        CameraGetSaturation(intCameraIndex,&dSaturation);
        uiCamera->labelSaturationValue->setText(QString("%1").arg(dSaturation));
        uiCamera->horizontalSliderSaturation->setValue(dSaturation*10);

        int intGain;//Gain:1-32
        CameraGetGain(intCameraIndex,&intGain);
        uiCamera->labelGainValue->setText(QString("%1").arg(intGain));
        uiCamera->horizontalSliderGain->setValue(intGain);

        int intExposure;//intExposure：1-4000
        CameraGetExposure(intCameraIndex,&intExposure);
        uiCamera->labelExposureValue->setText(QString("%1").arg(intExposure));
        uiCamera->horizontalSliderExposure->setValue(intExposure);
}

Camera::~Camera()
{
    delete uiCamera;
}

//设置分辨率
void Camera::on_cmbCameraResolution_currentIndexChanged(int index)
{
    int intCameraIndex=0;
    int width=0;
    int height=0;
    CameraSetResolution(intCameraIndex,index,&width,&height);
    emit resolutionChanged(width,height);

}

//一键白平衡
void Camera::on_pushButtonWhiteBalance_clicked()
{
    CameraOnePushWB(intCameraIndex);
}

//更改Gamma值
void Camera::on_horizontalSliderGamma_valueChanged(int intGamma)
{
    double dGamma=intGamma/10.0;
    CameraSetGamma(intCameraIndex,dGamma);
    uiCamera->labelGammaValue->setText(QString("%1").arg(intGamma));
}


void Camera::on_horizontalSliderSaturation_valueChanged(int intSaturation)
{
    double dSaturaion = intSaturation/10.0;
    CameraSetSaturation(intCameraIndex,dSaturaion);
    uiCamera->labelSaturationValue->setText(QString("%1").arg(intSaturation));
}


//更改增益
void Camera::on_horizontalSliderGain_valueChanged(int intGainValue)
{
    CameraSetGain(intCameraIndex,intGainValue);
    uiCamera->labelGainValue->setText(QString("%1").arg(intGainValue));
}


void Camera::on_horizontalSliderExposure_valueChanged(int intExposureValue)
{
    CameraSetExposure(intCameraIndex,intExposureValue);
    uiCamera->labelExposureValue->setText(QString("%1").arg(intExposureValue));
}

//更改对比度
void Camera::on_sliderContrast_valueChanged(int intContrastValue)
{
    double dContrast=intContrastValue/10.0;
    CameraSetContrast(intCameraIndex,dContrast);
    uiCamera->labelContrastValue->setText(QString("%1").arg(intContrastValue));
}


void Camera::on_checkBoxGain_toggled(bool checked)
{
    CameraSetAGC(intCameraIndex,checked);
    CameraGetAGC(intCameraIndex,&bAGC);
    if(bAGC)//相机已开启自动增益
    {
        uiCamera->horizontalSliderGain->setEnabled(false);
        uiCamera->checkBoxGain->setChecked(true);

    }
    else//相机关闭自动增益
    {
        int gain;
        CameraGetGain(intCameraIndex,&gain);
        uiCamera->labelGainValue->setText(QString("%1").arg(gain));
        uiCamera->horizontalSliderGain->setEnabled(true);
        uiCamera->horizontalSliderGain->setValue(gain);
    }
}

void Camera::on_checkBoxExposure_toggled(bool checked)
{
    CameraSetAEC(intCameraIndex,checked);
    CameraGetAEC(intCameraIndex,&bAEC);
    if(bAEC)//相机已开启自动曝光
    {
        uiCamera->horizontalSliderExposure->setEnabled(false);
        uiCamera->checkBoxExposure->setChecked(true);
    }
    else//相机关闭自动曝光
    {
        int exposure;
        CameraGetExposure(intCameraIndex,&exposure);
        uiCamera->labelExposureValue->setText(QString("%1").arg(exposure));
        uiCamera->horizontalSliderExposure->setEnabled(true);
    }
}


void Camera::on_pushButtonSaveSingleImage_clicked()
{
    emit savingSingleImage_triggered();
}


void Camera::on_pushButtonSaveMultipleImages_clicked()
{
    emit savingMultipleImages_triggered();
}


void Camera::on_pushButtonStopSaving_clicked()
{
    emit stopSaving_triggered();
}


void Camera::on_pushButtonSaveCameraConfiguration_clicked()
{
    QString qstrFileName=QFileDialog::getSaveFileName(this,"Save XML","G://MyWeldSeamTrack//camera","XML Files(*.xml)");

    if(qstrFileName.isEmpty()==false)
    {
        QFile file(qstrFileName);
        file.open(QIODevice::WriteOnly);

        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();

        xmlWriter.writeStartElement(QStringLiteral("相机参数"));
        xmlWriter.writeTextElement("Gamma",QString::number(uiCamera->horizontalSliderGamma->value()));
        xmlWriter.writeTextElement("Contrast",QString::number(uiCamera->sliderContrast->value()));
        xmlWriter.writeTextElement("Saturaion",QString::number(uiCamera->horizontalSliderSaturation->value()));

        int intGain;
        if(API_OK==CameraGetGain(intCameraIndex,&intGain));
        else intGain=0;
        xmlWriter.writeTextElement("Gain",uiCamera->checkBoxGain->isChecked()?QString
        ::number(intGain):QString::number(uiCamera->horizontalSliderGain->value()));

        int intExposure;
        if(API_OK==CameraGetExposure(intCameraIndex,&intExposure));
        else intExposure=0;
        xmlWriter.writeTextElement("Exposure",uiCamera->checkBoxExposure->isChecked()?
        QString::number(intExposure):QString::number(uiCamera->horizontalSliderExposure->value()));

        xmlWriter.writeEndElement();
        xmlWriter.writeEndDocument();
        file.close();

        QMessageBox msgbox;
        msgbox.setWindowTitle(QStringLiteral("保存提示"));
        msgbox.setText(qstrFileName+QStringLiteral("已保存"));
        msgbox.exec();

   }
}


void Camera::on_pushButtonLoadCameraConfiguration_clicked()
{
    QString qstrFileName=QFileDialog::getOpenFileName(this,"Load XML","/home/pi/课题/seamTracking/camera","XML Files(*.xml)");
    if(qstrFileName.isEmpty()==false)
    {
        QFile file(qstrFileName);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            std::cerr<<"Error:Cannot read file"<<qPrintable(qstrFileName)<<":"<<qPrintable(file.errorString())<<std::endl;
        }

        QXmlStreamReader xmlReader;
        xmlReader.setDevice(&file);
        xmlReader.readNext();

        while(!xmlReader.atEnd() && !xmlReader.hasError())
        {
            QXmlStreamReader::TokenType token=xmlReader.readNext();
            if(token==QXmlStreamReader::StartDocument) continue;
            if(token==QXmlStreamReader::StartElement)
            {
                if(xmlReader.name()==QStringLiteral("相机参数"))
                {
                    continue;
                }
                else if(xmlReader.name()=="Gamma")
                {
                    uiCamera->horizontalSliderGamma->setValue(xmlReader.readElementText().toInt());
                }
                else if(xmlReader.name()=="Contrast")
                {
                    uiCamera->sliderContrast->setValue(xmlReader.readElementText().toInt());
                }
                else if(xmlReader.name()=="Saturation")
                {
                    uiCamera->horizontalSliderSaturation->setValue(xmlReader.readElementText().toInt());
                }
                else if(xmlReader.name()=="Gain")
                {
                    uiCamera->horizontalSliderGain->setValue(xmlReader.readElementText().toInt());
                }
                else if(xmlReader.name()=="Exposure")
                {
                    uiCamera->horizontalSliderExposure->setValue(xmlReader.readElementText().toInt());
                }
            }
        }
        if(xmlReader.hasError())
        {
            QMessageBox::critical(this,"xmlFile.xml Parse Error",xmlReader.errorString(),QMessageBox::Ok);
            return;
        }
    }

}
