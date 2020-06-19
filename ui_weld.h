/********************************************************************************
** Form generated from reading UI file 'weld.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WELD_H
#define UI_WELD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_weld
{
public:
    QWidget *dockWidgetContents;
    QPushButton *pushButtonConfirm;
    QPushButton *pushButtonCancel;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *labelWeldSpeed;
    QLabel *labelGasFlow;
    QLabel *labelWeldVoltage;
    QFormLayout *formLayout_2;
    QLineEdit *lineEditWeldSpeed;
    QLineEdit *lineEditGasFlow;
    QLineEdit *lineEditWeldVoltage;
    QVBoxLayout *verticalLayout_2;
    QLabel *unitWeldSpeed;
    QLabel *unitGasFlow;
    QLabel *unitWeldVoltage;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelWeldDistance;
    QLabel *labelWireRate;
    QLabel *labelWeldCurrent;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *lineEditWeldDistance;
    QLineEdit *lineEditWireRate;
    QLineEdit *lineEditWeldCurrent;
    QVBoxLayout *verticalLayout_5;
    QLabel *unitWeldDistance;
    QLabel *unitWireRate;
    QLabel *unitWeldCurrent;

    void setupUi(QDockWidget *weld)
    {
        if (weld->objectName().isEmpty())
            weld->setObjectName(QString::fromUtf8("weld"));
        weld->resize(423, 373);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        pushButtonConfirm = new QPushButton(dockWidgetContents);
        pushButtonConfirm->setObjectName(QString::fromUtf8("pushButtonConfirm"));
        pushButtonConfirm->setGeometry(QRect(110, 290, 101, 31));
        pushButtonCancel = new QPushButton(dockWidgetContents);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));
        pushButtonCancel->setGeometry(QRect(240, 290, 101, 31));
        layoutWidget = new QWidget(dockWidgetContents);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(21, 30, 381, 121));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelWeldSpeed = new QLabel(layoutWidget);
        labelWeldSpeed->setObjectName(QString::fromUtf8("labelWeldSpeed"));

        verticalLayout->addWidget(labelWeldSpeed);

        labelGasFlow = new QLabel(layoutWidget);
        labelGasFlow->setObjectName(QString::fromUtf8("labelGasFlow"));

        verticalLayout->addWidget(labelGasFlow);

        labelWeldVoltage = new QLabel(layoutWidget);
        labelWeldVoltage->setObjectName(QString::fromUtf8("labelWeldVoltage"));

        verticalLayout->addWidget(labelWeldVoltage);


        horizontalLayout->addLayout(verticalLayout);

        formLayout_2 = new QFormLayout();
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        lineEditWeldSpeed = new QLineEdit(layoutWidget);
        lineEditWeldSpeed->setObjectName(QString::fromUtf8("lineEditWeldSpeed"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, lineEditWeldSpeed);

        lineEditGasFlow = new QLineEdit(layoutWidget);
        lineEditGasFlow->setObjectName(QString::fromUtf8("lineEditGasFlow"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lineEditGasFlow);

        lineEditWeldVoltage = new QLineEdit(layoutWidget);
        lineEditWeldVoltage->setObjectName(QString::fromUtf8("lineEditWeldVoltage"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lineEditWeldVoltage);


        horizontalLayout->addLayout(formLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        unitWeldSpeed = new QLabel(layoutWidget);
        unitWeldSpeed->setObjectName(QString::fromUtf8("unitWeldSpeed"));

        verticalLayout_2->addWidget(unitWeldSpeed);

        unitGasFlow = new QLabel(layoutWidget);
        unitGasFlow->setObjectName(QString::fromUtf8("unitGasFlow"));

        verticalLayout_2->addWidget(unitGasFlow);

        unitWeldVoltage = new QLabel(layoutWidget);
        unitWeldVoltage->setObjectName(QString::fromUtf8("unitWeldVoltage"));

        verticalLayout_2->addWidget(unitWeldVoltage);


        horizontalLayout->addLayout(verticalLayout_2);

        layoutWidget1 = new QWidget(dockWidgetContents);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 160, 371, 115));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        labelWeldDistance = new QLabel(layoutWidget1);
        labelWeldDistance->setObjectName(QString::fromUtf8("labelWeldDistance"));

        verticalLayout_3->addWidget(labelWeldDistance);

        labelWireRate = new QLabel(layoutWidget1);
        labelWireRate->setObjectName(QString::fromUtf8("labelWireRate"));

        verticalLayout_3->addWidget(labelWireRate);

        labelWeldCurrent = new QLabel(layoutWidget1);
        labelWeldCurrent->setObjectName(QString::fromUtf8("labelWeldCurrent"));

        verticalLayout_3->addWidget(labelWeldCurrent);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lineEditWeldDistance = new QLineEdit(layoutWidget1);
        lineEditWeldDistance->setObjectName(QString::fromUtf8("lineEditWeldDistance"));

        verticalLayout_4->addWidget(lineEditWeldDistance);

        lineEditWireRate = new QLineEdit(layoutWidget1);
        lineEditWireRate->setObjectName(QString::fromUtf8("lineEditWireRate"));

        verticalLayout_4->addWidget(lineEditWireRate);

        lineEditWeldCurrent = new QLineEdit(layoutWidget1);
        lineEditWeldCurrent->setObjectName(QString::fromUtf8("lineEditWeldCurrent"));

        verticalLayout_4->addWidget(lineEditWeldCurrent);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        unitWeldDistance = new QLabel(layoutWidget1);
        unitWeldDistance->setObjectName(QString::fromUtf8("unitWeldDistance"));

        verticalLayout_5->addWidget(unitWeldDistance);

        unitWireRate = new QLabel(layoutWidget1);
        unitWireRate->setObjectName(QString::fromUtf8("unitWireRate"));

        verticalLayout_5->addWidget(unitWireRate);

        unitWeldCurrent = new QLabel(layoutWidget1);
        unitWeldCurrent->setObjectName(QString::fromUtf8("unitWeldCurrent"));

        verticalLayout_5->addWidget(unitWeldCurrent);


        horizontalLayout_2->addLayout(verticalLayout_5);

        weld->setWidget(dockWidgetContents);

        retranslateUi(weld);

        QMetaObject::connectSlotsByName(weld);
    } // setupUi

    void retranslateUi(QDockWidget *weld)
    {
        weld->setWindowTitle(QApplication::translate("weld", "DockWidget", nullptr));
        pushButtonConfirm->setText(QApplication::translate("weld", "\347\241\256\345\256\232", nullptr));
        pushButtonCancel->setText(QApplication::translate("weld", "\345\217\226\346\266\210", nullptr));
        labelWeldSpeed->setText(QApplication::translate("weld", "\347\204\212\346\216\245\351\200\237\345\272\246\357\274\232", nullptr));
        labelGasFlow->setText(QApplication::translate("weld", "\344\277\235\346\212\244\346\260\224\346\265\201\351\207\217\357\274\232", nullptr));
        labelWeldVoltage->setText(QApplication::translate("weld", "\347\204\212\346\216\245\347\224\265\345\216\213\357\274\232", nullptr));
        unitWeldSpeed->setText(QApplication::translate("weld", "\346\257\253\347\261\263\357\274\210mm/s\357\274\211", nullptr));
        unitGasFlow->setText(QApplication::translate("weld", "\345\215\207/\345\210\206\357\274\210L/min\357\274\211", nullptr));
        unitWeldVoltage->setText(QApplication::translate("weld", "\344\274\217\357\274\210V\357\274\211", nullptr));
        labelWeldDistance->setText(QApplication::translate("weld", "\347\204\212\346\216\245\351\225\277\345\272\246\357\274\232", nullptr));
        labelWireRate->setText(QApplication::translate("weld", "\351\200\201\344\270\235\351\200\237\345\272\246\357\274\232", nullptr));
        labelWeldCurrent->setText(QApplication::translate("weld", "\347\204\212\346\216\245\347\224\265\346\265\201\357\274\232", nullptr));
        unitWeldDistance->setText(QApplication::translate("weld", "\346\257\253\347\261\263\357\274\210mm\357\274\211", nullptr));
        unitWireRate->setText(QApplication::translate("weld", "\347\261\263/\345\210\206\357\274\210m/min)", nullptr));
        unitWeldCurrent->setText(QApplication::translate("weld", "\345\256\211\357\274\210A)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class weld: public Ui_weld {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WELD_H
