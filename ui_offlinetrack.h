/********************************************************************************
** Form generated from reading UI file 'offlinetrack.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OFFLINETRACK_H
#define UI_OFFLINETRACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_offlinetrack
{
public:
    QWidget *dockWidgetContents;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonCollectData;
    QPushButton *pushButtonAnalyzeData;
    QPushButton *pushButtonRecoverSensorPosition;
    QPushButton *pushButtonClearData;
    QPushButton *pushButtonSaveData;
    QPushButton *pushButtonLoadData;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *labelWeldSwitch;
    QRadioButton *radioButtonOn;
    QRadioButton *radioButtonOff;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labelDataSource;
    QRadioButton *radioButtonFromSensor;
    QRadioButton *radioButtonFromFloder;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonStop;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *labelClearDataMethod;
    QRadioButton *radioButtonOnlyMemory;
    QRadioButton *radioButtonTotally;

    void setupUi(QDockWidget *offlinetrack)
    {
        if (offlinetrack->objectName().isEmpty())
            offlinetrack->setObjectName(QString::fromUtf8("offlinetrack"));
        offlinetrack->resize(400, 259);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        layoutWidget = new QWidget(dockWidgetContents);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 331, 101));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonCollectData = new QPushButton(layoutWidget);
        pushButtonCollectData->setObjectName(QString::fromUtf8("pushButtonCollectData"));

        gridLayout->addWidget(pushButtonCollectData, 0, 0, 1, 1);

        pushButtonAnalyzeData = new QPushButton(layoutWidget);
        pushButtonAnalyzeData->setObjectName(QString::fromUtf8("pushButtonAnalyzeData"));

        gridLayout->addWidget(pushButtonAnalyzeData, 0, 1, 1, 1);

        pushButtonRecoverSensorPosition = new QPushButton(layoutWidget);
        pushButtonRecoverSensorPosition->setObjectName(QString::fromUtf8("pushButtonRecoverSensorPosition"));

        gridLayout->addWidget(pushButtonRecoverSensorPosition, 0, 2, 1, 1);

        pushButtonClearData = new QPushButton(layoutWidget);
        pushButtonClearData->setObjectName(QString::fromUtf8("pushButtonClearData"));

        gridLayout->addWidget(pushButtonClearData, 1, 0, 1, 1);

        pushButtonSaveData = new QPushButton(layoutWidget);
        pushButtonSaveData->setObjectName(QString::fromUtf8("pushButtonSaveData"));

        gridLayout->addWidget(pushButtonSaveData, 1, 1, 1, 1);

        pushButtonLoadData = new QPushButton(layoutWidget);
        pushButtonLoadData->setObjectName(QString::fromUtf8("pushButtonLoadData"));

        gridLayout->addWidget(pushButtonLoadData, 1, 2, 1, 1);

        layoutWidget1 = new QWidget(dockWidgetContents);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 110, 184, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        labelWeldSwitch = new QLabel(layoutWidget1);
        labelWeldSwitch->setObjectName(QString::fromUtf8("labelWeldSwitch"));

        horizontalLayout->addWidget(labelWeldSwitch);

        radioButtonOn = new QRadioButton(layoutWidget1);
        radioButtonOn->setObjectName(QString::fromUtf8("radioButtonOn"));

        horizontalLayout->addWidget(radioButtonOn);

        radioButtonOff = new QRadioButton(layoutWidget1);
        radioButtonOff->setObjectName(QString::fromUtf8("radioButtonOff"));

        horizontalLayout->addWidget(radioButtonOff);

        layoutWidget2 = new QWidget(dockWidgetContents);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 150, 264, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        labelDataSource = new QLabel(layoutWidget2);
        labelDataSource->setObjectName(QString::fromUtf8("labelDataSource"));

        horizontalLayout_2->addWidget(labelDataSource);

        radioButtonFromSensor = new QRadioButton(layoutWidget2);
        radioButtonFromSensor->setObjectName(QString::fromUtf8("radioButtonFromSensor"));

        horizontalLayout_2->addWidget(radioButtonFromSensor);

        radioButtonFromFloder = new QRadioButton(layoutWidget2);
        radioButtonFromFloder->setObjectName(QString::fromUtf8("radioButtonFromFloder"));

        horizontalLayout_2->addWidget(radioButtonFromFloder);

        layoutWidget3 = new QWidget(dockWidgetContents);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(190, 110, 178, 37));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButtonStart = new QPushButton(layoutWidget3);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));

        horizontalLayout_3->addWidget(pushButtonStart);

        pushButtonStop = new QPushButton(layoutWidget3);
        pushButtonStop->setObjectName(QString::fromUtf8("pushButtonStop"));

        horizontalLayout_3->addWidget(pushButtonStop);

        layoutWidget4 = new QWidget(dockWidgetContents);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(0, 190, 264, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        labelClearDataMethod = new QLabel(layoutWidget4);
        labelClearDataMethod->setObjectName(QString::fromUtf8("labelClearDataMethod"));

        horizontalLayout_4->addWidget(labelClearDataMethod);

        radioButtonOnlyMemory = new QRadioButton(layoutWidget4);
        radioButtonOnlyMemory->setObjectName(QString::fromUtf8("radioButtonOnlyMemory"));

        horizontalLayout_4->addWidget(radioButtonOnlyMemory);

        radioButtonTotally = new QRadioButton(layoutWidget4);
        radioButtonTotally->setObjectName(QString::fromUtf8("radioButtonTotally"));

        horizontalLayout_4->addWidget(radioButtonTotally);

        offlinetrack->setWidget(dockWidgetContents);

        retranslateUi(offlinetrack);

        QMetaObject::connectSlotsByName(offlinetrack);
    } // setupUi

    void retranslateUi(QDockWidget *offlinetrack)
    {
        offlinetrack->setWindowTitle(QApplication::translate("offlinetrack", "DockWidget", nullptr));
        pushButtonCollectData->setText(QApplication::translate("offlinetrack", "\351\207\207\351\233\206\346\225\260\346\215\256", nullptr));
        pushButtonAnalyzeData->setText(QApplication::translate("offlinetrack", "\345\210\206\346\236\220\346\225\260\346\215\256", nullptr));
        pushButtonRecoverSensorPosition->setText(QApplication::translate("offlinetrack", "\350\277\224\345\233\236\351\233\266\347\202\271", nullptr));
        pushButtonClearData->setText(QApplication::translate("offlinetrack", "\346\270\205\351\231\244\346\225\260\346\215\256", nullptr));
        pushButtonSaveData->setText(QApplication::translate("offlinetrack", "\344\277\235\345\255\230\346\225\260\346\215\256", nullptr));
        pushButtonLoadData->setText(QApplication::translate("offlinetrack", "\350\275\275\345\205\245\346\225\260\346\215\256", nullptr));
        labelWeldSwitch->setText(QApplication::translate("offlinetrack", "\347\204\212\346\216\245\345\274\200\345\205\263\357\274\232", nullptr));
        radioButtonOn->setText(QApplication::translate("offlinetrack", "\345\274\200", nullptr));
        radioButtonOff->setText(QApplication::translate("offlinetrack", "\345\205\263", nullptr));
        labelDataSource->setText(QApplication::translate("offlinetrack", "\346\225\260\346\215\256\346\235\245\346\272\220\357\274\232", nullptr));
        radioButtonFromSensor->setText(QApplication::translate("offlinetrack", "\344\273\216\347\233\270\346\234\272", nullptr));
        radioButtonFromFloder->setText(QApplication::translate("offlinetrack", "\344\273\216\346\226\207\344\273\266\345\244\271", nullptr));
        pushButtonStart->setText(QApplication::translate("offlinetrack", "\345\220\257\345\212\250", nullptr));
        pushButtonStop->setText(QApplication::translate("offlinetrack", "\345\201\234\346\255\242", nullptr));
        labelClearDataMethod->setText(QApplication::translate("offlinetrack", "\346\225\260\346\215\256\346\270\205\351\231\244\346\226\271\345\274\217\357\274\232", nullptr));
        radioButtonOnlyMemory->setText(QApplication::translate("offlinetrack", "\344\273\205\345\206\205\345\255\230", nullptr));
        radioButtonTotally->setText(QApplication::translate("offlinetrack", "\346\211\200\346\234\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class offlinetrack: public Ui_offlinetrack {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OFFLINETRACK_H
