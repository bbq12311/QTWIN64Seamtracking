/********************************************************************************
** Form generated from reading UI file 'camera.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERA_H
#define UI_CAMERA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_camera
{
public:
    QWidget *dockWidgetContents;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBoxISP;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelContrast;
    QSlider *sliderContrast;
    QLabel *labelContrastValue;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *checkBoxExposure;
    QLabel *labelExposure;
    QSlider *horizontalSliderExposure;
    QLabel *labelExposureValue;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBoxGain;
    QLabel *labelGain;
    QSlider *horizontalSliderGain;
    QLabel *labelGainValue;
    QHBoxLayout *horizontalLayout;
    QLabel *labelGamma;
    QSlider *horizontalSliderGamma;
    QLabel *labelGammaValue;
    QHBoxLayout *horizontalLayout_7;
    QLabel *labelSaturation;
    QSlider *horizontalSliderSaturation;
    QLabel *labelSaturationValue;
    QPushButton *pushButtonWhiteBalance;
    QHBoxLayout *horizontalLayout_5;
    QLabel *labelChangeResolution;
    QComboBox *cmbCameraResolution;
    QGroupBox *groupBoxSaveLoad;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonLoadCameraConfiguration;
    QPushButton *pushButtonSaveCameraConfiguration;
    QPushButton *pushButtonSaveSingleImage;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonSaveMultipleImages;
    QPushButton *pushButtonStopSaving;

    void setupUi(QDockWidget *camera)
    {
        if (camera->objectName().isEmpty())
            camera->setObjectName(QString::fromUtf8("camera"));
        camera->resize(554, 402);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        layoutWidget = new QWidget(dockWidgetContents);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 495, 284));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBoxISP = new QGroupBox(layoutWidget);
        groupBoxISP->setObjectName(QString::fromUtf8("groupBoxISP"));
        gridLayout = new QGridLayout(groupBoxISP);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labelContrast = new QLabel(groupBoxISP);
        labelContrast->setObjectName(QString::fromUtf8("labelContrast"));

        horizontalLayout_2->addWidget(labelContrast);

        sliderContrast = new QSlider(groupBoxISP);
        sliderContrast->setObjectName(QString::fromUtf8("sliderContrast"));
        sliderContrast->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sliderContrast);

        labelContrastValue = new QLabel(groupBoxISP);
        labelContrastValue->setObjectName(QString::fromUtf8("labelContrastValue"));

        horizontalLayout_2->addWidget(labelContrastValue);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        checkBoxExposure = new QCheckBox(groupBoxISP);
        checkBoxExposure->setObjectName(QString::fromUtf8("checkBoxExposure"));

        horizontalLayout_4->addWidget(checkBoxExposure);

        labelExposure = new QLabel(groupBoxISP);
        labelExposure->setObjectName(QString::fromUtf8("labelExposure"));

        horizontalLayout_4->addWidget(labelExposure);

        horizontalSliderExposure = new QSlider(groupBoxISP);
        horizontalSliderExposure->setObjectName(QString::fromUtf8("horizontalSliderExposure"));
        horizontalSliderExposure->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSliderExposure);

        labelExposureValue = new QLabel(groupBoxISP);
        labelExposureValue->setObjectName(QString::fromUtf8("labelExposureValue"));

        horizontalLayout_4->addWidget(labelExposureValue);


        gridLayout->addLayout(horizontalLayout_4, 4, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBoxGain = new QCheckBox(groupBoxISP);
        checkBoxGain->setObjectName(QString::fromUtf8("checkBoxGain"));

        horizontalLayout_3->addWidget(checkBoxGain);

        labelGain = new QLabel(groupBoxISP);
        labelGain->setObjectName(QString::fromUtf8("labelGain"));

        horizontalLayout_3->addWidget(labelGain);

        horizontalSliderGain = new QSlider(groupBoxISP);
        horizontalSliderGain->setObjectName(QString::fromUtf8("horizontalSliderGain"));
        horizontalSliderGain->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSliderGain);

        labelGainValue = new QLabel(groupBoxISP);
        labelGainValue->setObjectName(QString::fromUtf8("labelGainValue"));

        horizontalLayout_3->addWidget(labelGainValue);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelGamma = new QLabel(groupBoxISP);
        labelGamma->setObjectName(QString::fromUtf8("labelGamma"));

        horizontalLayout->addWidget(labelGamma);

        horizontalSliderGamma = new QSlider(groupBoxISP);
        horizontalSliderGamma->setObjectName(QString::fromUtf8("horizontalSliderGamma"));
        horizontalSliderGamma->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSliderGamma);

        labelGammaValue = new QLabel(groupBoxISP);
        labelGammaValue->setObjectName(QString::fromUtf8("labelGammaValue"));

        horizontalLayout->addWidget(labelGammaValue);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        labelSaturation = new QLabel(groupBoxISP);
        labelSaturation->setObjectName(QString::fromUtf8("labelSaturation"));

        horizontalLayout_7->addWidget(labelSaturation);

        horizontalSliderSaturation = new QSlider(groupBoxISP);
        horizontalSliderSaturation->setObjectName(QString::fromUtf8("horizontalSliderSaturation"));
        horizontalSliderSaturation->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSliderSaturation);

        labelSaturationValue = new QLabel(groupBoxISP);
        labelSaturationValue->setObjectName(QString::fromUtf8("labelSaturationValue"));

        horizontalLayout_7->addWidget(labelSaturationValue);


        gridLayout->addLayout(horizontalLayout_7, 1, 0, 1, 1);


        verticalLayout_3->addWidget(groupBoxISP);

        pushButtonWhiteBalance = new QPushButton(layoutWidget);
        pushButtonWhiteBalance->setObjectName(QString::fromUtf8("pushButtonWhiteBalance"));

        verticalLayout_3->addWidget(pushButtonWhiteBalance);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        labelChangeResolution = new QLabel(layoutWidget);
        labelChangeResolution->setObjectName(QString::fromUtf8("labelChangeResolution"));

        horizontalLayout_5->addWidget(labelChangeResolution);

        cmbCameraResolution = new QComboBox(layoutWidget);
        cmbCameraResolution->setObjectName(QString::fromUtf8("cmbCameraResolution"));

        horizontalLayout_5->addWidget(cmbCameraResolution);


        verticalLayout_3->addLayout(horizontalLayout_5);


        horizontalLayout_6->addLayout(verticalLayout_3);

        groupBoxSaveLoad = new QGroupBox(layoutWidget);
        groupBoxSaveLoad->setObjectName(QString::fromUtf8("groupBoxSaveLoad"));
        gridLayout_2 = new QGridLayout(groupBoxSaveLoad);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonLoadCameraConfiguration = new QPushButton(groupBoxSaveLoad);
        pushButtonLoadCameraConfiguration->setObjectName(QString::fromUtf8("pushButtonLoadCameraConfiguration"));

        verticalLayout->addWidget(pushButtonLoadCameraConfiguration);

        pushButtonSaveCameraConfiguration = new QPushButton(groupBoxSaveLoad);
        pushButtonSaveCameraConfiguration->setObjectName(QString::fromUtf8("pushButtonSaveCameraConfiguration"));

        verticalLayout->addWidget(pushButtonSaveCameraConfiguration);

        pushButtonSaveSingleImage = new QPushButton(groupBoxSaveLoad);
        pushButtonSaveSingleImage->setObjectName(QString::fromUtf8("pushButtonSaveSingleImage"));

        verticalLayout->addWidget(pushButtonSaveSingleImage);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButtonSaveMultipleImages = new QPushButton(groupBoxSaveLoad);
        pushButtonSaveMultipleImages->setObjectName(QString::fromUtf8("pushButtonSaveMultipleImages"));

        verticalLayout_2->addWidget(pushButtonSaveMultipleImages);

        pushButtonStopSaving = new QPushButton(groupBoxSaveLoad);
        pushButtonStopSaving->setObjectName(QString::fromUtf8("pushButtonStopSaving"));

        verticalLayout_2->addWidget(pushButtonStopSaving);


        verticalLayout->addLayout(verticalLayout_2);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);


        horizontalLayout_6->addWidget(groupBoxSaveLoad);

        camera->setWidget(dockWidgetContents);

        retranslateUi(camera);

        QMetaObject::connectSlotsByName(camera);
    } // setupUi

    void retranslateUi(QDockWidget *camera)
    {
        camera->setWindowTitle(QApplication::translate("camera", "DockWidget", nullptr));
        groupBoxISP->setTitle(QApplication::translate("camera", "ISP", nullptr));
        labelContrast->setText(QApplication::translate("camera", "Contrast", nullptr));
        labelContrastValue->setText(QApplication::translate("camera", "null", nullptr));
        checkBoxExposure->setText(QApplication::translate("camera", "Auto", nullptr));
        labelExposure->setText(QApplication::translate("camera", "Exposure", nullptr));
        labelExposureValue->setText(QApplication::translate("camera", "null", nullptr));
        checkBoxGain->setText(QApplication::translate("camera", "Auto", nullptr));
        labelGain->setText(QApplication::translate("camera", "Gain", nullptr));
        labelGainValue->setText(QApplication::translate("camera", "null", nullptr));
        labelGamma->setText(QApplication::translate("camera", "Gamma", nullptr));
        labelGammaValue->setText(QApplication::translate("camera", "null", nullptr));
        labelSaturation->setText(QApplication::translate("camera", "Saturation", nullptr));
        labelSaturationValue->setText(QApplication::translate("camera", "null", nullptr));
        pushButtonWhiteBalance->setText(QApplication::translate("camera", "\344\270\200\351\224\256\347\231\275\345\271\263\350\241\241", nullptr));
        labelChangeResolution->setText(QApplication::translate("camera", "\345\217\230\346\233\264\347\233\270\346\234\272\345\210\206\350\276\250\347\216\207", nullptr));
        groupBoxSaveLoad->setTitle(QApplication::translate("camera", "Save and Load", nullptr));
        pushButtonLoadCameraConfiguration->setText(QApplication::translate("camera", "\350\275\275\345\205\245\347\233\270\346\234\272\351\205\215\347\275\256", nullptr));
        pushButtonSaveCameraConfiguration->setText(QApplication::translate("camera", "\344\277\235\345\255\230\347\233\270\346\234\272\351\205\215\347\275\256", nullptr));
        pushButtonSaveSingleImage->setText(QApplication::translate("camera", "\344\277\235\345\255\230\345\215\225\345\274\240\345\233\276\347\211\207", nullptr));
        pushButtonSaveMultipleImages->setText(QApplication::translate("camera", "\344\277\235\345\255\230\350\277\236\347\273\255\345\244\232\345\274\240\345\233\276\347\211\207", nullptr));
        pushButtonStopSaving->setText(QApplication::translate("camera", "\345\201\234\346\255\242\344\277\235\345\255\230", nullptr));
    } // retranslateUi

};

namespace Ui {
    class camera: public Ui_camera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERA_H
