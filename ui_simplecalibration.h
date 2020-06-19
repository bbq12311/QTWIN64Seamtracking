/********************************************************************************
** Form generated from reading UI file 'simplecalibration.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLECALIBRATION_H
#define UI_SIMPLECALIBRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_simplecalibration
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *labelBlockWidth;
    QLabel *labelBlockWidthPixel;
    QLabel *labelHorizontalCalibrationRatio;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *lineEditBlockWidth;
    QLineEdit *lineEditBlockWidthPixel;
    QLineEdit *lineEditHorizontalCalibrationRatio;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelUnitMM;
    QLabel *labelUnitPixel;
    QPushButton *pushButtonGetBlockWidthPixel;
    QPushButton *pushButtonCalculate;
    QPushButton *pushButtonQuit;

    void setupUi(QWidget *simplecalibration)
    {
        if (simplecalibration->objectName().isEmpty())
            simplecalibration->setObjectName(QString::fromUtf8("simplecalibration"));
        simplecalibration->resize(388, 209);
        verticalLayoutWidget = new QWidget(simplecalibration);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 30, 141, 111));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        labelBlockWidth = new QLabel(verticalLayoutWidget);
        labelBlockWidth->setObjectName(QString::fromUtf8("labelBlockWidth"));

        verticalLayout->addWidget(labelBlockWidth);

        labelBlockWidthPixel = new QLabel(verticalLayoutWidget);
        labelBlockWidthPixel->setObjectName(QString::fromUtf8("labelBlockWidthPixel"));

        verticalLayout->addWidget(labelBlockWidthPixel);

        labelHorizontalCalibrationRatio = new QLabel(verticalLayoutWidget);
        labelHorizontalCalibrationRatio->setObjectName(QString::fromUtf8("labelHorizontalCalibrationRatio"));

        verticalLayout->addWidget(labelHorizontalCalibrationRatio);

        verticalLayoutWidget_2 = new QWidget(simplecalibration);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(149, 30, 151, 113));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEditBlockWidth = new QLineEdit(verticalLayoutWidget_2);
        lineEditBlockWidth->setObjectName(QString::fromUtf8("lineEditBlockWidth"));

        verticalLayout_2->addWidget(lineEditBlockWidth);

        lineEditBlockWidthPixel = new QLineEdit(verticalLayoutWidget_2);
        lineEditBlockWidthPixel->setObjectName(QString::fromUtf8("lineEditBlockWidthPixel"));

        verticalLayout_2->addWidget(lineEditBlockWidthPixel);

        lineEditHorizontalCalibrationRatio = new QLineEdit(verticalLayoutWidget_2);
        lineEditHorizontalCalibrationRatio->setObjectName(QString::fromUtf8("lineEditHorizontalCalibrationRatio"));

        verticalLayout_2->addWidget(lineEditHorizontalCalibrationRatio);

        verticalLayoutWidget_3 = new QWidget(simplecalibration);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(300, 30, 71, 71));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        labelUnitMM = new QLabel(verticalLayoutWidget_3);
        labelUnitMM->setObjectName(QString::fromUtf8("labelUnitMM"));

        verticalLayout_3->addWidget(labelUnitMM);

        labelUnitPixel = new QLabel(verticalLayoutWidget_3);
        labelUnitPixel->setObjectName(QString::fromUtf8("labelUnitPixel"));

        verticalLayout_3->addWidget(labelUnitPixel);

        pushButtonGetBlockWidthPixel = new QPushButton(simplecalibration);
        pushButtonGetBlockWidthPixel->setObjectName(QString::fromUtf8("pushButtonGetBlockWidthPixel"));
        pushButtonGetBlockWidthPixel->setGeometry(QRect(20, 160, 101, 31));
        pushButtonCalculate = new QPushButton(simplecalibration);
        pushButtonCalculate->setObjectName(QString::fromUtf8("pushButtonCalculate"));
        pushButtonCalculate->setGeometry(QRect(130, 160, 101, 31));
        pushButtonQuit = new QPushButton(simplecalibration);
        pushButtonQuit->setObjectName(QString::fromUtf8("pushButtonQuit"));
        pushButtonQuit->setGeometry(QRect(240, 160, 101, 31));

        retranslateUi(simplecalibration);

        QMetaObject::connectSlotsByName(simplecalibration);
    } // setupUi

    void retranslateUi(QWidget *simplecalibration)
    {
        simplecalibration->setWindowTitle(QApplication::translate("simplecalibration", "Form", nullptr));
        labelBlockWidth->setText(QApplication::translate("simplecalibration", "\346\240\207\345\256\232\345\235\227\347\211\251\347\220\206\345\260\272\345\257\270\357\274\232", nullptr));
        labelBlockWidthPixel->setText(QApplication::translate("simplecalibration", "\346\240\207\345\256\232\345\235\227\345\203\217\347\264\240\345\260\272\345\257\270\357\274\232", nullptr));
        labelHorizontalCalibrationRatio->setText(QApplication::translate("simplecalibration", "\346\260\264\345\271\263\346\240\207\345\256\232\346\257\224\347\216\207\357\274\232", nullptr));
        labelUnitMM->setText(QApplication::translate("simplecalibration", "mm", nullptr));
        labelUnitPixel->setText(QApplication::translate("simplecalibration", "pix", nullptr));
        pushButtonGetBlockWidthPixel->setText(QApplication::translate("simplecalibration", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
        pushButtonCalculate->setText(QApplication::translate("simplecalibration", "\350\256\241\347\256\227", nullptr));
        pushButtonQuit->setText(QApplication::translate("simplecalibration", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class simplecalibration: public Ui_simplecalibration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLECALIBRATION_H
