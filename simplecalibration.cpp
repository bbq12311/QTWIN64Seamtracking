#include "simplecalibration.h"
#include "ui_simplecalibration.h"

SimpleCalibration::SimpleCalibration(QWidget *parent) :
    QWidget(parent),
    uiSimplecalibration(new Ui::simplecalibration)
{
    uiSimplecalibration->setupUi(this);
    setDefaultConfiguration();
}

SimpleCalibration::~SimpleCalibration()
{
    delete uiSimplecalibration;
}

/*******************************************************
 * Function:setDefaultConfiguration
 * Description:设置默认的标定块（Block)宽度为10mm
 * *****************************************************/
void SimpleCalibration::setDefaultConfiguration()
{
    dBlockWidthmm=10.0;
    dHorizontalCalibrationRatio=0.0;
    dBlockWidthPixel=100.0;

    uiSimplecalibration->lineEditBlockWidth->setText(QString::number(dBlockWidthmm));
    uiSimplecalibration->lineEditHorizontalCalibrationRatio->setText(QString::number(dHorizontalCalibrationRatio));
    uiSimplecalibration->lineEditBlockWidthPixel->setText(QString::number(dBlockWidthPixel));
}

/****************************************************************
 * Function:on_pushButtonGetBlockWidthPixel_clicked
 * Description:发送指令给Mainwindow，令其通过qt通信，返回标定块的像素值
 * **************************************************************/
void SimpleCalibration::on_pushButtonGetBlockWidthPixel_clicked()
{
    QString sBlockWidth=uiSimplecalibration->lineEditBlockWidth->text();
    bool bConversionState;
    double dBlockWidth=sBlockWidth.toDouble(&bConversionState);

    if(bConversionState)
    {
        dBlockWidthmm=dBlockWidth;
    }
    else
    {
        dBlockWidthmm=10.0;
        uiSimplecalibration->lineEditBlockWidth->setText(QString::number(dBlockWidthmm));

        QMessageBox msg;
        msg.setText(QStringLiteral("数据输入错误！已设置为默认"));
        msg.exec();

        return;
    }
    emit getBlockWidthPixel_triggered();
}

/****************************************************************
 * Function:receiveBlockWidthPixel
 * Description:接受Mainwindow传过来的blockWidth
 * **************************************************************/
void SimpleCalibration::receiveBlockWidthPixel(double blockWidth)
{
    dBlockWidthPixel=blockWidth;
}

/****************************************************************
 * Function:on_pushButtonCalculate_clicked
 * Description:计算水平标定率
 * **************************************************************/
void SimpleCalibration::on_pushButtonCalculate_clicked()
{
    QString str1=uiSimplecalibration->lineEditBlockWidth->text();
    QString str2=uiSimplecalibration->lineEditBlockWidthPixel->text();
    bool conversionState1;
    bool conversionState2;
    dBlockWidthmm=str1.toDouble(&conversionState1);
    dBlockWidthPixel=str2.toDouble(&conversionState2);

    if(dBlockWidthmm<=0.0&&conversionState1==false)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("物理尺寸输入错误，请更正！"));
        msgbox.exec();
        return;
    }

    if(dBlockWidthPixel<=0.0&&conversionState2==false)
    {
        QMessageBox msgbox;
        msgbox.setText(QStringLiteral("像素尺寸输入错误，请更正！"));
        msgbox.exec();
        return;
    }
    dHorizontalCalibrationRatio=dBlockWidthmm/dBlockWidthPixel;

    //ui->lineEditBlockWidthPixel->setText(QString::number(dBlockWidthPixel));
    uiSimplecalibration->lineEditHorizontalCalibrationRatio->setText(QString::number(dHorizontalCalibrationRatio));

    emit updateHorizontalCalibrationRatio_triggered(dHorizontalCalibrationRatio);
    emit updateCalibrationState_triggered();
}

void SimpleCalibration::on_pushButtonQuit_clicked()
{
    this->close();
}
